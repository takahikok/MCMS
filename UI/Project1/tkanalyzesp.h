#include "tkadc.h"
#include "tkadcinfo.h"
#include "tkshotinfo.h"
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include "clx/ini.h"
//#include "clx/ftp.h"
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <istream>
#include "clx/salgorithm.h"
#include "tkplot.h"
#include "tkutil.h"
#include "tkphysics.h"
#ifndef __TKANALYZESP__
#define __TKANALYZESP__

class TKANALYZESP
{
public:
	class FITRANGE
	{
	public:
		TKPLOT::RANGE<double> Iis;
		TKPLOT::RANGE<double> Ie;
		TKPLOT::RANGE<double> Ies;
	public:
		FITRANGE(TKPLOT::RANGE<double> Iis_, TKPLOT::RANGE<double> Ie_, TKPLOT::RANGE<double> Ies_)
		{
			Iis = Iis_;
			Ie = Ie_;
			Ies = Ies_;
		}
		FITRANGE()
		{
		}
	};
	FITRANGE fitrange;
private:
	TKSHOT* thisShot;
	clx::ini* Setting;
	std::vector<TKPLOT::PLOTINFO> plotInfo;

private:
	double calcSurfaceArea(TKChargedParticleType particle_type)
	{
		double r = std::stod((*Setting)["AnalyzeSP"]["ProbeTipRadius"]);
		double l = std::stod((*Setting)["AnalyzeSP"]["ProbeTipLength"]);

		switch (particle_type) {
		case TKChargedParticleType::electron:
			if ((*Setting)["AnalyzeSP"]["ElectronCurrentCollectionSurfaceArea"] == "2rl")
				return 2 * r * l;
			else if ((*Setting)["AnalyzeSP"]["ElectronCurrentCollectionSurfaceArea"] == "4rl")
				return 4 * r * l;
			else if ((*Setting)["AnalyzeSP"]["ElectronCurrentCollectionSurfaceArea"] == "Cylinder")
				return 4 * M_PI * r * l + M_PI * r * r;
			else
				return std::stod((*Setting)["AnalyzeSP"]["ElectronCurrentCollectionSurfaceArea"]);
			break;
		case TKChargedParticleType::ion:
			if ((*Setting)["AnalyzeSP"]["IonCurrentCollectionSurfaceArea"] == "2rl")
				return 2 * r * l;
			else if ((*Setting)["AnalyzeSP"]["IonCurrentCollectionSurfaceArea"] == "4rl")
				return 4 * r * l;
			else if ((*Setting)["AnalyzeSP"]["IonCurrentCollectionSurfaceArea"] == "Cylinder")
				return 4 * M_PI * r * l + M_PI * r * r;
			else
				return std::stod((*Setting)["AnalyzeSP"]["IonCurrentCollectionSurfaceArea"]);
			break;
		}

	}

public:
	TKANALYZESP(TKSHOT* TKShot_, clx::ini* Setting_)
	{
		thisShot = TKShot_;
		Setting = Setting_;
	}

	int PlotAnalyzeSP(TKPLOT::PLOTSIZE plot_size, int shot_number)
	{
		plotInfo.clear();
		for (int data_index = 0; data_index < thisShot->GetADCNumber(); data_index++) {
			for (int trace_index = 0; trace_index < thisShot->GetTraceTotalNumber(thisShot->GetADCID(data_index));
				trace_index++) {
				TKPLOT::PLOTINFO plot_info;

				plot_info.model_name = thisShot->GetModelName(thisShot->GetADCID(data_index));
				plot_info.channel_number = thisShot->GetChannelNumber(thisShot->GetADCID(data_index), trace_index);
				plot_info.plot_file_name = "analyzeSP";
				plot_info.xrange.min = thisShot->GetHOffset(thisShot->GetADCID(data_index));
				plot_info.xrange.max = (thisShot->GetHOffset(thisShot->GetADCID(data_index))
					+ thisShot->GetHResolution(thisShot->GetADCID(data_index))
					* thisShot->GetBlockSize(thisShot->GetADCID(data_index)));
				plot_info.h_resolution = thisShot->GetHResolution(thisShot->GetADCID(data_index));
				plot_info.trace_index = trace_index;
				plot_info.data_file_name = thisShot->GetDataFileName(thisShot->GetADCID(data_index));

				plot_info.yrange.min = thisShot->GetVMinData(thisShot->GetADCID(data_index), trace_index) * thisShot->GetVResolution(thisShot->GetADCID(data_index), trace_index) + thisShot->GetVOffset(thisShot->GetADCID(data_index), trace_index);
				plot_info.yrange.max = thisShot->GetVMaxData(thisShot->GetADCID(data_index), trace_index) * thisShot->GetVResolution(thisShot->GetADCID(data_index), trace_index) + thisShot->GetVOffset(thisShot->GetADCID(data_index), trace_index);

				switch (plot_size) {
				case TKPLOT::PLOTSIZE::small_size:
					plot_info.terminal_size.w = 400;
					plot_info.terminal_size.h = 200;
					plot_info.drawing_origin.x = 80;
					plot_info.drawing_origin.y = 50;
					plot_info.drawing_size.w = 300;
					plot_info.drawing_size.h = 130;
					plot_info.label_position.push_back(TKPLOT::POSITION<float>(0.0f, 1.06f));
					plot_info.label_position.push_back(TKPLOT::POSITION<float>(1.0f, 1.06f));
					plot_info.label_position.push_back(TKPLOT::POSITION<float>(0.5f, -0.3f));
					plot_info.label_position.push_back(TKPLOT::POSITION<float>(-0.23f, 0.5f));
					break;
				case TKPLOT::PLOTSIZE::medium_size:
					plot_info.terminal_size.w = 600;
					plot_info.terminal_size.h = 300;
					plot_info.drawing_origin.x = 90;
					plot_info.drawing_origin.y = 60;
					plot_info.drawing_size.w = 420;
					plot_info.drawing_size.h = 210;
					plot_info.label_position.push_back(TKPLOT::POSITION<float>(0.0f, 1.05f));
					plot_info.label_position.push_back(TKPLOT::POSITION<float>(1.0f, 1.05f));
					plot_info.label_position.push_back(TKPLOT::POSITION<float>(0.5f, -0.3f));
					plot_info.label_position.push_back(TKPLOT::POSITION<float>(-0.23f, 0.5f));
					break;
				}

				plot_info.every = 0xffff / 10 / plot_info.drawing_size.w;

				plotInfo.push_back(plot_info);
			}
		}

		std::ofstream of;
		of.open((std::string)"analyzeSP" + ".plt", std::ios::trunc);


		of << "set term png enhanced transparent truecolor font arial 11 size "
			<< plotInfo[0].terminal_size.str() << std::endl;
		of << "" << std::endl;
		of << "set datafile separator \',\'" << std::endl;
		of << "set grid xtics ytics" << std::endl;
		of << "set nokey" << std::endl;
		of << "" << std::endl;
		of << "#---CONST---" << std::endl;
		of << "CONST_PI=3.14160" << std::endl;
		of << "CONST_e=1.602176462e-19 #[C] ([J/eV])" << std::endl;
		of << "CONST_m_e=9.109e-31 #[kg]" << std::endl;
		of << "CONST_k_B=8.617e-5 #[eV/K]" << std::endl;
		of << "CONST_k_B2=1.381e-23 #[J/K]" << std::endl;
		of << "CONST_m_i=4.002602*1.661e-27-CONST_m_e*2" << std::endl;
		of << "CONST_eps0=8.854e-12" << std::endl;
		of << "S_e = " << calcSurfaceArea(TKChargedParticleType::electron) << " #[m^2]" << std::endl;
		of << "S_i = " << calcSurfaceArea(TKChargedParticleType::electron) << " #[m^2]" << std::endl;
		of << "" << std::endl;
		of << "#---FUNCTION---" << std::endl;
		of << "F_Iis(x)=a_Iis*x+b_Iis" << std::endl;
		of << "F_Ii(x)=a_Ii*x+b_Ii" << std::endl;
		of << "F_Ie(x)=exp(a_Ie*x+b_Ie)" << std::endl;
		of << "F_Ies(x)=exp(a_Ies*x+b_Ies)" << std::endl;
		of << "T_e(x)=x/CONST_k_B" << std::endl;
		of << "" << std::endl;
		of << "#---FITTING---" << std::endl;
		of << "set fit errorvariables" << std::endl;
		of << "set fit quiet" << std::endl;
		of << "" << std::endl;
		of << "fit " << fitrange.Iis.str() << " "
			<< "F_Iis(x) "
			<< "\"" << clx::replace_all_copy(plotInfo[std::stoi((*Setting)["AnalyzeSP"]["IChannelIndex"])].data_file_name, "\\", "\\\\") << ".CSV\""
			<< " every " << plotInfo[0].every
			<< " using "
			<< "($" << std::to_string(plotInfo[std::stoi((*Setting)["AnalyzeSP"]["VChannelIndex"])].trace_index + 1)
			<< "*(" << std::to_string(1.0 / std::stod(static_cast<std::string>((*Setting)["AnalyzeSP"]["VGain"]))) << "))"
			<< ":"
			<< "($" << std::to_string(plotInfo[std::stoi((*Setting)["AnalyzeSP"]["IChannelIndex"])].trace_index + 1)
			<< "*(" << std::to_string(1.0 / std::stod(static_cast<std::string>((*Setting)["AnalyzeSP"]["IR"]))
			/ std::stod(static_cast<std::string>((*Setting)["AnalyzeSP"]["IGain"]))
			* ((*Setting)["AnalyzeSP"]["ProbeCurrentPolarity"] == "IonCurrent" ? -1 : 1)) << ")"
			<< ") "
			<< "via a_Iis, b_Iis"
			<< std::endl;
		of << "" << std::endl;
		of << "" << std::endl;
		of << "#---PLOT---" << std::endl;
		of << "set out \"analyzeSP0.png\"" << std::endl;
		of << "set object 1 rect from graph 0, 0 to graph 1, 1 behind linewidth 0 fillcolor rgb \"yellow\" fill solid 0.3 noborder" << std::endl;
		of << "set object 2 rect from first " << fitrange.Iis.min << ", graph 0 to first " << fitrange.Iis.max << ", graph 1 behind linewidth 0 fillcolor rgb \"green\" fill solid 0.1 noborder" << std::endl;
		of << "set xtics 50" << std::endl;
		of << "set mxtics 5" << std::endl;
		of << "set xlabel \"probe voltage[V]\"" << std::endl;
		of << "set ylabel \"probe current[mA]\"" << std::endl;
		of << "plot \"" << clx::replace_all_copy(plotInfo[std::stoi((*Setting)["AnalyzeSP"]["IChannelIndex"])].data_file_name, "\\", "\\\\") << ".CSV\""
			<< " every " << plotInfo[0].every
			<< " using "
			<< "($" << std::to_string(plotInfo[std::stoi((*Setting)["AnalyzeSP"]["VChannelIndex"])].trace_index + 1)
			<< "*(" << std::to_string(1.0 / std::stod(static_cast<std::string>((*Setting)["AnalyzeSP"]["VGain"]))) << "))"
			<< ":"
			<< "($" << std::to_string(plotInfo[std::stoi((*Setting)["AnalyzeSP"]["IChannelIndex"])].trace_index + 1)
			<< "*(" << std::to_string(1.0 / std::stod(static_cast<std::string>((*Setting)["AnalyzeSP"]["IR"]))
			/ std::stod(static_cast<std::string>((*Setting)["AnalyzeSP"]["IGain"]))
			* ((*Setting)["AnalyzeSP"]["ProbeCurrentPolarity"] == "IonCurrent" ? -1 : 1) * 1e3) << ")"
			<< ")"
			<< " pt 0 lc rgb \"red\", F_Iis(x) * 1e3 lw 2 lc rgb \"dark-green\""
			<< std::endl;
		of << "" << std::endl;
		of << "" << std::endl;
		of << "#---FITTING---" << std::endl;
		of << "CONST_PI=3.1416" << std::endl;
		of << "CONST_e=1.602176462e-19 #[C] ([J/eV])" << std::endl;
		of << "CONST_m_e=9.109e-31 #[kg]" << std::endl;
		of << "CONST_k_B=8.617e-5 #[eV/K]" << std::endl;
		of << "CONST_k_B2=1.381e-23 #[J/K]" << std::endl;
		of << "CONST_m_i=4.002602*1.661e-27-CONST_m_e*2" << std::endl;
		of << "CONST_eps0=8.854e-12" << std::endl;
		of << "S_e = " << calcSurfaceArea(TKChargedParticleType::electron) << " #[m^2]" << std::endl;
		of << "S_i = " << calcSurfaceArea(TKChargedParticleType::electron) << " #[m^2]" << std::endl;
		of << "" << std::endl;
		of << "a_Ie = 0.1" << std::endl;
		of << "b_Ie = -3" << std::endl;
		of << "a_Ies = 0.004" << std::endl;
		of << "b_Ies = -6.3" << std::endl;
		of << "" << std::endl;
		of << "fit " << fitrange.Ie.str() << " "
			<< "F_Ie(x) "
			<< "\"" << clx::replace_all_copy(plotInfo[std::stoi((*Setting)["AnalyzeSP"]["IChannelIndex"])].data_file_name, "\\", "\\\\") << ".CSV\""
			<< " every " << plotInfo[0].every
			<< " using "
			<< "($" << std::to_string(plotInfo[std::stoi((*Setting)["AnalyzeSP"]["VChannelIndex"])].trace_index + 1)
			<< "*(" << std::to_string(1.0 / std::stod(static_cast<std::string>((*Setting)["AnalyzeSP"]["VGain"]))) << "))"
			<< ":"
			<< "($" << std::to_string(plotInfo[std::stoi((*Setting)["AnalyzeSP"]["IChannelIndex"])].trace_index + 1)
			<< "*(" << std::to_string(1.0 / std::stod(static_cast<std::string>((*Setting)["AnalyzeSP"]["IR"]))
			/ std::stod(static_cast<std::string>((*Setting)["AnalyzeSP"]["IGain"]))
			* ((*Setting)["AnalyzeSP"]["ProbeCurrentPolarity"] == "IonCurrent" ? -1 : 1)) << ")"
			<< "-F_Iis("
			<< "($" << std::to_string(plotInfo[std::stoi((*Setting)["AnalyzeSP"]["VChannelIndex"])].trace_index + 1)
			<< "*(" << std::to_string(1.0 / std::stod(static_cast<std::string>((*Setting)["AnalyzeSP"]["VGain"]))) << "))"
			<< ")"
			<< ") "
			<< "via a_Ie, b_Ie"
			<< std::endl;
		of << "" << std::endl;
		of << "fit " << fitrange.Ies.str() << " "
			<< "F_Ies(x) "
			<< "\"" << clx::replace_all_copy(plotInfo[std::stoi((*Setting)["AnalyzeSP"]["IChannelIndex"])].data_file_name, "\\", "\\\\") << ".CSV\""
			<< " every " << plotInfo[0].every
			<< " using "
			<< "($" << std::to_string(plotInfo[std::stoi((*Setting)["AnalyzeSP"]["VChannelIndex"])].trace_index + 1)
			<< "*(" << std::to_string(1.0 / std::stod(static_cast<std::string>((*Setting)["AnalyzeSP"]["VGain"]))) << "))"
			<< ":"
			<< "($" << std::to_string(plotInfo[std::stoi((*Setting)["AnalyzeSP"]["IChannelIndex"])].trace_index + 1)
			<< "*(" << std::to_string(1.0 / std::stod(static_cast<std::string>((*Setting)["AnalyzeSP"]["IR"]))
			/ std::stod(static_cast<std::string>((*Setting)["AnalyzeSP"]["IGain"]))
			* ((*Setting)["AnalyzeSP"]["ProbeCurrentPolarity"] == "IonCurrent" ? -1 : 1)) << ")"
			<< "-F_Iis("
			<< "($" << std::to_string(plotInfo[std::stoi((*Setting)["AnalyzeSP"]["VChannelIndex"])].trace_index + 1)
			<< "*(" << std::to_string(1.0 / std::stod(static_cast<std::string>((*Setting)["AnalyzeSP"]["VGain"]))) << "))"
			<< ")"
			<< ") "
			<< "via a_Ies, b_Ies"
			<< std::endl;
		of << "" << std::endl;
		of << "" << std::endl;
		of << "#---CALC---" << std::endl;
		of << "Vs_ = -(b_Ies - b_Ie)/(a_Ies - a_Ie)" << std::endl;
		of << "Ies_ = F_Ies(Vs_)" << std::endl;
		of << "Te_ = 1.0/a_Ie" << std::endl;
		of << "ne_ = Ies_ / (S_e * CONST_e * sqrt(CONST_e * Te_ / (2 * CONST_PI * CONST_m_e)))" << std::endl;
		of << "print Vs_" << std::endl;
		of << "print Ies_" << std::endl;
		of << "print ne_" << std::endl;
		of << "print Te_" << std::endl;
		of << "" << std::endl;
		of << "" << std::endl;
		of << "" << std::endl;
		of << "#---PLOT---" << std::endl;
		of << "set out \"analyzeSP1.png\"" << std::endl;
		of << "#set object 1 rect from graph 0, 0 to graph 1, 1 behind linewidth 0 fillcolor rgb \"yellow\" fill solid 0.3 noborder" << std::endl;
		of << "set object 2 rect from first " << fitrange.Ie.min << ", graph 0 to first " << fitrange.Ie.max << ", graph 1 behind linewidth 0 fillcolor rgb \"cyan\" fill solid 0.1 noborder" << std::endl;
		of << "set object 3 rect from first " << fitrange.Ies.min << ", graph 0 to first " << fitrange.Ies.max << ", graph 1 behind linewidth 0 fillcolor rgb \"skyblue\" fill solid 0.1 noborder" << std::endl;
		of << "set logscale y" << std::endl;
		of << "set format y \"10 ^ {%L}\"" << std::endl;
		of << "set yrange[F_Ie(" << fitrange.Ie.min << ") / 5:F_Ies(" << fitrange.Ies.max << ") * 2]" << std::endl;
		of << "set xtics 50" << std::endl;
		of << "set mxtics 5" << std::endl;
		of << "set mytics 10" << std::endl;
		of << "set xlabel \"probe voltage[V]\"" << std::endl;
		of << "set ylabel \"probe current[A]\"" << std::endl;
		of << "set label 120 sprintf(\"{ / Arial:Italic n}_e = %1.2E m^{ -3 }\", ne_) at graph 0.65, 0.35 left" << std::endl;
		of << "set label 121 sprintf(\"{ / Arial:Italic T}_e = %1.2f eV\", Te_) at graph 0.65, 0.27 left" << std::endl;
		of << "set label 122 sprintf(\"{ / Arial:Italic V}_s = %1.2f eV\", Vs_) at graph 0.65, 0.19 left" << std::endl;
		of << "plot \"" << clx::replace_all_copy(plotInfo[std::stoi((*Setting)["AnalyzeSP"]["IChannelIndex"])].data_file_name, "\\", "\\\\") << ".CSV\""
			<< " every " << plotInfo[0].every
			<< " using "
			<< "($" << std::to_string(plotInfo[std::stoi((*Setting)["AnalyzeSP"]["VChannelIndex"])].trace_index + 1)
			<< "*(" << std::to_string(1.0 / std::stod(static_cast<std::string>((*Setting)["AnalyzeSP"]["VGain"]))) << "))"
			<< ":"
			<< "($" << std::to_string(plotInfo[std::stoi((*Setting)["AnalyzeSP"]["IChannelIndex"])].trace_index + 1)
			<< "*(" << std::to_string(1.0 / std::stod(static_cast<std::string>((*Setting)["AnalyzeSP"]["IR"]))
			/ std::stod(static_cast<std::string>((*Setting)["AnalyzeSP"]["IGain"]))
			* ((*Setting)["AnalyzeSP"]["ProbeCurrentPolarity"] == "IonCurrent" ? -1 : 1)) << ")"
			<< "-F_Iis("
			<< "($" << std::to_string(plotInfo[std::stoi((*Setting)["AnalyzeSP"]["VChannelIndex"])].trace_index + 1)
			<< "*(" << std::to_string(1.0 / std::stod(static_cast<std::string>((*Setting)["AnalyzeSP"]["VGain"]))) << "))"
			<< ")"
			<< ") "
			<< " pt 0 lc rgb \"red\", "


			// plot fitting function

			<< "[" << fitrange.Ie.min - 20 << ":] F_Ie(x) lw 2 lc rgb \"blue\", "
			<< "[" << fitrange.Ie.min - 20 << ":] F_Ies(x) lw 2 lc rgb \"dark-magenta\""
			<< std::endl;
		of << "" << std::endl;
		of << "#---OUT---" << std::endl;
		of << "set print \"analyzeSP.tmp\"" << std::endl;
		of << "print Vs_" << std::endl;
		of << "print ne_" << std::endl;
		of << "print Te_" << std::endl;
		of << "" << std::endl;

		of.close();
		std::system(((std::string)"gnuplot " + plotInfo[0].plot_file_name + ".plt").c_str());


		return static_cast<int>(plotInfo.size());
	}
	std::vector<TKPLOT::PLOTINFO> GetPlotInfo()
	{
		return plotInfo;
	}
	std::vector<TKPLOT::PLOTINFO>::pointer GetPlotInfoPtr()
	{
		return plotInfo.data();
	}
	FITRANGE &SetRange()
	{
		return fitrange;
	}
};
#endif
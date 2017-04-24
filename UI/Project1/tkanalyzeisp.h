﻿#include "tkanalyze.h"
#ifndef __TKANALYZEISP__
#define __TKANALYZEISP__

class TKANALYZEISP : public TKANALYZE
{
private:
	int ma_sample_number;

private:
	double calcSurfaceArea(TKChargedParticleType particle_type)
	{
		double r = std::stod((*Setting)[group]["ProbeTipRadius"]);
		double l = std::stod((*Setting)[group]["ProbeTipLength"]);

		std::string prefix;
		switch (particle_type) {
		case TKChargedParticleType::electron:
			prefix = "Electron";
			break;
		case TKChargedParticleType::ion:
			prefix = "Ion";
			break;
		}
		if ((*Setting)[group][prefix + "CurrentCollectionSurfaceArea"] == "2rl")
			return 2 * r * l;
		else if ((*Setting)[group][prefix + "CurrentCollectionSurfaceArea"] == "4rl")
			return 4 * r * l;
		else if ((*Setting)[group][prefix + "CurrentCollectionSurfaceArea"] == "Cylinder")
			return 4 * M_PI * r * l + M_PI * r * r;
		else
			return std::stod((*Setting)[group][prefix + "CurrentCollectionSurfaceArea"]);
	}

public:
	TKANALYZEISP(TKSHOT* TKShot_, clx::ini* Setting_, std::string group_) : TKANALYZE(TKShot_, Setting_, group_)
	{
	}

	int PlotAnalyzeSP(TKPLOT::PLOTSIZE plot_size, int shot_number)
	{
		plotInfo.clear();
		for (int data_index = 0; data_index < thisShot->GetADCNumber(); data_index++)
			for (int trace_index = 0; trace_index < thisShot->GetTraceTotalNumber(thisShot->GetADCID(data_index));
				trace_index++)
				plotInfo.push_back(loadPlotInfoInstance(data_index, trace_index, plot_size));

		int v_channel_plot_info_index = std::stoi((*Setting)[group]["VChannelIndex"]);
		int i_channel_plot_info_index = std::stoi((*Setting)[group]["IChannelIndex"]);

		std::string ma_file_name = [&]() -> std::string
		{
			std::string source_file, out_file;


			if ((*Setting)[group]["PreDataProcessing"] == "Raw")
				pre_data_process = PREDATAPROCESSS::Raw;
			if ((*Setting)[group]["PreDataProcessing"] == "SMA")
				pre_data_process = PREDATAPROCESSS::SMA;
			if ((*Setting)[group]["PreDataProcessing"] == "SMA+KillHysteresis")
				pre_data_process = PREDATAPROCESSS::SMA_KH;
			if ((*Setting)[group]["PreDataProcessing"] == "SMA+KillHysteresis+SMA")
				pre_data_process = PREDATAPROCESSS::SMA_KH_SMA;

			int ma_sample[2];
			for (int i = 0; i < 2; i++)
				ma_sample[i] = std::stoi((*Setting)[group]["PreDataProcessingSMA" + std::to_string(i + 1) + "Sample"]);

			switch (pre_data_process) {
			case PREDATAPROCESSS::SMA:
				out_file = thisShot->GetDataFileName(thisShot->GetADCID(plotInfo[i_channel_plot_info_index].data_index))
					+ (std::string)"_SMA_" + std::to_string(ma_sample[0]);
				std::cerr << (std::string)"MovingAverage.exe " + thisShot->GetDataFileName(thisShot->GetADCID(plotInfo[i_channel_plot_info_index].data_index)) + ".CSV "
					+ std::to_string(ma_sample[0])
					+ " > " + out_file + ".CSV" << std::endl;
				if (!TKUTIL::IsExistFile(out_file + ".CSV"))
					std::system(((std::string)"MovingAverage.exe " + thisShot->GetDataFileName(thisShot->GetADCID(plotInfo[i_channel_plot_info_index].data_index)) + ".CSV "
						+ std::to_string(ma_sample[0])
						+ " > " + out_file + ".CSV").c_str());
				break;
			case PREDATAPROCESSS::SMA_KH:
				out_file = thisShot->GetDataFileName(thisShot->GetADCID(plotInfo[i_channel_plot_info_index].data_index))
					+ (std::string)"_SMA_" + std::to_string(ma_sample[0]);
				if (!TKUTIL::IsExistFile(out_file + ".CSV"))
					std::system(((std::string)"MovingAverage.exe " + thisShot->GetDataFileName(thisShot->GetADCID(plotInfo[i_channel_plot_info_index].data_index)) + ".CSV "
						+ std::to_string(ma_sample[0])
						+ " > " + out_file + ".CSV").c_str());

				source_file = out_file;
				out_file = source_file + "_KH_" + "0_200200_0";
				if (!TKUTIL::IsExistFile(out_file + ".CSV"))
					std::system(((std::string)"TKKillHysteresis.exe " + source_file + ".CSV "
						+ "0" + " " + "200200" + " " + "0"
						+ " > " + out_file + ".CSV").c_str());
				break;
			case PREDATAPROCESSS::SMA_KH_SMA:
				out_file = thisShot->GetDataFileName(thisShot->GetADCID(plotInfo[i_channel_plot_info_index].data_index))
					+ (std::string)"_SMA_" + std::to_string(ma_sample[0]);
				if (!TKUTIL::IsExistFile(out_file + ".CSV"))
					std::system(((std::string)"MovingAverage.exe " + thisShot->GetDataFileName(thisShot->GetADCID(plotInfo[i_channel_plot_info_index].data_index)) + ".CSV "
						+ std::to_string(ma_sample[0])
						+ " > " + out_file + ".CSV").c_str());

				source_file = out_file;
				out_file = source_file + "_KH_" + "0_200200_0";
				if (!TKUTIL::IsExistFile(out_file + ".CSV"))
					std::system(((std::string)"TKKillHysteresis.exe " + source_file + ".CSV "
						+ "0" + " " + "200200" + " " + "0"
						+ " > " + out_file + ".CSV").c_str());

				source_file = out_file;
				out_file = source_file
					+ (std::string)"_SMA_" + std::to_string(ma_sample[1]);
				if (!TKUTIL::IsExistFile(out_file + ".CSV"))
					std::system(((std::string)"MovingAverage.exe " + source_file + ".CSV "
						+ std::to_string(ma_sample[1])
						+ " > " + out_file + ".CSV").c_str());

				break;
			case PREDATAPROCESSS::Raw:
				out_file = thisShot->GetDataFileName(thisShot->GetADCID(plotInfo[i_channel_plot_info_index].data_index));
				break;
			default:
				break;
			}
			return out_file;

		}();

		std::ofstream of;
		of.open(group + ".plt", std::ios::trunc);


		of << "set term png enhanced transparent truecolor font arial 11 size "
			<< plotInfo[0].terminal_size.str() << std::endl;
		of << "" << std::endl;
		of << "set datafile separator \',\'" << std::endl;
		of << "set grid xtics ytics" << std::endl;
		of << "set nokey" << std::endl;
		of << "" << std::endl;

		auto def_const = [&]()
		{
			of << "#---CONST---" << std::endl;
			of << "CONST_PI=3.14160" << std::endl;
			of << "CONST_e=1.602176462e-19 #[C] ([J/eV])" << std::endl;
			of << "CONST_m_e=9.109e-31 #[kg]" << std::endl;
			of << "CONST_k_B=8.617e-5 #[eV/K]" << std::endl;
			of << "CONST_k_B2=1.381e-23 #[J/K]" << std::endl;
			of << "CONST_m_i=4.002602*1.661e-27-CONST_m_e*2" << std::endl;
			of << "CONST_eps0=8.854e-12" << std::endl;
			of << "S_e = " << calcSurfaceArea(TKChargedParticleType::electron) << " #[m^2]" << std::endl;
			of << "S_i = " << calcSurfaceArea(TKChargedParticleType::ion) << " #[m^2]" << std::endl;
			return 0;
		};
		def_const();
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

		auto polarity = [&]()
		{
			return (((*Setting)[group]["ProbeCurrentPolarity"] == "IonCurrent")
				^ ((*Setting)[group]["AnalyzeCurrentPolarity"] == "IonCurrent") ? -1 : 1);
		};

		auto svp = [&]()
		{
			return "($" + std::to_string(plotInfo[v_channel_plot_info_index].trace_index + 1)
				+ "*(" + std::to_string(1.0 / std::stod(static_cast<std::string>((*Setting)[group]["VGain"]))
					*((*Setting)[group]["VMonitorGain"] == "1/100" ? 100 : 1)) + ")"
				+ [&]()
			{
				if ((*Setting)[group]["ProbeVoltageShift"] == "Consider")
					return (std::string)" - " + "($" + std::to_string(plotInfo[i_channel_plot_info_index].trace_index + 1)
					+ " * (" + std::to_string(1.0 / std::stod(static_cast<std::string>((*Setting)[group]["IGain"]))
						* polarity()) + ")";
				else
					return (std::string)"";
			}()
				+ "))";
		};

		auto sip = [&]()
		{
			return "($" + std::to_string(plotInfo[i_channel_plot_info_index].trace_index + 1)
				+ "*(" + std::to_string(1.0 / std::stod(static_cast<std::string>((*Setting)[group]["IR"]))
					/ std::stod(static_cast<std::string>((*Setting)[group]["IGain"]))
					* polarity()) + "))";
		};

		//of << "fit " << fitrange.Iis.str() << " "
		//	<< "F_Iis(x) "
		//	<< "\"" << clx::replace_all_copy(ma_file_name, "\\", "\\\\") << ".CSV\""
		//	<< " every " << plotInfo[i_channel_plot_info_index].CalcEveryValue(10)
		//	<< " using "
		//	<< svp()
		//	<< ":"
		//	<< sip()
		//	<< "via a_Iis, b_Iis"
		//	<< std::endl;
		of << "" << std::endl;
		of << "" << std::endl;

		of << "#---PLOT---" << std::endl;
		of << "set out \"" + group + "0.png\"" << std::endl;
		of << "set object 1 rect from graph 0, 0 to graph 1, 1 behind linewidth 0 fillcolor rgb \"yellow\" fill solid 0.3 noborder" << std::endl;
		of << "set object 2 rect from first " << fitrange.Ie.min << ", graph 0 to first " << fitrange.Ie.max << ", graph 1 behind linewidth 0 fillcolor rgb \"skyblue\" fill solid 0.1 noborder" << std::endl;
		//		of << "set object 2 rect from first " << fitrange.Iis.min << ", graph 0 to first " << fitrange.Iis.max << ", graph 1 behind linewidth 0 fillcolor rgb \"skyblue\" fill solid 0.1 noborder" << std::endl;
		auto graph_top_info = [&]()
		{
			of << "set label 1 left at graph " << plotInfo[i_channel_plot_info_index].label_position[0].str() << " \""
				<< "CH" << thisShot->GetChannelNumber(thisShot->GetADCID(plotInfo[v_channel_plot_info_index].data_index), plotInfo[v_channel_plot_info_index].trace_index)
				<< " : CH" << thisShot->GetChannelNumber(thisShot->GetADCID(plotInfo[i_channel_plot_info_index].data_index), plotInfo[i_channel_plot_info_index].trace_index)
				<< " - " << thisShot->GetModelName(thisShot->GetADCID(plotInfo[i_channel_plot_info_index].data_index)) << "\"" << std::endl;
			std::vector<std::string> tok;
			clx::split_if(thisShot->GetDataFileName(thisShot->GetADCID(plotInfo[i_channel_plot_info_index].data_index)), tok, clx::is_any_of("\\"));
			of << "set label 2 right at graph " << plotInfo[i_channel_plot_info_index].label_position[1].str() << " \""
				<< (shot_number ? "#" + TKUTIL::ZeroFill(shot_number, 8) : tok[tok.size() - 1])
				<< "\"" << std::endl;
			return 0;
		};
		graph_top_info();
		of << "set xtics 50" << std::endl;
		of << "set mxtics 5" << std::endl;
		of << "set xlabel \"probe voltage [V]\"" << std::endl;
		of << "set ylabel \"probe current [uA]\"" << std::endl;
		of << "plot "
			<< "\"" << clx::replace_all_copy(ma_file_name, "\\", "\\\\") << ".CSV\""
			<< " every " << plotInfo[i_channel_plot_info_index].CalcEveryValue(10)
			<< " using "
			<< svp()
			<< ":"
			<< "(" << sip() << "*1e6)"
			<< " pt 6 ps 0.2 lc rgb \"red\""
			//<<", F_Iis(x) * 1e3 lw 2 lc rgb \"dark-green\""
			<< std::endl;

		of << "set out \"" + group + "1.png\"" << std::endl;
		of << "set xrange [-50:50]" << std::endl;
		of << "set xtics 10" << std::endl;
		of << "set mxtics 5" << std::endl;
		of << "replot" << std::endl;

		of << "" << std::endl;
		of << "" << std::endl;

		of << "#---FITTING---" << std::endl;
		def_const();
		of << "" << std::endl;
		of << "a_Ie = 0.1" << std::endl;
		of << "b_Ie = -3" << std::endl;
		of << "a_Ies = 0.004" << std::endl;
		of << "b_Ies = -6.3" << std::endl;
		of << "" << std::endl;

		of << "fit " << fitrange.Ie.str() << " "
			<< "F_Ie(x) "
			<< "\"" << clx::replace_all_copy(ma_file_name, "\\", "\\\\") << ".CSV\""
			<< " every " << plotInfo[i_channel_plot_info_index].CalcEveryValue(20)
			<< " using "
			<< svp()
			<< ":"
			<< sip()
			<< "via a_Ie, b_Ie"
			<< std::endl;
		of << "" << std::endl;

		//of << "fit " << fitrange.Ies.str() << " "
		//	<< "F_Ies(x) "
		//	<< "\"" << clx::replace_all_copy(ma_file_name, "\\", "\\\\") << ".CSV\""
		//	<< " every " << plotInfo[i_channel_plot_info_index].CalcEveryValue(10)
		//	<< " using "
		//	<< svp()
		//	<< ":"
		//	<< "(" << sip() << "-F_Iis(" << svp() << "))"
		//	<< "via a_Ies, b_Ies"
		//	<< std::endl;
		of << "" << std::endl;
		of << "" << std::endl;

		of << "#---CALC---" << std::endl;
		//		of << "Vs_ = -(b_Ies - b_Ie)/(a_Ies - a_Ie)" << std::endl;
		//		of << "Ies_ = F_Ies(Vs_)" << std::endl;
		of << "Ti_ = -1.0/a_Ie" << std::endl;
		//		of << "ne_ = Ies_ / (S_e * CONST_e * sqrt(CONST_e * Te_ / (2 * CONST_PI * CONST_m_e)))" << std::endl;
				//of << "print vs_" << std::endl;
				//of << "print ies_" << std::endl;
				//of << "print ne_" << std::endl;
		of << "print Ti_" << std::endl;
		of << "" << std::endl;
		of << "" << std::endl;
		of << "" << std::endl;

		of << "#---PLOT---" << std::endl;
		of << "set out \"" + group + "2.png\"" << std::endl;
		of << "#set object 1 rect from graph 0, 0 to graph 1, 1 behind linewidth 0 fillcolor rgb \"yellow\" fill solid 0.3 noborder" << std::endl;
		of << "set object 2 rect from first " << fitrange.Ie.min << ", graph 0 to first " << fitrange.Ie.max << ", graph 1 behind linewidth 0 fillcolor rgb \"skyblue\" fill solid 0.1 noborder" << std::endl;
		//		of << "set object 3 rect from first " << fitrange.Ies.min << ", graph 0 to first " << fitrange.Ies.max << ", graph 1 behind linewidth 0 fillcolor rgb \"skyblue\" fill solid 0.1 noborder" << std::endl;
		graph_top_info();
		of << "set logscale y" << std::endl;
		of << "set format y \"10^{%T}\"" << std::endl;
		of << "unset xrange" << std::endl;
		of << "set xtics 50" << std::endl;
		of << "set mxtics 5" << std::endl;
		of << "set yrange[F_Ie(" << fitrange.Ie.max << ") / 5:F_Ie(" << fitrange.Ie.min << ") * 5]" << std::endl;
		of << "set xtics 50" << std::endl;
		of << "set mxtics 5" << std::endl;
		of << "set mytics 10" << std::endl;
		of << "set xlabel \"probe voltage [V]\"" << std::endl;
		of << "set ylabel \"electron current [A]\"" << std::endl;
		//		of << "set label 120 sprintf(\"@{{/Arial:Italic n}_e}&{n_e} = %1.2E m^{ -3 }\", ne_) at graph 0.05, 0.85 left" << std::endl;
		of << "set label 121 sprintf(\"@{{/Arial:Italic T}_i}&{n_e} = %1.2f eV\", Ti_) at graph 0.05, 0.77 left" << std::endl;
		//		of << "set label 122 sprintf(\"@{{/Arial:Italic V}_s}&{n_e} = %1.2f eV\", Vs_) at graph 0.05, 0.69 left" << std::endl;


		of << "plot "
			<< "\"" << clx::replace_all_copy(ma_file_name, "\\", "\\\\") << ".CSV\""
			<< " every " << plotInfo[i_channel_plot_info_index].CalcEveryValue(40)
			<< " using "
			<< svp()
			<< ":"
			<< sip()
			<< " pt 6 ps 0.2 lc rgb \"red\", "


			// plot fitting function

			<< "[" << fitrange.Ie.min - 20 << ":] F_Ie(x) lw 2 lc rgb \"blue\" "
			//			<< "[" << fitrange.Ie.min - 20 << ":] F_Ies(x) lw 2 lc rgb \"dark-magenta\""
			<< std::endl;

		of << "set out \"" + group + "3.png\"" << std::endl;
		of << "set xrange [-50:50]" << std::endl;
		of << "set xtics 10" << std::endl;
		of << "set mxtics 5" << std::endl;
		of << "replot" << std::endl;

		of << "" << std::endl;
		of << "#---OUT---" << std::endl;
		of << "set print \"" + group + ".tmp\"" << std::endl;
		//		of << "print Vs_" << std::endl;
		//		of << "print ne_" << std::endl;
		of << "print Ti_" << std::endl;
		of << "" << std::endl;

		of.close();
		std::system(((std::string)"gnuplot " + group + ".plt").c_str());

		for (int i = 0; i < 4; i++)
			plotInfo[i].plot_file_name = group;

		return static_cast<int>(plotInfo.size());
	}

};
#endif
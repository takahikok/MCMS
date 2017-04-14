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
#ifndef __TKANALYZESP__
#define __TKANALYZESP__

class TKANALYZESP {
private:
	TKSHOT* thisShot;
	clx::ini* Setting;
	std::vector<TKPLOT::PLOTINFO> plotInfo;

public:
	TKANALYZESP(TKSHOT* TKShot_, clx::ini* Setting_)
	{
		thisShot = TKShot_;
		Setting = Setting_;
	}

	int PlotRaw(TKPLOT::PLOTSIZE plot_size, int shot_number)
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

		for (int i = 0; i < 3; i++) {
			std::ofstream of;
			plotInfo[i].plot_file_name = plotInfo[i].plot_file_name + std::to_string(i);
			of.open(plotInfo[i].plot_file_name + ".plt", std::ios::trunc);
			of << "set term png enhanced transparent truecolor font arial 11 size "
				<< plotInfo[i].terminal_size.str() << std::endl;
			of << "set out \"" << plotInfo[i].plot_file_name << ".png\"" << std::endl;
			of << "set datafile separator \',\'" << std::endl;
			of << "set grid xtics ytics" << std::endl;
			of << "set nokey" << std::endl;
#if 0
			of << "set multiplot " << std::endl;
//			of << "set origin " << atGraph(plotInfo[i].drawing_origin, plotInfo[i]).str() << std::endl;
//			of << "set size " << atGraph(plotInfo[i].drawing_size, plotInfo[i]).str() << std::endl;
			of << "set margin 0, 0, 0, 0" << std::endl;
			of << "set label 1 left at graph " << plotInfo[i].label_position[0].str() << " \""
				<< "CH" << plotInfo[i].channel_number
				<< " - " << plotInfo[i].model_name << "\"" << std::endl;

			std::vector<std::string> tok;
			clx::split_if(plotInfo[i].data_file_name, tok, clx::is_any_of("\\"));
			of << "set label 2 right at graph " << plotInfo[i].label_position[1].str() << " \""
				<< (shot_number ? "#" + TKUTIL::ZeroFill(shot_number, 8) : tok[tok.size() - 1])
				<< "\"" << std::endl;

			//			of << "set yrange [*<0:0<*]" << std::endl;
//			of << "set yrange " << plotInfo[i].yrange.str() << std::endl;
			//			of << "set format y \"%1.1tE%+-T\"" << std::endl;
			of << "set label 3 center at graph " << plotInfo[i].label_position[2].str()
				<< " \"Time [s]\"" << std::endl;
			of << "set label 4 center at graph " << plotInfo[i].label_position[3].str()
				<< " rotate \"Voltage [V]\"" << std::endl;
//			of << "set xrange " << plotInfo[i].xrange.str() << std::endl;
#endif
			switch (i) {
			case 0:
				break;
			case 1:
				of << "set logscale y" << std::endl;
				break;
			case 2:
				of << "set logscale y" << std::endl;
				of << "set xrange [-50:50]" << std::endl;
				break;
			}
			of << "plot \"" << clx::replace_all_copy(plotInfo[std::stoi((*Setting)["AnalyzeSP"]["IChannelIndex"])].data_file_name, "\\", "\\\\") << ".CSV\""
				<< " every " << plotInfo[i].every
				<< " using "
				<< "($" << std::to_string(plotInfo[std::stoi((*Setting)["AnalyzeSP"]["VChannelIndex"])].trace_index + 1)
				<< "*(" << std::to_string(1.0 / std::stod(static_cast<std::string>((*Setting)["AnalyzeSP"]["VGain"]))) << "))"
				<< ":"
				<< "($" << std::to_string(plotInfo[std::stoi((*Setting)["AnalyzeSP"]["IChannelIndex"])].trace_index + 1)
				<< "*(" << std::to_string(1.0 / std::stod(static_cast<std::string>((*Setting)["AnalyzeSP"]["IR"])) / std::stod(static_cast<std::string>((*Setting)["AnalyzeSP"]["IGain"]))) << ")"
				<< "+" << std::to_string(std::stod(static_cast<std::string>((*Setting)["AnalyzeSP"]["IOffset"]))) << ")"
				<< " with line"
				<< std::endl;
			of << "set print \"" << plotInfo[i].plot_file_name << ".tmp\"" << std::endl;
			of << "print GPVAL_Y_MIN" << std::endl;
			of << "print GPVAL_Y_MAX" << std::endl;
			of << "" << std::endl;

			of.close();
			std::system(((std::string)"gnuplot " + plotInfo[i].plot_file_name + ".plt").c_str());

		}

		for (int i = 0; i < static_cast<int>(plotInfo.size()); i++) {
			std::ifstream ifs(plotInfo[i].plot_file_name + ".tmp");
			std::string buf;
			for (int lines = 1; std::getline(ifs, buf); lines++) {
				switch (lines) {
					//Model
				case 1:
					std::sscanf(buf.c_str(), "%f", &plotInfo[i].yrange.min);
					break;

					//Model
				case 2:
					std::sscanf(buf.c_str(), "%f", &plotInfo[i].yrange.max);
					break;
				}
			}

		}

		return static_cast<int>(plotInfo.size());
	}
	std::vector<TKPLOT::PLOTINFO> GetPlotInfo()
	{
		return plotInfo;
	}
	std::vector<TKPLOT::PLOTINFO>::pointer GetPlotInfoPtr()
	{
		return plotInfo.data();
	}};
#endif
#include "tkadc.h"
#include "tkadcinfo.h"
#include "tkshotinfo.h"
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
//#include "clx/ini.h"
//#include "clx/ftp.h"
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <istream>
#include "clx/salgorithm.h"
#include "tkutil.h"
#ifndef __TKPLOT__
#define __TKPLOT__

class TKPLOT
{
public:
	template<typename T> class RANGE {
	public:
		T min;
		T max;
		RANGE(T min_, T max_)
		{
			min = min_;
			max = max_;
		}
		RANGE()
		{
		}
		std::string str()
		{
			return "[" + std::to_string(min) + ":" + std::to_string(max) + "]";
		}
	};
	template<typename T> class POSITION {
	public:
		T x;
		T y;
		T& u = x;
		T& v = y;
		POSITION(T x_, T y_)
		{
			x = x_;
			y = y_;
		}
		POSITION()
		{
		}
		std::string str()
		{
			return std::to_string(x) + ", " + std::to_string(y);
		}
	};
	template<typename T> class SIZE {
	public:
		T w;
		T h;
		T& u = w;
		T& v = h;
		std::string str()
		{
			return std::to_string(w) + ", " + std::to_string(h);
		}
	};
	struct PLOTINFO {
		std::string plot_file_name;
		std::string data_file_name;
		int trace_index;
		TKPLOT::RANGE<float> xrange;
		TKPLOT::RANGE<float> yrange;
		int every;
		std::string model_name;
		int channel_number;
		float h_resolution;
		SIZE<int> terminal_size;
		SIZE<int> drawing_size;
		POSITION<int> drawing_origin;
		std::vector<POSITION<float>> label_position;

	};
	enum class PLOTSIZE
	{
		small_size, medium_size
	};

private:
	TKSHOT* thisShot;
	std::vector<TKPLOT::PLOTINFO> plotInfo;

private:
	//makeGPCommandPlot;
	/*
	template<typename T> POSITION<float> atGraph(POSITION<T> const &argument, PLOTINFO const &plot_info)
	{
		POSITION<float> at_graph;
		at_graph.x = (float)argument.x / plot_info.terminal_size.w;
		at_graph.y = (float)argument.y / plot_info.terminal_size.h;
		return at_graph;
	}

	template<typename T> SIZE<float> atGraph(SIZE<T> const &argument, PLOTINFO const &plot_info)
	{
		SIZE<float> at_graph;
		at_graph.w = (float)argument.w / plot_info.terminal_size.w;
		at_graph.h = (float)argument.h / plot_info.terminal_size.h;
		return at_graph;
	}
	*/
	template<typename T, template<class> class C> C<float> atGraph(C<T> const &argument, PLOTINFO const &plot_info)
	{
		C<float> at_graph;
		at_graph.u = (float)argument.u / plot_info.terminal_size.u;
		at_graph.v = (float)argument.v / plot_info.terminal_size.v;
		return at_graph;
	}

public:
	TKPLOT(TKSHOT* TKShot_)
	{
		thisShot = TKShot_;
	}
	int Plot()
	{
		std::ofstream of;
		of.open("plot.plt", std::ios::trunc);
		of << "set term png enhanced transparent truecolor font arial 11 size 640, 480" << std::endl;
		of << "set out \"graph1.png\"" << std::endl;
		//	of << "plot using " << std::endl;
		of << "set datafile separator \',\'" << std::endl;
		of << "set multiplot " << std::endl;
		of << "set origin 0.0, 0.46" << std::endl;
		of << "set size 1.0, 0.5" << std::endl;
		of << "set lmargin 7.5" << std::endl;
		of << "set rmargin 2" << std::endl;
		of << "set tmargin 0" << std::endl;
		of << "set bmargin 0" << std::endl;
		of << "set label 2 left at graph 0.05,0.9 \"{/Arial (a)} {/Arial:Italic n}_{/Arial e}\"" << std::endl;
		of << "set yrange [*<0:0<*]" << std::endl;
		of << "plot \"" << thisShot->GetDataFileName(TKADCINFO_ADC_ID_DL750) << ".CSV\""
			<< " every 10"
			<< " using (" << thisShot->GetHOffset(TKADCINFO_ADC_ID_DL750)
			<< " + (column(0)) * 10 * " << thisShot->GetHResolution(TKADCINFO_ADC_ID_DL750)
			<< "):7"
			<< " with line"
			<< std::endl;
		of << "" << std::endl;
		of << "" << std::endl;
		of << "" << std::endl;
		of << "" << std::endl;
		of << "" << std::endl;
		std::system("gnuplot plot.plt");
		return 0;
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
				plot_info.plot_file_name = "PlotRaw_" + plot_info.model_name
					+ "_CH" + std::to_string(plot_info.channel_number);
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
				case PLOTSIZE::small_size:
					plot_info.terminal_size.w = 400;
					plot_info.terminal_size.h = 200;
					plot_info.drawing_origin.x = 80;
					plot_info.drawing_origin.y = 50;
					plot_info.drawing_size.w = 300;
					plot_info.drawing_size.h = 130;
					plot_info.label_position.push_back(POSITION<float>(0.0f, 1.06f));
					plot_info.label_position.push_back(POSITION<float>(1.0f, 1.06f));
					plot_info.label_position.push_back(POSITION<float>(0.5f, -0.3f));
					plot_info.label_position.push_back(POSITION<float>(-0.23f, 0.5f));
					break;
				case PLOTSIZE::medium_size:
					plot_info.terminal_size.w = 600;
					plot_info.terminal_size.h = 300;
					plot_info.drawing_origin.x = 90;
					plot_info.drawing_origin.y = 60;
					plot_info.drawing_size.w = 420;
					plot_info.drawing_size.h = 210;
					plot_info.label_position.push_back(POSITION<float>(0.0f, 1.05f));
					plot_info.label_position.push_back(POSITION<float>(1.0f, 1.05f));
					plot_info.label_position.push_back(POSITION<float>(0.5f, -0.3f));
					plot_info.label_position.push_back(POSITION<float>(-0.23f, 0.5f));
					break;
				}

				plot_info.every = thisShot->GetBlockSize(thisShot->GetADCID(data_index)) / 10 / plot_info.drawing_size.w;

				plotInfo.push_back(plot_info);
			}
		}

		for (int i = 0; i < static_cast<int>(plotInfo.size()); i++) {
			std::ofstream of;
			of.open(plotInfo[i].plot_file_name + ".plt", std::ios::trunc);
			of << "set term png enhanced transparent truecolor font arial 11 size "
				<< plotInfo[i].terminal_size.str() << std::endl;
			of << "set out \"" << plotInfo[i].plot_file_name << ".png\"" << std::endl;
			of << "set datafile separator \',\'" << std::endl;
			of << "set grid xtics ytics" << std::endl;
			of << "set nokey" << std::endl;
			of << "set multiplot " << std::endl;
			of << "set origin " << atGraph(plotInfo[i].drawing_origin, plotInfo[i]).str() << std::endl;
			of << "set size " << atGraph(plotInfo[i].drawing_size, plotInfo[i]).str() << std::endl;
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
			of << "set yrange " << plotInfo[i].yrange.str() << std::endl;
//			of << "set format y \"%1.1tE%+-T\"" << std::endl;
			of << "set label 3 center at graph " << plotInfo[i].label_position[2].str()
				<< " \"Time [s]\"" << std::endl;
			of << "set label 4 center at graph " << plotInfo[i].label_position[3].str()
				<< " rotate \"Voltage [V]\"" << std::endl;
			of << "set xrange " << plotInfo[i].xrange.str() << std::endl;
			of << "plot \"" << clx::replace_all_copy(plotInfo[i].data_file_name, "\\", "\\\\") << ".CSV\""
				<< " every " << plotInfo[i].every
				<< " using (" << plotInfo[i].xrange.min
				<< " + (column(0)) * " << plotInfo[i].every
				<< " * " << plotInfo[i].h_resolution << ")"
				<< ":" << std::to_string(plotInfo[i].trace_index + 1)
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
	}

};

#endif
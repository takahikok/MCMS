﻿#include "tkadc.h"
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
	template<typename T> class RANGE
	{
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
	template<typename T> class POSITION
	{
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
	template<typename T> class SIZE
	{
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

public:
	enum class PLOTSIZE
	{
		SMALL_SIZE,
		MEDIUM_SIZE
	};
	enum class DATASOURCE
	{
		BINARY,
		ASCII
	};


	/**
	* @class PLOTINFO
	* @blief プロット情報クラス
	*
	*	プロット情報クラスはグラフの描画に必要な情報を集めたクラスです。<br>
	*	<br>
	* @par このクラスが作られた背景
	*	ADCモデルによっては機能が制限されることがあります。例えばDL750はVXI11に対応していません。DL1740のコントロールにはEthernetを用いることができません。<br>
	*	また、DL750とDL850のステータスビットの違いのように、ADCモデルによっては同じ機能でも実装が異なることがあります。<br>
	*	このような実装の違いもメソッドをオーバーロードさせることで同様に扱うことができます。<br>
	* @note
	*	もし新たな計測器を追加するようなことがあれば、可能な限りADCコントロールクラスを派生させて多態性を持たせてください。
	*/
	/**
	* @todo
	*	ショット情報に関するPLOTINFOインスタンスは廃止し、TKSHOTを直接参照する
	*/
public:
	class PLOTINFO
	{

	public:
		std::string plot_file_name;
		/**
		* @todo
		*	このインスタンスは廃止し、TKSHOTを直接参照する
		*/
		std::string data_file_name;
		int data_index;
		int trace_index;
		int data_source_point_number;
		int point_number;
		DATASOURCE data_source;
		TKPLOT::RANGE<float> xrange;
		TKPLOT::RANGE<float> yrange;
		unsigned int every = 0;
		/**
		* @todo
		*	このインスタンスは廃止し、TKSHOTを直接参照する
		*/
		std::string model_name;
		/**
		* @todo
		*	このインスタンスは廃止し、TKSHOTを直接参照する
		*/
//		TKDATA::BYTEORDER byte_order;
		/**
		* @todo
		*	このインスタンスは廃止し、TKSHOTを直接参照する
		*/
//		TKDATA::DATAFORMAT data_format;
		/**
		* @todo
		*	このインスタンスは廃止し、TKSHOTを直接参照する
		*/
//		int block_size;
		/**
		*	このインスタンスは廃止し、TKSHOTを直接参照する
		*/
//		int data_offset;
		/**
		* @todo
		*	このインスタンスは廃止し、TKSHOTを直接参照する
		*/
		int channel_number;
		/**
		* @todo
		*	このインスタンスは廃止し、TKSHOTを直接参照する
		*/
//		float h_resolution;
		/**
		* @todo
		*	このインスタンスは廃止し、TKSHOTを直接参照する
		*/
//		float h_offset;
		/**
		* @todo
		*	このインスタンスは廃止し、TKSHOTを直接参照する
		*/
//		float v_resolution;
		/**
		* @todo
		*	このインスタンスは廃止し、TKSHOTを直接参照する
		*/
//		float v_offset;
		SIZE<int> terminal_size;
		SIZE<int> drawing_size;
		POSITION<int> drawing_origin;
		std::vector<POSITION<float>> label_position;

	public:
		std::string GeneratePlotFileName(const std::string prefix)
		{
			plot_file_name = prefix + "_" + model_name + "_CH" + std::to_string(channel_number);
			return plot_file_name;
		}
		unsigned int CalcEveryValue(const unsigned int point_per_pixel)
		{
			every = data_source_point_number / point_per_pixel / drawing_size.w;
			if (every < 0)
				every = 0;
			return every;
		}
	};

private:
	TKSHOT* thisShot;
	std::vector<TKPLOT::PLOTINFO> plotInfo;

private:
	template<typename T, template<class> class C> C<float> atGraph(C<T> const &argument, PLOTINFO const &plot_info)
	{
		C<float> at_graph;
		at_graph.u = (float)argument.u / plot_info.terminal_size.u;
		at_graph.v = (float)argument.v / plot_info.terminal_size.v;
		return at_graph;
	}

protected:
	PLOTINFO& loadPlotInfoInstance(const int data_index, const int trace_index, const PLOTSIZE plot_size = PLOTSIZE::SMALL_SIZE)
	{
		static PLOTINFO plot_info;
		plot_info.data_index = data_index;
		plot_info.trace_index = trace_index;
		plot_info.channel_number = thisShot->GetChannelNumber(thisShot->GetADCID(data_index), trace_index);
		plot_info.model_name = thisShot->GetModelName(thisShot->GetADCID(data_index));
		plot_info.data_source = DATASOURCE::BINARY;
		plot_info.data_source_point_number = thisShot->GetBlockSize(thisShot->GetADCID(data_index));
		plot_info.xrange.min = thisShot->GetHOffset(thisShot->GetADCID(data_index));
		plot_info.xrange.max = (thisShot->GetHOffset(thisShot->GetADCID(data_index))
			+ thisShot->GetHResolution(thisShot->GetADCID(data_index))
			* thisShot->GetBlockSize(thisShot->GetADCID(data_index)));

		plot_info.yrange.min = thisShot->GetVMinData(thisShot->GetADCID(data_index), trace_index) * thisShot->GetVResolution(thisShot->GetADCID(data_index), trace_index) + thisShot->GetVOffset(thisShot->GetADCID(data_index), trace_index);
		plot_info.yrange.max = thisShot->GetVMaxData(thisShot->GetADCID(data_index), trace_index) * thisShot->GetVResolution(thisShot->GetADCID(data_index), trace_index) + thisShot->GetVOffset(thisShot->GetADCID(data_index), trace_index);

		switch (plot_size) {
		case PLOTSIZE::SMALL_SIZE:
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
		case PLOTSIZE::MEDIUM_SIZE:
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

		return plot_info;
	}

public:
	TKPLOT(TKSHOT* TKShot_)
	{
		thisShot = TKShot_;
	}


	int PlotRaw(const TKPLOT::PLOTSIZE plot_size, const int shot_number)
	{
		plotInfo.clear();
		for (int data_index = 0; data_index < thisShot->GetADCNumber(); data_index++)
			for (int trace_index = 0; trace_index < thisShot->GetTraceTotalNumber(thisShot->GetADCID(data_index));
			trace_index++)
				plotInfo.push_back(loadPlotInfoInstance(data_index, trace_index, plot_size));

		for (int i = 0; i < static_cast<int>(plotInfo.size()); i++) {
			std::ofstream of;
			of.open(plotInfo[i].GeneratePlotFileName("PlotRaw") + ".plt", std::ios::trunc);
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
			of << "set object 1 rect from graph 0, 0 to graph 1, 1 behind linewidth 0 fillcolor rgb \"yellow\" fill solid 0.3 noborder" << std::endl;
			of << "set label 1 left at graph " << plotInfo[i].label_position[0].str() << " \""
				<< "CH" << thisShot->GetChannelNumber(thisShot->GetADCID(plotInfo[i].data_index), plotInfo[i].trace_index)
				<< " - " << thisShot->GetModelName(thisShot->GetADCID(plotInfo[i].data_index)) << "\"" << std::endl;

			std::vector<std::string> tok;
			clx::split_if(thisShot->GetDataFileName(thisShot->GetADCID(plotInfo[i].data_index)), tok, clx::is_any_of("\\"));
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
			switch (plotInfo[i].data_source) {
			case DATASOURCE::BINARY:
				//UNIX系では拡張子の大文字小文字の違いに注意
				of << "plot \"" << clx::replace_all_copy(thisShot->GetDataFileName(thisShot->GetADCID(plotInfo[i].data_index)), "\\", "\\\\") << ".WVF\""
					<< " binary format=\"%int16\" array=" << thisShot->GetBlockSize(thisShot->GetADCID(plotInfo[i].data_index))
					<< " dx=" << thisShot->GetHResolution(thisShot->GetADCID(plotInfo[i].data_index))
					<< " skip=" << std::to_string(thisShot->GetBlockSize(thisShot->GetADCID(plotInfo[i].data_index)) * 2 * plotInfo[i].trace_index + thisShot->GetDataOffset(thisShot->GetADCID(plotInfo[i].data_index)))
					<< " origin=(" << thisShot->GetHOffset(thisShot->GetADCID(plotInfo[i].data_index)) << "," << thisShot->GetVOffset(thisShot->GetADCID(plotInfo[i].data_index), plotInfo[i].trace_index) << ")"
					<< " endian=" << (thisShot->GetByteOrder(thisShot->GetADCID(plotInfo[i].data_index)) == TKDATA::BYTEORDER::LITTLE_ENDIAN ? "little" : "big")
					<< " every " << plotInfo[i].CalcEveryValue(10)
					//<< " index " << std::to_string(plotInfo[i].trace_index)
					<< " using ($1)*" << thisShot->GetVResolution(thisShot->GetADCID(plotInfo[i].data_index), plotInfo[i].trace_index)
					<< " \\"
					<< std::endl;
				break;
			case DATASOURCE::ASCII:
				of << "plot \"" << clx::replace_all_copy(thisShot->GetDataFileName(thisShot->GetADCID(plotInfo[i].data_index)), "\\", "\\\\") << ".CSV\""
					<< " every " << plotInfo[i].CalcEveryValue(10)
					<< " using (" << plotInfo[i].xrange.min
					<< " + (column(0)) * " << plotInfo[i].every
					<< " * " << thisShot->GetHResolution(thisShot->GetADCID(plotInfo[i].data_index)) << "+" << thisShot->GetHOffset(thisShot->GetADCID(plotInfo[i].data_index)) << ")"
					<< ":" << std::to_string(plotInfo[i].trace_index + 1)
					<< " \\"
					<< std::endl;
				break;
			}
			of << " with line lc rgb \"red\"" << std::endl;
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
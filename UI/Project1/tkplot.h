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
#include "tkutil.h"
#include <chrono>
#include <ctime>
#ifndef __TKPLOT__
#define __TKPLOT__

/**
* @blief
*	グラフ描画に関するクラスです。
*/
class TKPLOT {
public:
	template<typename T> class RANGE {
	public:
		T min;
		T max;
	public:
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
		T median()
		{
			return (min + max) / 2;
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

public:
	/**
	* @blief
	*	グラフサイズ型
	*/
	enum class PLOTSIZE {
		SMALL_SIZE,
		MEDIUM_SIZE
	};

	/**
	* @blief
	*	データファイル形式型
	*/
	enum class DATASOURCE {
		/**
		* @blief
		*	バイナリファイル<br>
		*	非常に高速に処理できますが、柔軟性にかけるため使用できないことがあります。
		*/
		BINARY,
		/**
		* @blief
		*	ASCIIファイル<br>
		*	データ変換のイニシャルタイムが必要であり、データ読み込みもハイコストなため、処理は遅くなりますが、全ての機能を利用できます。
		*/
		ASCII
	};


	/**
	* @class PLOTINFO
	* @blief プロット情報クラス
	*
	*	プロット情報クラスはグラフの描画に必要な情報を集めたクラスです。
	*/
	/**
	* @todo
	*	ショット情報に関するPLOTINFOインスタンスは廃止し、TKSHOTを直接参照する
	*/
public:
	class PLOTINFO {

	public:
		/**
		* @brief
		*	gnuplotのコマンドファイルの、拡張子を除いたファイルパスです。出力されるグラフのファイルパスも同じパスとなります。<br>
		*	データファイルの拡張子は.pltとなります。<br>
		*	GeneratePlotFileName()によって自動的に初期化されます。
		*/
		std::string plot_file_name;
		std::string out_file_name;

		/**
		* @brief
		*	プロットすべきデータファイルの、拡張子を除いたファイルパスです。絶対参照、相対参照ともに使えます。<br>
		*	データファイルの拡張子は、ASCIIの場合.CSV、バイナリの場合.WVFである必要があります。
		* @note
		*	データファイルがASCIIの場合、最終的に参照されるのは
		*	data_file_nameの末尾に（大文字の）.CSVを足したファイルになります。この仕様によって、大文字と小文字を区別する（例えばUnix系の）環境では
		*	data_file_nameの末尾に（小文字の）.csvを足したファイルをデータファイルとして参照することはできません。大文字と小文字を区別しない
		*	（例えばWindowsのような）環境ではどちらか存在する方のファイルが参照される事になります。
		* @note
		*	データファイルの拡張子が大文字なのは、横河電機のADCの仕様に沿うためです。
		* @todo
		*	このインスタンスは廃止し、TKSHOTを直接参照する
		*/
		std::string data_file_name;

		/**
		* @brief
		*	TKSHOTに格納された全ADC、全トレースのデータを順番に並べたときのトレースの番号です。
		*	data_indexは一意なトレースを指します。
		*/
		int data_index;

		/**
		* @brief
		*	そのトレースが含まれるADCの、全トレースのデータを順番に並べたときのトレースの番号です。
		*	trace_indexはそのADCにおいて一意なトレースを指します。
		* @note
		*	例えばあるADCで CH2, CH5, CH8 を用いて計測が行われていたとき、CH5の
		*	trace_indexは 1 になります。
		* @note
		*	計測器を1台しか用いないショットではdata_indexと
		*	trace_indexの値は等しくなります。
		*/
		int trace_index;

		/**
		* @brief
		*	データファイルの1列あたりのデータ点数です。
		*/
		int data_source_point_number;

		/**
		* @brief
		*	最終的に描画される1列あたりのデータ点数です。
		*/
		int point_number;

		/**
		* @brief
		*	ファイルデータのデータ形式を指定します。指定できるデータ形式は
		*	DATASOURCEを参照してくださいｓ。
		*/
		DATASOURCE data_source;

		/**
		* @brief
		*	描画される、あるいは描画された、グラフのx軸の領域です。
		*/
		TKPLOT::RANGE<float> xrange;

		/**
		* @brief
		*	描画される、あるいは描画された、グラフのy軸の領域です。
		*/
		TKPLOT::RANGE<float> yrange;
		/**
		* @brief
		*	データの間引き量です。データファイルのevery点に対して1点の描画を行います。
		*/
		unsigned int every = 0;

		/**
		* @brief
		*	ADCのモデル名です。
		*	TKSHOTのインスタンスと同じです。
		* @todo
		*	このインスタンスは廃止し、TKSHOTを直接参照する
		*/
		std::string model_name;

		/**
		* @brief
		*	チャンネル番号です。
		*	TKSHOTのインスタンスと同じです。
		* @todo
		*	このインスタンスは廃止し、TKSHOTを直接参照する
		*/
		int channel_number;

		/**
		* @brief
		*	描画されるグラフの、余白を含めた1枚の大きさです。
		*/
		SIZE<int> terminal_size;

		/**
		* @brief
		*	描画されるグラフの、グラフが描画される部分の大きさです。
		*/
		SIZE<int> drawing_size;

		/**
		* @brief
		*	描画されるグラフの、グラフが描画される部分の基点座標です。
		*/
		POSITION<int> drawing_origin;

		/**
		* @brief
		*	描画されるグラフの、ラベル描画の基点座標です。
		*/
		std::vector<POSITION<float>> label_position;

	public:
		/**
		* @brief
		*	gnuplotのコマンドファイルの、拡張子を除いたファイルパスを生成します。出力されるグラフのファイルパスも同じパスとなります。<br>同時に
		*	plot_file_nameを初期化します。
		* @param[in] prefix
		*	ファイル先頭に付けるプレフィックスを指定します。
		* @return plot_file_name
		*	生成されたファイルパスを返します。
		*/
		std::string GeneratePlotFileName(const std::string prefix)
		{
			plot_file_name = prefix + "_" + model_name + "_CH" + std::to_string(channel_number);
			out_file_name = plot_file_name;
			return plot_file_name;
		}

		/**
		* @brief
		*	グラフ情報を元にファイルデータの間引き量を計算します。<br>同時に
		*	everyを初期化します。
		* @param[in] point_per_pixel
		*	1ピクセルあたりの描画点数を指定します。
		* @return every
		*	間引き量を返します。
		*/
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
	clx::ini* Setting;
	std::vector<TKPLOT::PLOTINFO> plotInfo;
	std::string tmp_root;

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
			plot_info.label_position.clear();
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
			plot_info.label_position.clear();
			plot_info.label_position.push_back(POSITION<float>(0.0f, 1.03f));
			plot_info.label_position.push_back(POSITION<float>(1.0f, 1.03f));
			plot_info.label_position.push_back(POSITION<float>(0.5f, -0.3f));
			plot_info.label_position.push_back(POSITION<float>(-0.23f, 0.5f));
			break;
		}

		return plot_info;
	}

	std::string getExtension(std::string group)
	{
		return "."_s + (*Setting)[group]["Terminal"];
	}

public:
	TKPLOT(TKSHOT* TKShot_, clx::ini* Setting_) : thisShot(TKShot_), Setting(Setting_)
	{
		tmp_root = (*Setting)["Utility"]["TempPath"];
	}


	int PlotRaw(const TKPLOT::PLOTSIZE plot_size, const int shot_number, bool replot = true)
	{
		plotInfo.clear();
		for (int data_index = 0; data_index < thisShot->GetADCNumber(); data_index++)
			for (int trace_index = 0; trace_index < thisShot->GetTraceTotalNumber(thisShot->GetADCID(data_index));
				trace_index++)
				plotInfo.push_back(loadPlotInfoInstance(data_index, trace_index, plot_size));

		for (int i = 0; i < static_cast<int>(plotInfo.size()); i++) {
			if (!replot&&TKUTIL::IsExistFile(tmp_root + plotInfo[i].out_file_name + getExtension("PlotRaw")))
				continue;

			std::ofstream of;
			of.open(tmp_root + plotInfo[i].GeneratePlotFileName("PlotRaw") + ".plt", std::ios::trunc);

			if ((*Setting)["PlotRaw"]["Terminal"] == "png")
				of << "set term png enhanced transparent truecolor font arial 11 size "
				<< plotInfo[i].terminal_size.str() << std::endl;
			if ((*Setting)["PlotRaw"]["Terminal"] == "svg")
				of << R"(set term svg size )" << plotInfo[i].terminal_size.str()
				<< R"( enhanced font "Arial, 11")" << std::endl;
			of << "set out \"" << clx::replace_all_copy(tmp_root, "\\", "\\\\")
				<< plotInfo[i].out_file_name << getExtension("PlotRaw")<<"\"" << std::endl;
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

			std::system(((std::string)"gnuplot " + tmp_root + plotInfo[i].plot_file_name + ".plt").c_str());
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

	void MakeHTML(std::string html_path)
	{
		std::ofstream of;
		of.open(html_path, std::ios::trunc);
		of << R"(
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<HTML>
<HEAD> 
<META http-equiv="Content-Type" content="text/html; charset=Shift_JIS">
<TITLE></TITLE>
</HEAD>
<BODY>
)" << std::endl;
		for (const auto& iter : plotInfo) {
			std::string img_src;
			img_src = R"(<img src="$imgFileName" alt="$imgAlt">)";
			clx::replace_all(img_src, "$imgFileName"_s, iter.plot_file_name + getExtension("PlotRaw"));
			clx::replace_all(img_src, "$imgAlt"_s, iter.plot_file_name);
			clx::replace_all(img_src, "#"_s, "%23"_s);
			of << img_src << std::endl;
		}
		std::chrono::system_clock::time_point p = std::chrono::system_clock::now();
		std::time_t t = std::chrono::system_clock::to_time_t(p);
		const std::tm* lt = std::localtime(&t);
		const std::tm gt = thisShot->GetTime(thisShot->GetADCID(plotInfo[0].data_index));
		of << R"(<BR><BR><HR>)" << std::endl;
		of << "Shot date : " << std::put_time(&gt, "%c") << "　　　　" << std::endl;
		of << "Last modified : " << std::put_time(lt, "%c") << "" << std::endl;
		of << R"(
</BODY>
</HTML>
)" << std::endl;
	}

};

#endif
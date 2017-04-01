#include "tkadc.h"
#include "tkadcinfo.h"
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
#ifndef __TKSHOTINFO__
#define __TKSHOTINFO__

//#define TKSI_ADC_MAX 
class TKDATA
{
private:
	TKADCINFO::ADCID adc_id;

	std::string data_file_name;

	int trace_total_number;

	std::string model_name;
	struct CHDATA {
		int ch_number;
		std::string trace_name;
		float v_resolution;
		float v_offset;
		float h_resolution;
		float h_offset;
		int block_size;
		struct std::tm time;
	};
	std::vector<TKDATA::CHDATA> CHData;
//	TKDATA::CHDATA CHData[TKADC_ADC_CHANNEL_MAX];
	int channel_number_to_trace_number[TKADC_ADC_CHANNEL_MAX];

	inline void readHDRLineString(std::string buf, int trace_number, char* key_name, std::string* odata);
	template<typename T> int readHDRLine(std::string buf, int trace_number, char* key_name, T* data);
	template<> int readHDRLine(std::string buf, int trace_number, char* key_name, float* data);
	template<> int readHDRLine(std::string buf, int trace_number, char* key_name, int* data);
	template<> int readHDRLine(std::string buf, int trace_number, char* key_name, struct std::tm* data);
	int traceNameToCHNumber(std::string trace_name);

public:
	TKDATA()
	{
		for (int i = 0; i < TKADC_ADC_CHANNEL_MAX; i++)
			channel_number_to_trace_number[i] = -1;
	}
	int ParseHDR();
	int SetADCID(TKADCINFO::ADCID iadc_id)
	{
		adc_id = iadc_id;
		return 0;
	}
	TKADCINFO::ADCID GetADCID()
	{
		return adc_id;
	}
	int SetDataFileName(std::string idata_file_name)
	{
		data_file_name = idata_file_name;
		return 0;
	}
	std::string GetDataFileName()
	{
		return data_file_name;
	}
		float GetHResolution()
	{
		return CHData[0].h_resolution;
	}
	int GetBlockSize()
	{
		return CHData[0].block_size;
	}
	float GetHOffset()
	{
		return CHData[0].h_offset;
	}
	std::string GetModelName()
	{
		return model_name;
	}
	int GetTraceTotalNumber()
	{
		return trace_total_number;
	}
	int ChannnelNumberToTraceNumber(int channel_number)
	{
		return channel_number_to_trace_number[channel_number];
	}
	int GetChannelNumber(int trace_index)
	{
		return CHData[trace_index].ch_number;
	}


};

class TKSHOT
{
private:
	int shot_number;
	bool is_current_shot;

	int adc_num = 0;
	std::vector<TKDATA> TKData;
//	TKDATA TKData[2];

	int plot_num;
//	std::vector<TKPLOT> TKPlot;


	int getADCDataIndexByADCID(TKADCINFO::ADCID adc_id)
	{
		for (int i = 0; i < adc_num; i++)
			if (TKData[i].GetADCID() == adc_id)
				return i;
		return -1;
	}

public:
	TKSHOT()
	{
		/*int ishot_num
		adc_num = 0;
		shot_number = ishot_num;
		if (ishot_num == -1) {
			//ショット番号なしカレントショット
			is_current_shot = true;
		}
		else {
			//ショット番号有保存済みショット
			is_current_shot = false;

		}
		*/

	}
	~TKSHOT()
	{

	}

	int GetADCNumber()
	{
		return adc_num;
	}
	std::string GetDataFileName(TKADCINFO::ADCID adc_id)
	{
		return TKData[getADCDataIndexByADCID(adc_id)].GetDataFileName();
	}

	int NameShotNumber(int ishot_number)
	{
		shot_number = ishot_number;
		return 0;
	}
	int AppendDataFile(TKADCINFO::ADCID adc_id, std::string data_file_name)
	{
		
		TKDATA *this_data;
		adc_num++;
	TKData.push_back(TKDATA());
		this_data = &(TKData[adc_num - 1]);
		this_data->SetADCID(adc_id);
		this_data->SetDataFileName(data_file_name);
		this_data->ParseHDR();
		return 0;
		adc_num++;
		TKData.push_back(TKDATA::TKDATA());
//		TKData.resize(16);
		TKData[adc_num - 1].SetADCID(adc_id);
		TKData[adc_num - 1].SetDataFileName(data_file_name);
		TKData[adc_num - 1].ParseHDR();
		return 0;
	}
	float GetHResolution(TKADCINFO::ADCID adc_id)
	{
		return TKData[getADCDataIndexByADCID(adc_id)].GetHResolution();
	}
	int GetBlockSize(TKADCINFO::ADCID adc_id)
	{
		return TKData[getADCDataIndexByADCID(adc_id)].GetBlockSize();
	}
	float GetHOffset(TKADCINFO::ADCID adc_id)
	{
		return TKData[getADCDataIndexByADCID(adc_id)].GetHOffset();
	}
	std::string GetModelName(TKADCINFO::ADCID adc_id)
	{
		return TKData[getADCDataIndexByADCID(adc_id)].GetModelName();
	}
	int GetTraceTotalNumber(TKADCINFO::ADCID adc_id)
	{
		return TKData[getADCDataIndexByADCID(adc_id)].GetTraceTotalNumber();
	}
	int ADCIDToADCDataIndex(TKADCINFO::ADCID adc_id)
	{
		return getADCDataIndexByADCID(adc_id);
	}
	TKADCINFO::ADCID GetADCID(int adc_index)
	{
		return TKData[adc_index].GetADCID();
	}
	int GetChannelNumber(TKADCINFO::ADCID adc_id, int trace_index)
	{
		return TKData[getADCDataIndexByADCID(adc_id)].GetChannelNumber(trace_index);
	}
};


class TKPLOT
{
private:
	TKSHOT* TKShot;
public:
	TKPLOT(TKSHOT* TKShot_)
	{
		TKShot = TKShot_;
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
		of << "plot \"" << TKShot->GetDataFileName(TKADCINFO_ADC_ID_DL750) << ".CSV\""
			<< " every 10"
			<< " using (" << TKShot->GetHOffset(TKADCINFO_ADC_ID_DL750) << " + (column(0)) * 10 * " << TKShot->GetHResolution(TKADCINFO_ADC_ID_DL750) << "):7"
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
	int PlotRaw(std::vector<std::string> &oplot_file_name)
	{
		int total_plot = 0;
		for (int data_index = 0; data_index < TKShot->GetADCNumber(); data_index++) {
			for (int trace_index = 0; trace_index < TKShot->GetTraceTotalNumber(TKShot->GetADCID(data_index)); trace_index++) {
				std::ofstream of;
				std::string plot_file_name;
				plot_file_name = "PlotRaw_" + TKShot->GetModelName(TKShot->GetADCID(data_index)) + "_CH" + std::to_string(TKShot->GetChannelNumber(TKShot->GetADCID(data_index), trace_index));
				of.open(plot_file_name + ".plt", std::ios::trunc);
//				of << "set term png enhanced transparent truecolor font arial 11 size 600, 300" << std::endl;
				of << "set term png enhanced transparent truecolor font arial 11 size 400, 200" << std::endl;
				of << "set out \"" << plot_file_name << ".png\"" << std::endl;
				//	of << "plot using " << std::endl;
				of << "set datafile separator \',\'" << std::endl;
				of << "set grid xtics ytics" << std::endl;
				of << "set nokey" << std::endl;
				of << "set multiplot " << std::endl;
//				of << "set origin 0.15, 0.2" << std::endl;
//				of << "set size 0.7, 0.7" << std::endl;
				of << "set origin 0.2, 0.25" << std::endl;
				of << "set size 0.75, 0.65" << std::endl;
				of << "set lmargin 0" << std::endl;
				of << "set rmargin 0" << std::endl;
				of << "set tmargin 0" << std::endl;
				of << "set bmargin 0" << std::endl;
//				of << "set label 2 left at graph 0,1.05 \""
					of << "set label 2 left at graph 0,1.06 \""
					<< "CH" << std::to_string(TKShot->GetChannelNumber(TKShot->GetADCID(data_index), trace_index))
					<< " - " << TKShot->GetModelName(TKShot->GetADCID(data_index))
					<< "\"" << std::endl;
//				of << "set label 3 right at graph 1,1.05 \""
					of << "set label 3 right at graph 1,1.06 \""
					<< "#" << std::to_string(0)
					<< "\"" << std::endl;
				of << "set yrange [*<0:0<*]" << std::endl;
//				of << "set xlabel \"Time [s]\"" << std::endl;
//				of << "set ylabel \"Voltage [V]\"" << std::endl;
				of << "set format y \"%1.1tE%+-T\"" << std::endl;
				of << "set label 10 center at graph 0.5, -0.3 \"Time [s]\"" << std::endl;
				of << "set label 11 center at graph -0.23, 0.5 rotate \"Voltage [V]\"" << std::endl;
				of << "set xrange ["
					<< TKShot->GetHOffset(TKShot->GetADCID(data_index))
					<< ":"
					<< (TKShot->GetHOffset(TKShot->GetADCID(data_index)) + TKShot->GetHResolution(TKShot->GetADCID(data_index)) * TKShot->GetBlockSize(TKShot->GetADCID(data_index)))
					<< "]"
					<< std::endl;
				of << "plot \"" << TKShot->GetDataFileName(TKShot->GetADCID(data_index)) << ".CSV\""
					<< " every 10"
					<< " using (" << TKShot->GetHOffset(TKShot->GetADCID(data_index)) << " + (column(0)) * 10 * " << TKShot->GetHResolution(TKShot->GetADCID(data_index)) << ")"
					<< ":" << std::to_string(trace_index + 1)
					<< " with line"
					<< std::endl;
				of << "" << std::endl;

				std::system(((std::string)"gnuplot " + plot_file_name + ".plt").c_str());
				oplot_file_name.push_back(plot_file_name.c_str());
				total_plot++;
			}
		}
		return total_plot;
	}

};

#endif
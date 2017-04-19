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

#define NATIVE_ENDIAN TKDATA::BYTEORDER::LITTLE_ENDIAN


//#define TKSI_ADC_MAX 
class TKDATA
{
public:
	const enum class BYTEORDER
	{
		BIG_ENDIAN,// 680xx
		LITTLE_ENDIAN// 80x86
	};
	const enum class DATAFORMAT
	{
		TRACE,
		BLOCK
	};

private:
	int adc_id;

	std::string data_file_name;

	int trace_total_number;

	std::string model_name;
	BYTEORDER byte_order;
	DATAFORMAT data_format;
	int data_offset;

	struct CHDATA
	{
		int ch_number;
		std::string trace_name;
		float v_resolution;
		float v_offset;
		int v_max_data;
		int v_min_data;
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
	int SetADCID(int iadc_id)
	{
		adc_id = iadc_id;
		return 0;
	}
	int GetADCID()
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
	float GetVOffset(int const trace_index)
	{
		return CHData[trace_index].v_offset;
	}
	float GetVResolution(int const trace_index)
	{
		return CHData[trace_index].v_resolution;
	}
	int GetVMaxData(int const trace_index)
	{
		return CHData[trace_index].v_max_data;
	}
	int GetVMinData(int const trace_index)
	{
		return CHData[trace_index].v_min_data;
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
	TKDATA::BYTEORDER GetByteOrder()
	{
		return byte_order;
	}
	TKDATA::DATAFORMAT GetDataFormat()
	{
		return data_format;
	}
	int GetDataOffset()
	{
		return data_offset;
	}
	int GetTraceTotalNumber()
	{
		return trace_total_number;
	}
	int ChannnelNumberToTraceNumber(int const channel_number)
	{
		return channel_number_to_trace_number[channel_number];
	}
	int GetChannelNumber(int const trace_index)
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


	int getADCDataIndexByADCID(int adc_id)
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
		this->Clear();
	}
	~TKSHOT()
	{

	}

	int GetADCNumber()
	{
		return adc_num;
	}
	std::string GetDataFileName(int adc_id)
	{
		return TKData[getADCDataIndexByADCID(adc_id)].GetDataFileName();
	}

	int NameShotNumber(int ishot_number)
	{
		shot_number = ishot_number;
		return 0;
	}
	int Clear()
	{
		adc_num = 0;
		TKData.clear();
		return 0;
	}
	int AppendDataFile(std::string data_file_name)
	{

		TKDATA *this_data;
		adc_num++;
		TKData.push_back(TKDATA());
		this_data = &(TKData[adc_num - 1]);
		this_data->SetADCID(adc_num-1);
		this_data->SetDataFileName(data_file_name);
		this_data->ParseHDR();
		return adc_num-1;
		/*
		adc_num++;
		TKData.push_back(TKDATA::TKDATA());
		TKData[adc_num - 1].SetADCID(adc_id);
		TKData[adc_num - 1].SetDataFileName(data_file_name);
		TKData[adc_num - 1].ParseHDR();
		return 0;
		*/
	}
	float GetHResolution(int adc_id)
	{
		return TKData[getADCDataIndexByADCID(adc_id)].GetHResolution();
	}
	int GetBlockSize(int adc_id)
	{
		return TKData[getADCDataIndexByADCID(adc_id)].GetBlockSize();
	}
	float GetVOffset(int adc_id, int trace_index)
	{
		return TKData[getADCDataIndexByADCID(adc_id)].GetVOffset(trace_index);
	}
	float GetVResolution(int adc_id, int trace_index)
	{
		return TKData[getADCDataIndexByADCID(adc_id)].GetVResolution(trace_index);
	}
	int GetVMaxData(int adc_id, int trace_index)
	{
		return TKData[getADCDataIndexByADCID(adc_id)].GetVMaxData(trace_index);
	}
	int GetVMinData(int adc_id, int trace_index)
	{
		return TKData[getADCDataIndexByADCID(adc_id)].GetVMinData(trace_index);
	}
	float GetHOffset(int adc_id)
	{
		return TKData[getADCDataIndexByADCID(adc_id)].GetHOffset();
	}
	std::string GetModelName(int adc_id)
	{
		return TKData[getADCDataIndexByADCID(adc_id)].GetModelName();
	}
	TKDATA::BYTEORDER GetByteOrder(int adc_id)
	{
		return TKData[getADCDataIndexByADCID(adc_id)].GetByteOrder();
	}
	TKDATA::DATAFORMAT GetDataFormat(int adc_id)
	{
		return TKData[getADCDataIndexByADCID(adc_id)].GetDataFormat();
	}
	int GetDataOffset(int adc_id)
	{
		return TKData[getADCDataIndexByADCID(adc_id)].GetDataOffset();
	}
	int GetTraceTotalNumber(int adc_id)
	{
		return TKData[getADCDataIndexByADCID(adc_id)].GetTraceTotalNumber();
	}
	int ADCIDToADCDataIndex(int adc_id)
	{
		return getADCDataIndexByADCID(adc_id);
	}
	int GetADCID(int adc_index)
	{
		return TKData[adc_index].GetADCID();
	}
	int GetChannelNumber(int adc_id, int trace_index)
	{
		return TKData[getADCDataIndexByADCID(adc_id)].GetChannelNumber(trace_index);
	}
};


#endif
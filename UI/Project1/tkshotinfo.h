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

	struct CHDATA {
		std::string trace_name;
		float v_resolution;
		float v_offset;
		float h_resolution;
		float h_offset;
		struct std::tm time;
	};
	std::vector<TKDATA::CHDATA> CHData;

	inline void readHDRLineString(std::string buf, int trace_number, char* key_name, std::string* odata)
	{
		char data[4][256];
		switch (trace_number) {
		case 1:
			sscanf(buf.c_str(), "%s %s", key_name, &(data[0]));
			break;
		case 2:
			sscanf(buf.c_str(), "%s %s %s", key_name, &(data[0]), &(data[1]));
			break;
		case 3:
			sscanf(buf.c_str(), "%s %s %s %s", key_name, &(data[0]), &(data[1]), &(data[2]));
			break;
		case 4:
			sscanf(buf.c_str(), "%s %s %s %s %s", key_name, &(data[0]), &(data[1]), &(data[2]), &(data[3]));
			break;
		}
		for (int i = 0; i < trace_number; i++)
			odata[i] = (std::string)data[i];
	}
	template<typename T> int readHDRLine(std::string buf, int trace_number, char* key_name, T* data)
	{
		readHDRLineString(buf, trace_number, key_name, data);
		return 0;
	}
	template<> int readHDRLine(std::string buf, int trace_number, char* key_name, float* data)
	{
		std::string idata[4];
		readHDRLineString(buf, trace_number, key_name, idata);
		for (int i = 0; i < trace_number; i++)
			data[i] = std::stof(idata[i], NULL);
		return 0;
	}
	template<> int readHDRLine(std::string buf, int trace_number, char* key_name, int* data)
	{
		std::string idata[4];
		readHDRLineString(buf, trace_number, key_name, idata);
		for (int i = 0; i < trace_number; i++)
			data[i] = std::stoi(idata[i], NULL, 10);
		return 0;
	}
	template<> int readHDRLine(std::string buf, int trace_number, char* key_name, struct std::tm* data)
	{
		std::string idata[4];
		readHDRLineString(buf, trace_number, key_name, idata);
		for (int i = 0; i < trace_number; i++, data) {
			std::stringstream ss;
			std::string ibuf;
			ss << idata[i];
			if ((std::string)key_name == "Date") {
				std::getline(ss, ibuf, '/');
				(data + i)->tm_year = std::stoi(ibuf) - 1900;
				std::getline(ss, ibuf, '/');
				(data + i)->tm_mon = std::stoi(ibuf) - 1;
				std::getline(ss, ibuf, '/');
				(data + i)->tm_mday = std::stoi(ibuf);
			} else if ((std::string)key_name == "Time") {
				std::getline(ss, ibuf, ':');
				(data + i)->tm_hour = std::stoi(ibuf);
				std::getline(ss, ibuf, ':');
				(data + i)->tm_min = std::stoi(ibuf);
				std::getline(ss, ibuf, ':');
				(data + i)->tm_sec = (int)std::stof(ibuf);
			} else {
				return -1;
			}
		}
		return 0;
	}

public:
	int ParseHDR()
	{
		std::ifstream ifs(data_file_name + ".HDR");
		std::string buf;
		for (int lines = 1, current_trace_number = 0; std::getline(ifs, buf); lines++) {
			int group_number;
			int trace_number;
			char key_name[64];
			int idata[4];
			float fdata[4];
			std::string sdata[4];
			char cdata[4][64];
			struct std::tm tmdata[4];

			switch (lines) {
				
			//GroupNumber
			case 8:
				readHDRLine(buf, 1, key_name, idata);
				group_number = idata[0];
				break;
		
			//TraceTotalNumber
			case 9:
				readHDRLine(buf, 1, key_name, idata);
				trace_total_number = idata[0];
				break;

			//TraceNumber
			case 13:
			case 33:
			case 53:
			case 73:
				readHDRLine(buf, 1, key_name, idata);
				trace_number = idata[0];
				break;

			//TraceName
			case 15:
			case 35:
			case 55:
			case 75:
				for (int i = 0; i < trace_number; i++)
					CHData.push_back(TKDATA::CHDATA());
				readHDRLine(buf, trace_number, key_name, sdata);
				for (int i = 0; i < trace_number; i++)
					CHData[i].trace_name = sdata[i];
				current_trace_number += trace_number;
				break;

			//HResolution
			case 26:
			case 46:
			case 66:
			case 86:
				readHDRLine(buf, trace_number, key_name, fdata);
				for (int i = 0; i < trace_number; i++)
					CHData[i].h_resolution = fdata[i];
				break;

			//HOffset
			case 27:
			case 47:
			case 67:
			case 87:
				readHDRLine(buf, trace_number, key_name, fdata);
				for (int i = 0; i < trace_number; i++)
					CHData[i].h_offset = fdata[i];
				break;

			//Date
			case 29:
			case 49:
			case 69:
			case 89:
			//Time
			case 30:
			case 50:
			case 70:
			case 90:
				readHDRLine(buf, trace_number, key_name, tmdata);
				for (int i = 0; i < trace_number; i++)
					CHData[i].time = tmdata[i];
				break;
			}
		}
		return 0;
	}
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
	float GetHOffset()
	{
		return CHData[0].h_offset;
	}


};

class TKPLOT
{
private:
public:

};

class TKSHOT
{
private:
	int shot_number;
	bool is_current_shot;

	int adc_num;
	std::vector<TKDATA> TKData;

	int plot_num;
	std::vector<TKPLOT> TKPlot;


	int getADCDataIndexByADCID(TKADCINFO::ADCID adc_id)
	{
		for (int i = 0; i < adc_num; i++)
			if (TKData[i].GetADCID() == adc_id)
				return i;
		return -1;
	}

public:
	TKSHOT(int ishot_num)
	{
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
	}
	~TKSHOT()
	{

	}

	int GetADCNumber()
	{
		return adc_num;
	}
	std::string GetShotDataFileName(TKADCINFO::ADCID adc_id)
	{
		return TKData[getADCDataIndexByADCID(adc_id)].GetDataFileName();
	}

	int NameShotNumber(int ishot_number)
	{
		shot_number = ishot_number;
		return 0;
	}
	int AppendShotDataFile(TKADCINFO::ADCID adc_id, std::string data_file_name)
	{
		TKDATA *this_data;
		adc_num++;
		TKData.push_back(TKDATA());
		this_data = &(TKData[adc_num - 1]);
		this_data->SetADCID(adc_id);
		this_data->SetDataFileName(data_file_name);
		this_data->ParseHDR();
		return 0;
	}
	float GetHResolution(TKADCINFO::ADCID adc_id)
	{
		return TKData[getADCDataIndexByADCID(adc_id)].GetHResolution();
	}
	float GetHOffset(TKADCINFO::ADCID adc_id)
	{
		return TKData[getADCDataIndexByADCID(adc_id)].GetHOffset();
	}
};


#endif
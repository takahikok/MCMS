#include "tkadc.h"
#include "tkadcinfo.h"
#include <vector>
#include <string>
#include <iostream>

#ifndef __TKSHOTINFO__
#define __TKSHOTINFO__

//#define TKSI_ADC_MAX 
class TKDATA
{
private:
	TKADCINFO::ADCID adc_id;

	std::string data_file_name;

public:
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


};

class TKSHOT
{
private:
	int shot_number;
	bool is_current_shot;

	int adc_num;
	std::vector<TKDATA> TKData;

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
		return 0;
	}
};


#endif
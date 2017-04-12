#include <string>
#include <iostream>
#include "tmctl.h"

#ifndef __TKADC__
#define __TKADC__

//#define DEVICE_MAX 2
#define TKADC_ADC_MODEL_DL750 TKADC::ADCModel::ADCTypeDL750
#define TKADC_ADC_MODEL_DL850 TKADC::ADCModel::ADCTypeDL850
#define TKADC_ADC_CHANNEL_MAX 18
class TKADC
{
public:
	const enum class ADCModel
	{
		ADCTypeDL750,
		ADCTypeDL850
	};
	virtual const enum class ConditionFlag
	{
		ALL = 0xffff
	};

public:
	TKADC(ADCModel adcmodel);
	~TKADC();
	ADCModel Model();
	int Open(int wire_type_, const char* adress_);
	int Close();
	int SendMessage(const char* message);
	int Start();
	int Stop();
	int WaitADC();
	int WaitADC(TKADC::ConditionFlag flag);
	int WaitADC2();
	int SaveShot(std::string file_name);

/*	void BeginThread();
	void TermThread();
	bool m_run;
	HANDLE m_hThread;
	DWORD m_dwThrdAddr;
	*/
	int GetDeviceID();

	virtual int GetStatusCondition(TKADC::ConditionFlag flag);
	virtual int Delete(std::string file_name);

public:
	//local shot number 
	int GetLastLocalShotNumber();
	int GetNextLocalShotNumber();
	int SetLastLocalShotNumber(int new_local_shot_number);
	int IncrementLocalShotNumber();
	int SetLocalShotNumberMax(int new_local_shot_number_max);
	int GetLocalShotNumberMax();


protected:
private:
	ADCModel adc_model;
	int device_id;
	int wire_type;
	char adress[256];
	char name[256];
	char file_name_header[32];
	char file_path[32];
	int next_local_shot_number;
	int local_shot_number_max = 99999999;

};

struct DEVICE {
	int device_id;
	int wire_type;
	char adress[256];
	char name[256];
	char file_name_header[32];
	char file_path[32];
};

class TKADC_DL750 : public TKADC {
public:

	//The condition flag is depending on the ADC model.
	//Details are described in the YOKOGAWA IM701210-18 document.

	const enum class ConditionFlag
	{
		ALL = 0xffff,	//16bit
		RUN = 1 << 0,	//Running
		TRG = 1 << 2,	//Awaiting trigger
		TRGINV = ALL - TRG,
		CAL = 1 << 3,	//Calibration
		TST = 1 << 4,	//Testing
		PRN = 1 << 5,	//Printing
		ACS = 1 << 6,	//Accessing
		MES = 1 << 7,	//Measuring
		HST = 1 << 8,	//History Search
		SUP = 1 << 9,	//Setup
		NGO = 1 << 10,	//Go/No-Go
		SCH = 1 << 11,	//Search
		NSS = 1 << 12,	//N-Single
		INI = 1 << 13,	//Initializing
		FFT = 1 << 14,	//FFT
	};

public:
	TKADC_DL750();
	int TKADC_DL750::GetStatusCondition(TKADC_DL750::ConditionFlag flag);
	int Delete(std::string file_name);
};

class TKADC_DL850 : public TKADC {
public:

	//The condition flag is depending on the ADC model.
	//Details are described in the YOKOGAWA IMDL850E-17 document.

	const enum class ConditionFlag
	{
		ALL = 0xffff,	//16bit
		CAP = 1 << 0,	//Capture
		REC = 1 << 1,	//Record
		TRG = 1 << 2,	//Awaiting trigger
		TRGINV = ALL - TRG,
		CAL = 1 << 3,	//Calibration
		TST = 1 << 4,	//Testing
		PRN = 1 << 5,	//Printing
		ACS = 1 << 6,	//Accessing
		MES = 1 << 7,	//Measuring
		HST = 1 << 8,	//History Search
		CNT = 1 << 9,	//CONection
		NGO = 1 << 10,	//Go/No-Go
		SCH = 1 << 11,	//Search
		RUN = 1 << 12,	//Running
		KLK = 1 << 13,	//Key lock
		AN  = 1 << 14	//Analysis
	};

public:
	TKADC_DL850();
	int TKADC_DL850::GetStatusCondition(TKADC_DL850::ConditionFlag flag);
	int Delete(std::string file_name);
};

#endif
#include <string>
#include <iostream>
#include "tmctl.h"

#include <Windows.h>
#include <WinBase.h>

#ifndef __TKADC__
#define __TKADC__

//#define DEVICE_MAX 2
#define TKADC_ADC_TYPE_DL750 TKADC::ADCType::ADCTypeDL750
#define TKADC_ADC_TYPE_DL850 TKADC::ADCType::ADCTypeDL850

class TKADC
{
public:
	TKADC();
	~TKADC();
	int Open(int wire_type_, const char* adress_);
	int Close();
	int SendMessage(const char* message);
	int Start();
	int Stop();
	int WaitADC();
	int WaitADC2();
	int SaveShot(std::string file_name);

	void BeginThread();
	void TermThread();
	bool m_run;
	HANDLE m_hThread;
	DWORD m_dwThrdAddr;
	int GetDeviceID();

	//local shot number 
	int GetLastLocalShotNumber();
	int GetNextLocalShotNumber();
	int SetLastLocalShotNumber(int new_local_shot_number);
	int IncrementLocalShotNumber();
	int SetLocalShotNumberMax(int new_local_shot_number_max);
	int GetLocalShotNumberMax();

	enum class ADCType
	{
		ADCTypeDL750,
		ADCTypeDL850
	};


private:
	int device_id;
	int wire_type;
	char adress[256];
	char name[256];
	char file_name_header[32];
	char file_path[32];
//	DWORD WINAPI EventFunc(LPVOID pContext);
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

#if 0
int TKLoadDeviceSettings(struct DEVICE *device);
int TKADCOpenADC(struct DEVICE *device);
int TKADCCloseADC(struct DEVICE *device);
int TKADCInitADC(struct DEVICE *device);
int TKADCStartADC(struct DEVICE *device);
int TKADCManualTrigger(struct DEVICE *device);
int TKADCWaitADC(struct DEVICE *device);
int TKADCSaveShot(struct DEVICE *device, const char* file_name);
#endif
#endif
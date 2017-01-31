#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tmctl.h"

#ifndef __TKADC__
#define __TKADC__

#define DEVICE_MAX 2

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
private:
	int device_id;
	int wire_type;
	char adress[256];
	char name[256];
	char file_name_header[32];
	char file_path[32];

};

struct DEVICE {
	int device_id;
	int wire_type;
	char adress[256];
	char name[256];
	char file_name_header[32];
	char file_path[32];
};

int TKLoadDeviceSettings(struct DEVICE *device);
int TKADCOpenADC(struct DEVICE *device);
int TKADCCloseADC(struct DEVICE *device);
int TKADCInitADC(struct DEVICE *device);
int TKADCStartADC(struct DEVICE *device);
int TKADCManualTrigger(struct DEVICE *device);
int TKADCWaitADC(struct DEVICE *device);
int TKADCSaveShot(struct DEVICE *device, const char* file_name);

#endif
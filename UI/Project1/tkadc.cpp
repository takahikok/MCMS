#include "tkadc.h"
#include <string.h>  


TKADC::TKADC()
{
}

TKADC::~TKADC()
{
}

int TKADC::Open(int wire_type_, const char* adress_)
{
	// DL750.Open(TM_CTL_ETHER,  "10.240.58.184,anonymous,");
	// DL850.Open(TM_CTL_VXI11, "10.240.58.244");
	wire_type = wire_type_;
	strcpy(adress, adress_);
	if (TmcInitialize(wire_type, adress, &device_id))
		return TmcGetLastError(device_id);
	return 0;
}

int TKADC::Close()
{
	if (TmcFinish(device_id))
		return TmcGetLastError(device_id);
	return 0;
}

int TKADC::SendMessage(const char* message)
{
	if (TmcSend(device_id, (char*)message))
		return TmcGetLastError(device_id);
	else
		return 0;
}

int TKADC::Start()
{
	return this->SendMessage(":start");
}
int TKADC::Stop()
{
	return this->SendMessage(":stop");
}



int TKLoadDeviceSettings(struct DEVICE *device)
{
	static int i;

	for (i = 0; i < DEVICE_MAX; i++) {
		switch (i) {
		case 0:
			((device + i) + i)->wire_type = TM_CTL_VXI11;
			strcpy_s((device + i)->adress, "10.240.58.244");
			strcpy_s((device + i)->name, "DL850");
			strcpy_s((device + i)->file_name_header, "D8A");
			strcpy_s((device + i)->file_path, "HD, 0");
			break;
		case 1:
			(device + i)->wire_type = TM_CTL_ETHER;
			strcpy_s((device + i)->adress, "10.240.58.184,anonymous,");
			strcpy_s((device + i)->name, "701210");
			strcpy_s((device + i)->file_name_header, "D7A");
			strcpy_s((device + i)->file_path, "HD-0");
			break;
		}
	}
	return 0;
}


int TKADCOpenADC(struct DEVICE *device)
{
	if (TmcInitialize(device->wire_type, device->adress, &device->device_id))
		return TmcGetLastError(device->device_id);
	return 0;
}

int TKADCCloseADC(struct DEVICE *device)
{
	if (TmcFinish(device->device_id))
		goto error;
	return 0;
error:
	return TmcGetLastError(device->device_id);
}

int TKADCInitADC(struct DEVICE *device)
{
	char send_msg[1024];
	char rcv_msg[1024];
	int rcv_length;
	char* next_token;

	if (TmcSend(device->device_id, "*IDN?"))
		goto error;
	if (TmcReceive(device->device_id, rcv_msg, sizeof(rcv_msg), &rcv_length))
		goto error;
	strcpy_s(device->name, strtok_s(rcv_msg, ",", &next_token));

	if (TmcSend(device->device_id, ":trigger:mode single"))
		goto error;
	if (TmcSend(device->device_id, ":trigger:out:type 1"))
		goto error;
	return 0;
error:
	return TmcGetLastError(device->device_id);
}

int TKADCStartADC(struct DEVICE *device)
{
	if (TmcSend(device->device_id, ":start"))
		goto error;
	return 0;
error:
	return TmcGetLastError(device->device_id);
}

int TKADCManualTrigger(struct DEVICE *device)
{
	if (TmcSend(device->device_id, ":mtrigger"))
		goto error;
	return 0;
error:
	return TmcGetLastError(device->device_id);
}


int TKADCWaitADC(struct DEVICE *device)
{
	char send_msg[1024];
	char rcv_msg[1024];
	int rcv_length;

	printf("[%s] Busy\n", device->name);
	for (;;) {
		int condition;
		char* stop_str;

		if (TmcSend(device->device_id, ":status:condition?"))
			goto error;
		if (TmcReceive(device->device_id, rcv_msg, sizeof(rcv_msg), &rcv_length))
			goto error;
		condition = strtol(rcv_msg, &stop_str, 10);
		if (!condition)
			break;
	}
	return 0;
error:
	return TmcGetLastError(device->device_id);
}

int TKADCSaveShot(struct DEVICE *device, const char* file_name)
{
	char send_msg[1024];
	char rcv_msg[1024];
	int rcv_length;

	sprintf_s(send_msg, ":file:save:name \"%s\"", file_name);
	printf("%s\n", send_msg);
	if (TmcSend(device->device_id, send_msg))
		goto error;
	if (TmcSend(device->device_id, ":file:save:binary"))
		goto error;
	return 0;
error:
	return TmcGetLastError(device->device_id);
}


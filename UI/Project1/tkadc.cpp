#include "tkadc.h"
#include <string>  
//#include <Windows.h>


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

int TKADC::WaitADC2()
{
	return 0;
}

int TKADC::WaitADC()
{
	char send_msg[1024];
	char rcv_msg[1024];
	int rcv_length;
	MSG msg;

//	printf("[%s] Busy\n", device->name);
	for (;;) {
		int condition;
		
		if (TmcSend(device_id, ":status:condition?"))
			goto error;
		if (TmcReceive(device_id, rcv_msg, sizeof(rcv_msg), &rcv_length))
			goto error;
		condition = std::stol((std::string)rcv_msg);
		if (!condition)
			break;
//		GetMessage(&msg, NULL, 0, 0);
//		TranslateMessage(&msg);
//		DispatchMessage(&msg);
		Sleep(1);
		System::Windows::Forms::Application::DoEvents();
	}
	return 0;
error:
	return TmcGetLastError(device_id);
}
int TKADC::GetDeviceID(void)
{
	return this->device_id;
}

int TKADC::SaveShot(std:: string file_name)
{
	std::string send_msg;
	char rcv_msg[1024];
	int rcv_length;

	send_msg = (std::string)":file:save:name \"" + file_name + "\"";
//	sprintf_s(send_msg, ":file:save:name \"%s\"", file_name);
//	printf("%s\n", send_msg);
	if (TmcSend(device_id, (char*)send_msg.c_str()))
		goto error;
	if (TmcSend(device_id, ":file:save:binary"))
		goto error;
	return 0;
error:
	return TmcGetLastError(device_id);
}

#if 0

DWORD WINAPI EventFunc(LPVOID pContext)
{
	TKADC* pThread = (TKADC*)pContext;
	int i;
	char send_msg[1024];
	char rcv_msg[1024];
	int rcv_length;

	for (;;) {
		int condition;

		if (TmcSend(pThread->GetDeviceID(), ":status:condition?"))
			goto error;
		if (TmcReceive(pThread->GetDeviceID(), rcv_msg, sizeof(rcv_msg), &rcv_length))
			goto error;
		condition = std::stol((std::string)rcv_msg);
		if (!condition)
			break;
		Sleep(0);
	}
	return 0;
error:
	return TmcGetLastError(pThread->GetDeviceID());
}

void TKADC::BeginThread(void)
{
	m_run = TRUE;
	m_hThread = CreateThread(NULL, 0, EventFunc, this, 0, &m_dwThrdAddr);
}
void TKADC::TermThread(void)
{
	m_run = FALSE;
	WaitForSingleObject(m_hThread, 3000);
	CloseHandle(m_hThread);
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
#endif
int TKADC::GetLastLocalShotNumber()
{
	return next_local_shot_number - 1;
}

int TKADC::GetNextLocalShotNumber()
{
	return next_local_shot_number;
}

int TKADC::SetLastLocalShotNumber(int new_local_shot_number)
{
	return next_local_shot_number = new_local_shot_number + 1;
}

int TKADC::IncrementLocalShotNumber()
{
	next_local_shot_number++;
	if (next_local_shot_number > local_shot_number_max)
		next_local_shot_number = 1;
	return next_local_shot_number;
}

int TKADC::SetLocalShotNumberMax(int new_local_shot_number_max)
{
	return local_shot_number_max = new_local_shot_number_max;
}

int TKADC::GetLocalShotNumberMax()
{
	return local_shot_number_max;
}


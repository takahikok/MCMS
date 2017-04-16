#include "tkadc.h"
#include <string>  


TKADC::TKADC(ADCModel adcmodel)
{
	adc_model = adcmodel;
}

TKADC::~TKADC()
{
}

TKADC::ADCModel TKADC::Model()
{
	return adc_model;
}

int TKADC::Open(int wire_type_, const char* adress_)
{
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



int TKADC::WaitADC()
{
	char rcv_msg[1024];
	int rcv_length;

	for (;;) {
		int condition;

		if (TmcSend(device_id, ":status:condition?"))
			goto error;
		if (TmcReceive(device_id, rcv_msg, sizeof(rcv_msg), &rcv_length))
			goto error;
		condition = std::stol((std::string)rcv_msg);
		if (!condition)
			break;
#ifdef _MANAGED
		Sleep(1);
		System::Windows::Forms::Application::DoEvents();
#endif
	}
	return 0;
error:
	return TmcGetLastError(device_id);
}
int TKADC::WaitADC(TKADC::ConditionFlag flag)
{
	char rcv_msg[1024];
	int rcv_length;

	for (;;) {
		int condition;

		if (TmcSend(device_id, ":status:condition?"))
			goto error;
		if (TmcReceive(device_id, rcv_msg, sizeof(rcv_msg), &rcv_length))
			goto error;
		condition = static_cast<int>(std::stol((std::string)rcv_msg)) & static_cast<int>(flag);
		if (!condition)
			break;
#ifdef _MANAGED
		Sleep(1);
		System::Windows::Forms::Application::DoEvents();
#endif
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

	send_msg = (std::string)":file:save:name \"" + file_name + "\"";
	if (TmcSend(device_id, (char*)send_msg.c_str()))
		goto error;
	if (TmcSend(device_id, ":file:save:binary"))
		goto error;
	return 0;
error:
	return TmcGetLastError(device_id);
}

int TKADC::GetStatusCondition(TKADC::ConditionFlag flag)
{
	char rcv_msg[1024];
	int rcv_length;

	if (TmcSend(device_id, ":status:condition?"))
		goto error;
	if (TmcReceive(device_id, rcv_msg, sizeof(rcv_msg), &rcv_length))
		goto error;
	return static_cast<int>(std::stol((std::string)rcv_msg)) & static_cast<int>(flag);
error:
	return TmcGetLastError(device_id);
}

int TKADC::Delete(std::string file_name)
{
	return 0;
}

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




TKADC_DL750::TKADC_DL750() : TKADC(TKADC_ADC_MODEL_DL750)
{
}
TKADC_DL850::TKADC_DL850() : TKADC(TKADC_ADC_MODEL_DL850)
{
}
int TKADC_DL750::GetStatusCondition(TKADC_DL750::ConditionFlag flag)
{
	char rcv_msg[1024];
	int rcv_length;

	int device_id = GetDeviceID();

	if (TmcSend(device_id, ":status:condition?"))
		goto error;
	if (TmcReceive(device_id, rcv_msg, sizeof(rcv_msg), &rcv_length))
		goto error;
	return static_cast<int>(std::stol((std::string)rcv_msg)) & static_cast<int>(flag);
error:
	return TmcGetLastError(device_id);
}
int TKADC_DL750::Delete(std::string file_name)
{
	int device_id = GetDeviceID();
	std::string send_msg = (std::string)":file:delete:binary \"" + file_name + "\"";

	if (TmcSend(device_id, (char*)send_msg.c_str()))
		goto error;
	if (TmcSend(device_id, ":file:save:binary"))
		goto error;
	return 0;
error:
	return TmcGetLastError(device_id);
}

int TKADC_DL850::GetStatusCondition(TKADC_DL850::ConditionFlag flag)
{
	char rcv_msg[1024];
	int rcv_length;

	int device_id = GetDeviceID();

	if (TmcSend(device_id, ":status:condition?"))
		goto error;
	if (TmcReceive(device_id, rcv_msg, sizeof(rcv_msg), &rcv_length))
		goto error;
	return static_cast<int>(std::stol((std::string)rcv_msg)) & static_cast<int>(flag);
error:
	return TmcGetLastError(device_id);
}
int TKADC_DL850::Delete(std::string file_name)
{
	int device_id = GetDeviceID();
	std::string send_msg = (std::string)":file:delete \"" + file_name + ".WDF\"";

	if (TmcSend(device_id, (char*)send_msg.c_str()))
		goto error;
	if (TmcSend(device_id, ":file:save:binary"))
		goto error;
	return 0;
error:
	return TmcGetLastError(device_id);
}

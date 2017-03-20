#include "tkshotinfo.h"


inline void TKDATA::readHDRLineString(std::string buf, int trace_number, char* key_name, std::string* odata)
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
template<typename T> int TKDATA::readHDRLine(std::string buf, int trace_number, char* key_name, T* data)
{
	readHDRLineString(buf, trace_number, key_name, data);
	return 0;
}
template<> int TKDATA::readHDRLine(std::string buf, int trace_number, char* key_name, float* data)
{
	std::string idata[4];
	readHDRLineString(buf, trace_number, key_name, idata);
	for (int i = 0; i < trace_number; i++)
		data[i] = std::stof(idata[i], NULL);
	return 0;
}
template<> int TKDATA::readHDRLine(std::string buf, int trace_number, char* key_name, int* data)
{
	std::string idata[4];
	readHDRLineString(buf, trace_number, key_name, idata);
	for (int i = 0; i < trace_number; i++)
		data[i] = std::stoi(idata[i], NULL, 10);
	return 0;
}
template<> int TKDATA::readHDRLine(std::string buf, int trace_number, char* key_name, struct std::tm* data)
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
		}
		else if ((std::string)key_name == "Time") {
			std::getline(ss, ibuf, ':');
			(data + i)->tm_hour = std::stoi(ibuf);
			std::getline(ss, ibuf, ':');
			(data + i)->tm_min = std::stoi(ibuf);
			std::getline(ss, ibuf, ':');
			(data + i)->tm_sec = (int)std::stof(ibuf);
		}
		else {
			return -1;
		}
	}
	return 0;
}

int TKDATA::ParseHDR()
{
	std::ifstream ifs(data_file_name + ".HDR");
	std::string buf;
	for (int lines = 1, trace_number_offset = 0, force_break = 0; 
		!force_break && std::getline(ifs, buf); lines++) {
		int group_number;
		int trace_number;
		char key_name[64];
		int idata[4];
		float fdata[4];
		std::string sdata[4];
		char cdata[4][64];
		struct std::tm tmdata[4];

		switch (lines) {

			//Model
		case 5:
			readHDRLine(buf, 1, key_name, sdata);
			model_name = sdata[0];
			break;

			//GroupNumber
		case 8:
			readHDRLine(buf, 1, key_name, idata);
			group_number = idata[0];
			break;

			//TraceTotalNumber
		case 9:
			readHDRLine(buf, 1, key_name, idata);
			trace_total_number = idata[0];
			CHData.resize(trace_total_number);
			break;

			//TraceNumber
		case 33:
		case 53:
		case 73:
			trace_number_offset += trace_number;
		case 13:
			readHDRLine(buf, 1, key_name, idata);
			trace_number = idata[0];
			break;

			//TraceName
		case 15:
		case 35:
		case 55:
		case 75:
			readHDRLine(buf, trace_number, key_name, sdata);
			for (int i = 0; i < trace_number; i++) {
				CHData[trace_number_offset + i].trace_name = sdata[i];
				//TraceNameからADCチャンネルを推測(HDRパースには不要)
				CHData[trace_number_offset + i].ch_number = traceNameToCHNumber(sdata[i]);
				if (CHData[trace_number_offset + i].ch_number != -1)
					channel_number_to_trace_number[CHData[trace_number_offset + i].ch_number]
					= trace_number_offset + i;
			}
			break;

			//HResolution
		case 26:
		case 46:
		case 66:
		case 86:
			readHDRLine(buf, trace_number, key_name, fdata);
			for (int i = 0; i < trace_number; i++)
				CHData[trace_number_offset + i].h_resolution = fdata[i];
			break;

			//HOffset
		case 27:
		case 47:
		case 67:
		case 87:
			readHDRLine(buf, trace_number, key_name, fdata);
			for (int i = 0; i < trace_number; i++)
				CHData[trace_number_offset + i].h_offset = fdata[i];
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
				CHData[trace_number_offset + i].time = tmdata[i];
			break;

			//EOF
		case 31:
		case 51:
		case 71:
		case 91:
			if (trace_number_offset + trace_number >= trace_total_number)
				force_break = 1;
				break;
		}
	}
	return 0;
}
int TKDATA::traceNameToCHNumber(std::string trace_name)
{
	for (int i = 0; i < 100; i++)
	if (trace_name == ("CH" + std::to_string(i)))
		return i;
	return -1;
}
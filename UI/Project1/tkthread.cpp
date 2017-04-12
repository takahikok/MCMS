#include "tkthread.h"
#if 0
exadcstart::exadcstart(TKADCINFO::ADCID const adcid_, TKADC::ConditionFlag flag_)
{
	adcid = adcid_;
	flag = flag_;
}

exadcstart::~exadcstart() {}

void exadcstart::operator()() {
	TKADCINFO::ADCIDToTKADCPtr(adcid)->Start();
	TKADCINFO::ADCIDToTKADCPtr(adcid)->GetStatusCondition(flag);
}

std::string exfunctor::makeLocalFileName(std::string prefix, int local_shot_number, int shot_number_length, std::string suffix)
{
	std::ostringstream fname;
	fname << prefix << std::setfill('0') << std::setw(shot_number_length) << std::right << (local_shot_number) << suffix;
	return (std::string)fname.str();
}
inline std::string exfunctor::getLastLocalFileName(TKADCINFO::ADCID adcid)
{
	return makeLocalFileName((*Setting)[TKADCINFO::ADCIDToSectionName(adcid)]["LocalShotNamePrefix"],
		TKADCINFO::ADCIDToTKADCPtr(adcid)->GetLastLocalShotNumber(), 5, "");
}
inline std::string exfunctor::getNextLocalFileName(TKADCINFO::ADCID adcid)
{
	return makeLocalFileName((*Setting)[TKADCINFO::ADCIDToSectionName(adcid)]["LocalShotNamePrefix"],
		TKADCINFO::ADCIDToTKADCPtr(adcid)->GetNextLocalShotNumber(), 5, "");
}
inline int exfunctor::downloadFromADC(TKADCINFO::ADCID adcid, std::string filename)
{
	clx::ftp session((std::string)((*Setting)[TKADCINFO::ADCIDToSectionName(adcid)]["IPAddress"]), 21);
	session.login((std::string)((*Setting)[TKADCINFO::ADCIDToSectionName(adcid)]["UserName"].c_str()),
		(std::string)(clx::base64::decode((*Setting)[TKADCINFO::ADCIDToSectionName(adcid)]["Password"].c_str())));
	session.cd((std::string)((*Setting)[TKADCINFO::ADCIDToSectionName(adcid)]["StragePath"]));
	session.retrieve(filename, filename, clx::ftp::binary);
	session.finish();
	return 0;
}

exfunctor::exfunctor(clx::ini* const Setting_, TKADCINFO::ADCID const adcid_, TKADC::ConditionFlag flag_)
{
	adcid = adcid_;
	Setting = Setting_;
}

exfunctor::~exfunctor() {}

void exfunctor::operator()() {
	TKADCINFO::ADCIDToTKADCPtr(adcid)->WaitADC();
	TKADCINFO::ADCIDToTKADCPtr(adcid)->SaveShot(getNextLocalFileName(adcid));
	TKADCINFO::ADCIDToTKADCPtr(adcid)->WaitADC();
	switch (TKADCINFO::ADCIDToTKADCPtr(adcid)->Model()) {
	case TKADC_ADC_MODEL_DL750:
		downloadFromADC(adcid, getNextLocalFileName(adcid) + ".WVF");
		downloadFromADC(adcid, getNextLocalFileName(adcid) + ".HDR");
		std::system(((std::string)"wvfconv.exe " + getNextLocalFileName(TKADCINFO_ADC_ID_DL750)
			+ " > " + getNextLocalFileName(TKADCINFO_ADC_ID_DL750) + ".CSV").c_str());
		break;
	case TKADC_ADC_MODEL_DL850:
		downloadFromADC(adcid, getNextLocalFileName(adcid) + ".WDF");
		std::system(((std::string)"WDFCon.exe " + getNextLocalFileName(TKADCINFO_ADC_ID_DL850) + ".WDF").c_str());
		std::system(((std::string)"wvfconv.exe " + getNextLocalFileName(TKADCINFO_ADC_ID_DL850)
			+ " > " + getNextLocalFileName(TKADCINFO_ADC_ID_DL850) + ".CSV").c_str());
		break;
	}
	TKADCINFO::ADCIDToTKADCPtr(adcid)->IncrementLocalShotNumber();
	(*Setting)[TKADCINFO::ADCIDToSectionName(adcid)]["LastLocalShotNumber"]
		= std::to_string(TKADCINFO::ADCIDToTKADCPtr(adcid)->GetLastLocalShotNumber());
}

#endif
#if 0
#include "tkadc.h"
#include "tkadcinfo.h"
#include "clx/base64.h"
#include "clx/ini.h"
/*
#include "clx/ftp.h"
#include "clx/thread.h"
*/
#pragma once

#if 0
class exadcstart {
private:
	TKADCINFO::ADCID adcid;
	TKADCCONTROL::CONDITIONFLAG flag;
public:
	exadcstart(TKADCINFO::ADCID const adcid_, TKADCCONTROL::CONDITIONFLAG flag_);
	virtual ~exadcstart();
	void operator()();
};

class exfunctor {
private:
	TKADCINFO::ADCID adcid;
	clx::ini* Setting;
	std::string makeLocalFileName(std::string prefix, int local_shot_number, int shot_number_length, std::string suffix);
	inline std::string getLastLocalFileName(TKADCINFO::ADCID adcid);
	inline std::string getNextLocalFileName(TKADCINFO::ADCID adcid);
	inline int downloadFromADC(TKADCINFO::ADCID adcid, std::string filename);
public:
	exfunctor(clx::ini* const Setting_, TKADCINFO::ADCID const adcid_, TKADCCONTROL::CONDITIONFLAG flag_);
	virtual ~exfunctor();
	void operator()();
};
#else
class exadcstart {
private:
	TKADCINFO::ADCID adcid;
	TKADCCONTROL::CONDITIONFLAG flag;
public:
	exadcstart(TKADCINFO::ADCID const adcid_, TKADCCONTROL::CONDITIONFLAG flag_)
	{
		adcid = adcid_;
		flag = flag_;
	}

	virtual ~exadcstart() {};
	void operator()()
	{
		TKADCINFO::ADCIDToTKADCPtr(adcid)->Start();
		TKADCINFO::ADCIDToTKADCPtr(adcid)->GetStatusCondition(flag);
	}
};

class exfunctor {
private:
	TKADCINFO::ADCID adcid;
	clx::ini* Setting;
	std::string makeLocalFileName(std::string prefix, int local_shot_number, int shot_number_length, std::string suffix)
	{
		std::ostringstream fname;
		fname << prefix << std::setfill('0') << std::setw(shot_number_length) << std::right << (local_shot_number) << suffix;
		return (std::string)fname.str();
	}

	inline std::string getLastLocalFileName(TKADCINFO::ADCID adcid)
	{
		return makeLocalFileName((*Setting)[TKADCINFO::ADCIDToSectionName(adcid)]["LocalShotNamePrefix"],
			TKADCINFO::ADCIDToTKADCPtr(adcid)->GetLastLocalShotNumber(), 5, "");
	}

	inline std::string getNextLocalFileName(TKADCINFO::ADCID adcid)
	{
		return makeLocalFileName((*Setting)[TKADCINFO::ADCIDToSectionName(adcid)]["LocalShotNamePrefix"],
			TKADCINFO::ADCIDToTKADCPtr(adcid)->GetNextLocalShotNumber(), 5, "");
	}

	inline int downloadFromADC(TKADCINFO::ADCID adcid, std::string filename)
	{
		clx::ftp session((std::string)((*Setting)[TKADCINFO::ADCIDToSectionName(adcid)]["IPAddress"]), 21);
		session.login((std::string)((*Setting)[TKADCINFO::ADCIDToSectionName(adcid)]["UserName"].c_str()),
			(std::string)(clx::base64::decode((*Setting)[TKADCINFO::ADCIDToSectionName(adcid)]["Password"].c_str())));
		session.cd((std::string)((*Setting)[TKADCINFO::ADCIDToSectionName(adcid)]["StragePath"]));
		session.retrieve(filename, filename, clx::ftp::binary);
		session.finish();
		return 0;
	}

public:
	exfunctor(clx::ini* const Setting_, TKADCINFO::ADCID const adcid_, TKADCCONTROL::CONDITIONFLAG flag_)
	{
		adcid = adcid_;
		Setting = Setting_;
	}

	virtual ~exfunctor() {};
	void operator()()
	{
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
};

#endif
#endif
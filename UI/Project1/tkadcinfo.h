#include "tkadc.h"
#ifndef __TKADCINFO__
#define __TKADCINFO__

#define TKADCINFO_ADC_ID_DL750 TKADCINFO::ADCID::ADCNameDL750
#define TKADCINFO_ADC_ID_DL850 TKADCINFO::ADCID::ADCNameDL850

namespace TKADCINFO
{
	enum class ADCID : int
	{
		ADCNameDL750,
		ADCNameDL850
	};
//	extern TKADC* tkadc_ptr[(int)sizeof(ADCID)];
	TKADC*& ADCIDToTKADCPtr(ADCID adcid);
//	TKADC::ADCType ADCIDToADCType(TKADCINFO::ADCID adcid);
//	std::string ADCIDToADCName(TKADCINFO::ADCID adcid);
	std::string ADCIDToSectionName(TKADCINFO::ADCID adcid);
};
#endif
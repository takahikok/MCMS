#include "tkadc.h"
#include "tkadcinfo.h"
namespace TKADCINFO
{
/*	TKADC::ADCModel ADCIDToADCType(TKADCINFO::ADCID adcid)
	{
		switch (adcid) {
		case TKADCINFO_ADC_ID_DL750:
			return TKADC_ADC_MODEL_DL750;
		case TKADCINFO_ADC_ID_DL850:
			return TKADC_ADC_MODEL_DL850;
		}
	}
	std::string ADCIDToADCName(TKADCINFO::ADCID adcid)
	{
		switch (adcid) {
		case TKADCINFO_ADC_ID_DL750:
			return "DL750";
		case TKADCINFO_ADC_ID_DL850:
			return "DL850";
		}
	}*/
	TKADC*& ADCIDToTKADCPtr(ADCID adcid)
	{
		static TKADC* tkadc_ptr[(int)sizeof(ADCID)];
		return tkadc_ptr[(int)adcid];
	}
	std::string ADCIDToSectionName(TKADCINFO::ADCID adcid)
	{
		switch (adcid) {
		case TKADCINFO_ADC_ID_DL750:
			return "DL750";
		case TKADCINFO_ADC_ID_DL850:
			return "DL850";
		}
		return "";
	}
};

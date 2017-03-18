#include "tkadc.h"
#include "tkadcinfo.h"
namespace TKADCINFO
{
	TKADC::ADCType ADCIDToADCType(TKADCINFO::ADCID adcid)
	{
		switch (adcid) {
		case TKADCINFO::ADCID::ADCNameDL750:
			return TKADC_ADC_TYPE_DL750;
		case TKADCINFO::ADCID::ADCNameDL850:
			return TKADC_ADC_TYPE_DL850;
		}
	}
	std::string ADCIDToADCName(TKADCINFO::ADCID adcid)
	{
		switch (adcid) {
		case TKADCINFO::ADCID::ADCNameDL750:
			return "DL750";
		case TKADCINFO::ADCID::ADCNameDL850:
			return "DL850";
		}
	}
};

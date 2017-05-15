#include "MyForm.h"
void Project1::MyForm::startMeasurement(Project1::MyForm^ parent)
{
#ifndef _MULTI_THREAD_
#if 0
	thisShot->Clear();
	TKADCINFO::ADCIDToTKADCPtr(TKADCINFO_ADC_ID_DL750)->Start();
	TKADCINFO::ADCIDToTKADCPtr(TKADCINFO_ADC_ID_DL850)->Start();
	TKADCINFO::ADCIDToTKADCPtr(TKADCINFO_ADC_ID_DL750)->WaitADC();
	TKADCINFO::ADCIDToTKADCPtr(TKADCINFO_ADC_ID_DL850)->WaitADC();
	TKADCINFO::ADCIDToTKADCPtr(TKADCINFO_ADC_ID_DL750)
		->SaveShot(makeLocalFileName("D7T", TKADCINFO::ADCIDToTKADCPtr(TKADCINFO_ADC_ID_DL750)->GetNextLocalShotNumber(), 5, ""));
	TKADCINFO::ADCIDToTKADCPtr(TKADCINFO_ADC_ID_DL850)
		->SaveShot(makeLocalFileName("D8T", TKADCINFO::ADCIDToTKADCPtr(TKADCINFO_ADC_ID_DL850)->GetNextLocalShotNumber(), 5, ""));
	TKADCINFO::ADCIDToTKADCPtr(TKADCINFO_ADC_ID_DL750)->WaitADC();
	TKADCINFO::ADCIDToTKADCPtr(TKADCINFO_ADC_ID_DL850)->WaitADC();
	downloadFromADC(TKADCINFO_ADC_ID_DL750, makeLocalFileName("D7T", TKADCINFO::ADCIDToTKADCPtr(TKADCINFO_ADC_ID_DL750)->GetNextLocalShotNumber(), 5, ".WVF"));
	downloadFromADC(TKADCINFO_ADC_ID_DL750, makeLocalFileName("D7T", TKADCINFO::ADCIDToTKADCPtr(TKADCINFO_ADC_ID_DL750)->GetNextLocalShotNumber(), 5, ".HDR"));
	downloadFromADC(TKADCINFO_ADC_ID_DL850, makeLocalFileName("D8T", TKADCINFO::ADCIDToTKADCPtr(TKADCINFO_ADC_ID_DL850)->GetNextLocalShotNumber(), 5, ".WDF"));
	TKADCINFO::ADCIDToTKADCPtr(TKADCINFO_ADC_ID_DL750)->IncrementLocalShotNumber();
	TKADCINFO::ADCIDToTKADCPtr(TKADCINFO_ADC_ID_DL850)->IncrementLocalShotNumber();
	(*Setting)["DL750"]["LastLocalShotNumber"] = std::to_string(TKADCINFO::ADCIDToTKADCPtr(TKADCINFO_ADC_ID_DL750)->GetLastLocalShotNumber());
	(*Setting)["DL850"]["LastLocalShotNumber"] = std::to_string(TKADCINFO::ADCIDToTKADCPtr(TKADCINFO_ADC_ID_DL850)->GetLastLocalShotNumber());
	Setting->write(SETTING_FILE_PATH);
	plotRaw(0);
#else
	thisShot->Clear();
	threadADCStart(TKADCINFO_ADC_ID_DL750);
	threadADCStart(TKADCINFO_ADC_ID_DL850);
	threadADCWait(TKADCINFO_ADC_ID_DL750);
	threadADCWait(TKADCINFO_ADC_ID_DL850);
	threadADCWaitandDownload(TKADCINFO_ADC_ID_DL750);
	threadADCWaitandDownload(TKADCINFO_ADC_ID_DL850);
	Setting->write(SETTING_FILE_PATH);
	plotRaw(0);
#endif
#else
	thisShot->Clear();

	flushADCState("Checking file...");

//	TKADCINFO::ADCIDToTKADCPtr(TKADCINFO_ADC_ID_DL750)->Delete(getNextLocalFileName(TKADCINFO_ADC_ID_DL750));
//	TKADCINFO::ADCIDToTKADCPtr(TKADCINFO_ADC_ID_DL850)->Delete(getNextLocalFileName(TKADCINFO_ADC_ID_DL850));

	flushADCState("Calibration", System::Drawing::Color::OrangeRed);
	{
		clx::thread t1(exadcstart(TKADCINFO_ADC_ID_DL750, static_cast<TKADCCONTROL::CONDITIONFLAG>(TKADCCONTROL_DL750::CONDITIONFLAG::TRGINV)));
		clx::thread t2(exadcstart(TKADCINFO_ADC_ID_DL850, static_cast<TKADCCONTROL::CONDITIONFLAG>(TKADCCONTROL_DL850::CONDITIONFLAG::TRGINV)));

		t1.join();
		t2.join();

		t1.detach();
		t2.detach();
	}

	flushADCState("Running", System::Drawing::Color::Blue);

	for (;;) {
		if (!TKADCINFO::ADCIDToTKADCPtr(TKADCINFO_ADC_ID_DL750)->GetStatusCondition(
			static_cast<TKADCCONTROL::CONDITIONFLAG>(TKADCCONTROL_DL750::CONDITIONFLAG::ALL)))
			break;
		if (!TKADCINFO::ADCIDToTKADCPtr(TKADCINFO_ADC_ID_DL850)->GetStatusCondition(
			static_cast<TKADCCONTROL::CONDITIONFLAG>(TKADCCONTROL_DL850::CONDITIONFLAG::ALL)))
			break;
		System::Windows::Forms::Application::DoEvents();
	}

	flushADCState("Getting file...");
#if 0
	{
		clx::thread t1(exfunctor(Setting, TKADCINFO_ADC_ID_DL750, static_cast<TKADCCONTROL::CONDITIONFLAG>(TKADCCONTROL_DL750::CONDITIONFLAG::ALL)));
		clx::thread t2(exfunctor(Setting, TKADCINFO_ADC_ID_DL850, static_cast<TKADCCONTROL::CONDITIONFLAG>(TKADCCONTROL_DL750::CONDITIONFLAG::ALL)));

		t1.join();
		t2.join();

		t1.detach();
		t2.detach();
	}
#else
	TKADCINFO::ADCIDToTKADCPtr(TKADCINFO_ADC_ID_DL750)->WaitADC();
	TKADCINFO::ADCIDToTKADCPtr(TKADCINFO_ADC_ID_DL850)->WaitADC();
	TKADCINFO::ADCIDToTKADCPtr(TKADCINFO_ADC_ID_DL750)
		->SaveShot(makeLocalFileName("D7T", TKADCINFO::ADCIDToTKADCPtr(TKADCINFO_ADC_ID_DL750)->GetNextLocalShotNumber(), 5, ""));
	TKADCINFO::ADCIDToTKADCPtr(TKADCINFO_ADC_ID_DL850)
		->SaveShot(makeLocalFileName("D8T", TKADCINFO::ADCIDToTKADCPtr(TKADCINFO_ADC_ID_DL850)->GetNextLocalShotNumber(), 5, ""));
	TKADCINFO::ADCIDToTKADCPtr(TKADCINFO_ADC_ID_DL750)->WaitADC();
	TKADCINFO::ADCIDToTKADCPtr(TKADCINFO_ADC_ID_DL850)->WaitADC();
	downloadFromADC(TKADCINFO_ADC_ID_DL750, makeLocalFileName("D7T", TKADCINFO::ADCIDToTKADCPtr(TKADCINFO_ADC_ID_DL750)->GetNextLocalShotNumber(), 5, ".WVF"));
	downloadFromADC(TKADCINFO_ADC_ID_DL750, makeLocalFileName("D7T", TKADCINFO::ADCIDToTKADCPtr(TKADCINFO_ADC_ID_DL750)->GetNextLocalShotNumber(), 5, ".HDR"));
	downloadFromADC(TKADCINFO_ADC_ID_DL850, makeLocalFileName("D8T", TKADCINFO::ADCIDToTKADCPtr(TKADCINFO_ADC_ID_DL850)->GetNextLocalShotNumber(), 5, ".WDF"));
	std::system(((std::string)"wvfconv.exe " + getNextLocalFileName(TKADCINFO_ADC_ID_DL750)
		+ " > " + getNextLocalFileName(TKADCINFO_ADC_ID_DL750) + ".CSV").c_str());
			std::system(((std::string)"WDFCon.exe " + getNextLocalFileName(TKADCINFO_ADC_ID_DL850) + ".WDF").c_str());
			std::system(((std::string)"wvfconv.exe " + getNextLocalFileName(TKADCINFO_ADC_ID_DL850)
				+ " > " + getNextLocalFileName(TKADCINFO_ADC_ID_DL850) + ".CSV").c_str());
			TKADCINFO::ADCIDToTKADCPtr(TKADCINFO_ADC_ID_DL750)->IncrementLocalShotNumber();
	TKADCINFO::ADCIDToTKADCPtr(TKADCINFO_ADC_ID_DL850)->IncrementLocalShotNumber();
	(*Setting)["DL750"]["LastLocalShotNumber"] = std::to_string(TKADCINFO::ADCIDToTKADCPtr(TKADCINFO_ADC_ID_DL750)->GetLastLocalShotNumber());
	(*Setting)["DL850"]["LastLocalShotNumber"] = std::to_string(TKADCINFO::ADCIDToTKADCPtr(TKADCINFO_ADC_ID_DL850)->GetLastLocalShotNumber());
#endif
	Setting->write(SETTING_FILE_PATH);

	flushADCState("Ready");

	thisShot->Clear();
	thisShot->AppendDataFile(getLastLocalFileName(TKADCINFO_ADC_ID_DL750));
	thisShot->AppendDataFile(getLastLocalFileName(TKADCINFO_ADC_ID_DL850));
	parent->plotRaw(0, true);
#endif

}
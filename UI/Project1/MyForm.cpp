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
#if 1
	{
		System::Threading::Thread^ thread750 = gcnew System::Threading::Thread(
			gcnew System::Threading::ThreadStart(this, &MyForm::threadADCWaitandDownload750));
		//		gcnew System::Threading::ParameterizedThreadStart(this, &MyForm::threadADCWaitandDownload));
		System::Threading::Thread^ thread850 = gcnew System::Threading::Thread(
			gcnew System::Threading::ThreadStart(this, &MyForm::threadADCWaitandDownload850));


		thread750->Start();
		thread850->Start();

		thread750->Join();
		thread850->Join();

		std::system(((std::string)"wvfconv.exe " + getNextLocalFileName(TKADCINFO_ADC_ID_DL750)
			+ " > " + getNextLocalFileName(TKADCINFO_ADC_ID_DL750) + ".CSV").c_str());
		std::system(((std::string)"WDFCon.exe " + getNextLocalFileName(TKADCINFO_ADC_ID_DL850) + ".WDF").c_str());
		std::system(((std::string)"wvfconv.exe " + getNextLocalFileName(TKADCINFO_ADC_ID_DL850)
			+ " > " + getNextLocalFileName(TKADCINFO_ADC_ID_DL850) + ".CSV").c_str());
		TKADCINFO::ADCIDToTKADCPtr(TKADCINFO_ADC_ID_DL750)->IncrementLocalShotNumber();
		TKADCINFO::ADCIDToTKADCPtr(TKADCINFO_ADC_ID_DL850)->IncrementLocalShotNumber();
		(*Setting)["DL750"]["LastLocalShotNumber"] = std::to_string(TKADCINFO::ADCIDToTKADCPtr(TKADCINFO_ADC_ID_DL750)->GetLastLocalShotNumber());
		(*Setting)["DL850"]["LastLocalShotNumber"] = std::to_string(TKADCINFO::ADCIDToTKADCPtr(TKADCINFO_ADC_ID_DL850)->GetLastLocalShotNumber());
	}
#elif 0
	{
		std::string setting[2][10];
		for (TKADCINFO::ADCID adcid = TKADCINFO_ADC_ID_DL750; adcid < TKADCINFO_ADC_ID_DL850; adcid++) {
			setting[static_cast<unsigned int>(adcid)][0] = (*Setting)[TKADCINFO::ADCIDToSectionName(adcid)]["LocalShotNamePrefix"];
			setting[static_cast<unsigned int>(adcid)][0] = (*Setting)[TKADCINFO::ADCIDToSectionName(adcid)]["IPAddress"];
			setting[static_cast<unsigned int>(adcid)][0] = (*Setting)[TKADCINFO::ADCIDToSectionName(adcid)]["UserName"];
			setting[static_cast<unsigned int>(adcid)][0] = (std::string)(clx::base64::decode((*Setting)[TKADCINFO::ADCIDToSectionName(adcid)]["Password"].c_str()));
			setting[static_cast<unsigned int>(adcid)][0] = (*Setting)[TKADCINFO::ADCIDToSectionName(adcid)]["StragePath"];
		}

		clx::thread t3(exfunctor(setting[static_cast<unsigned int>(TKADCINFO_ADC_ID_DL750)], TKADCINFO_ADC_ID_DL750));
		clx::thread t4(exfunctor(setting[static_cast<unsigned int>(TKADCINFO_ADC_ID_DL750)], TKADCINFO_ADC_ID_DL850));

		t3.join();
		t4.join();

		t3.detach();
		t4.detach();
		//		TKADCINFO::ADCIDToTKADCPtr(TKADCINFO_ADC_ID_DL750)->IncrementLocalShotNumber();
		//TKADCINFO::ADCIDToTKADCPtr(TKADCINFO_ADC_ID_DL850)->IncrementLocalShotNumber();
		//(*Setting)["DL750"]["LastLocalShotNumber"] = std::to_string(TKADCINFO::ADCIDToTKADCPtr(TKADCINFO_ADC_ID_DL750)->GetLastLocalShotNumber());
		//(*Setting)["DL850"]["LastLocalShotNumber"] = std::to_string(TKADCINFO::ADCIDToTKADCPtr(TKADCINFO_ADC_ID_DL850)->GetLastLocalShotNumber());
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
	parent->webBrowser1->Refresh();
#endif

}
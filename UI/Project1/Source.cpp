#include "MyForm.h" // [2]で付けたForm名.h
#include "SetupADCConnection.h"
#include "SetupADCMeasurement.h"
#include "SetupPlot.h"
#include "tkadc.h"
#include <iostream>
#include "clx/ini.h"
#include "tkshotinfo.h"
#include "tkplot.h"

#define SETTING_FILE_PATH "settings.ini"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
int main(array<String^>^ args)
{
	TKADCCONTROL_DL750* DL750;
	TKADCCONTROL_DL850* DL850;
	DL750 = new TKADCCONTROL_DL750();
	DL850 = new TKADCCONTROL_DL850();
	TKSHOT* thisShot;
	thisShot = new TKSHOT;
	TKPLOT* thisPlot;
	thisPlot = new TKPLOT(thisShot);


	clx::ini* Setting;
	Setting = new clx::ini(SETTING_FILE_PATH);

	try {
		Application::EnableVisualStyles();
		Application::SetCompatibleTextRenderingDefault(false);
		Application::Run(gcnew Project1::MyForm(Setting, thisShot, thisPlot, DL750, DL850));
	}
	catch (...) {

	}

	Setting->write(SETTING_FILE_PATH);
	delete DL750;
	delete DL850;
	delete thisShot;
	delete thisPlot;
	delete Setting;
	return 0;
}

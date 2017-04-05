#include "MyForm.h" // [2]‚Å•t‚¯‚½Form–¼.h
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
	TKADC* DL750;
	TKADC* DL850;
	DL750 = new TKADC;
	DL850 = new TKADC;
	TKSHOT* thisShot;
	thisShot = new TKSHOT;
	TKPLOT* thisPlot;
	thisPlot = new TKPLOT(thisShot);

	
	clx::ini* Setting;
	Setting = new clx::ini(SETTING_FILE_PATH);

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew Project1::MyForm(Setting, thisShot, thisPlot, DL750, DL850));

	Setting->write(SETTING_FILE_PATH);
	delete DL750;
	delete DL850;
	delete thisShot;
	delete thisPlot;
	delete Setting;
	return 0;
}

#include "MyForm.h" // [2]で付けたForm名.h
#include "SetupADCConnection.h"
#include "SetupADCMeasurement.h"
#include "SetupPlot.h"
#include "tkadc.h"
#include <iostream>
#include "clx/ini.h"
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

	clx::ini* Setting;
	Setting = new clx::ini(SETTING_FILE_PATH);

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	// gcnew [1]で付けたプロジェクト名::[2]で付けたForm名()
	Application::Run(gcnew Project1::MyForm(Setting, DL750, DL850));

	Setting->write(SETTING_FILE_PATH);
	return 0;
}

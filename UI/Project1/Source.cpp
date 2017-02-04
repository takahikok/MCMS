#include "MyForm.h" // [2]�ŕt����Form��.h
#include "SetupADCConnection.h" // [2]�ŕt����Form��.h
#include "tkadc.h"
#include <iostream>
#include "clx/ini.h"

using namespace System;                                                                                                      
using namespace System::Windows::Forms;

[STAThreadAttribute]
int main(array<String^>^ args) 
{
	TKADC* DL750;
	TKADC* DL850;
	DL750 = new TKADC;
	DL850 = new TKADC;

	const char SETTING_FILE_PATH[] = "settings.ini";
	clx::ini* Setting;
	Setting = new clx::ini(SETTING_FILE_PATH);

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	// gcnew [1]�ŕt�����v���W�F�N�g��::[2]�ŕt����Form��()
	Application::Run(gcnew Project1::MyForm(Setting, DL750, DL850));

	Setting->write(SETTING_FILE_PATH);
	return 0;
}

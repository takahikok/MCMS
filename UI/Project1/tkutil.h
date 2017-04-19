#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
#pragma once

namespace TKUTIL {
	std::string SystemStringToString(System::String ^ s);
	//note: (to String) : gcnew System::String(char*);
	std::string ZeroFill(int number, int length);
	int IsExistFile(std::string file_name);
}
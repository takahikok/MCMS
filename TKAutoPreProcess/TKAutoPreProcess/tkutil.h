#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
#pragma once

namespace TKUTIL {
#if 0
	std::string SystemStringToString(System::String ^ s);
#endif
	//note: (to String) : gcnew System::String(char*);
	std::string ZeroFill(int number, int length);
	int IsExistFile(std::string file_name);
}
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#pragma once

namespace TKUTIL {
	std::string SystemStringToString(System::String ^ s);
	//note: (to String) : gcnew System::String(char*);
	std::string ZeroFill(int number, int length);
}
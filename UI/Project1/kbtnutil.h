#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#pragma once

namespace kbtn {
	extern std::string SystemStringToString(System::String ^ s);
	//note: (to String) : gcnew System::String(char*);
}
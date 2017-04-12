#include <string>
#include <iostream>
#include "tkutil.h"

std::string TKUTIL::SystemStringToString(System::String ^ s)
{
	std::string os;
	using namespace System::Runtime::InteropServices;
	const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
	os = chars;
	Marshal::FreeHGlobal(System::IntPtr((void*)chars));
	return os;
}

std::string TKUTIL::ZeroFill(int number, int length)
{
	std::ostringstream fname;
	fname << std::setfill('0') << std::setw(length) << std::right << (number);
	return (std::string)fname.str();
}

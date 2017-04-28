#include <string>
#include <iostream>
#include <fstream>
#include "tkutil.h"

#if 0
std::string TKUTIL::SystemStringToString(System::String ^ s)
{
	std::string os;
	using namespace System::Runtime::InteropServices;
	const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
	os = chars;
	Marshal::FreeHGlobal(System::IntPtr((void*)chars));
	return os;
}
#endif
std::string TKUTIL::ZeroFill(int number, int length)
{
	std::ostringstream fname;
	fname << std::setfill('0') << std::setw(length) << std::right << (number);
	return (std::string)fname.str();
}

int TKUTIL::IsExistFile(std::string file_name)
{
#if 1
	std::fstream fs;
	try {
		fs.open(file_name, std::fstream::in);
	}
	catch (std::ifstream::failure& e) {
		return 0;
	}
	if (!fs.is_open())
		return 0;
	fs.close();
	return 1;
#else
	FILE  *fp;

	if ((fp = fopen(filename, "r")) == NULL)
		return (0);
	fclose(fp);
	return (1);
#endif
}
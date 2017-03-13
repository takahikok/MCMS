#include <string>
#include <iostream>
#include "kbtnutil.h"

namespace kbtn {
	std::string SystemStringToString(System::String ^ s)
	{
		std::string os;
		using namespace System::Runtime::InteropServices;
		const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
		os = chars;
		Marshal::FreeHGlobal(System::IntPtr((void*)chars));
		return os;
	}

}

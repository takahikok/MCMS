#include "tkutil.h"

std::string TKUTIL::ZeroFill(int const number, int const length)
{
	std::ostringstream fname;
	fname << std::setfill('0') << std::setw(length) << std::right << (number);
	return (std::string)fname.str();
}

bool TKUTIL::IsExistFile(std::string const file_name)
{
	std::fstream fs;
	try {
		fs.open(file_name, std::fstream::in);
	}
	catch (const std::ifstream::failure&) {
		return false;
	}
	if (!fs.is_open())
		return false;
	fs.close();
	return true;
}
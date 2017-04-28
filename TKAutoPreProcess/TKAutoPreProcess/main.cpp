#include <iostream>
#include "tkutil.h"

int main(int argc, char* argv[])
{

	switch (argc) {
	case 1:
	default:
		std::cerr << "TK Auto Pre Process" << std::endl;
		std::cerr << "syntax: " << std::endl;
		std::cerr << "\targument1: start#" << std::endl;
		std::cerr << "\targument2: stop#" << std::endl;
		return 0;
		break;
	case 3:
		if (std::stoi(argv[1]) > std::stoi(argv[2])) {
			std::cerr << "argument2 must larger than argument1" << std::endl;
			return 0;
		}
	}

	for (int i = std::stoi(argv[1]); i <= std::stoi(argv[2]); i++) {
		std::string source_file, out_file;

		source_file = (std::string)"D8T" + TKUTIL::ZeroFill(i, 5);
		out_file = source_file + "_SMA_21";
		if (!TKUTIL::IsExistFile(out_file + ".CSV"))
			system(((std::string)"TKMovingAverage.exe " + source_file + ".CSV"
				+ " 21 > " + out_file + ".CSV").c_str());

		std::cerr << out_file + ".CSV" << std::endl;

		source_file = out_file;
		out_file = source_file + "_KH_0_400000_0";
		if (!TKUTIL::IsExistFile(out_file + ".CSV"))
			system(((std::string)"TKKillHysteresis.exe " + source_file + ".CSV"
				+ " 0 400000 0 > " + out_file + ".CSV").c_str());

		std::cerr << out_file + ".CSV" << std::endl;

		source_file = out_file;
		out_file = source_file + "_SMA_5";
		if (!TKUTIL::IsExistFile(out_file + ".CSV"))
			system(((std::string)"TKMovingAverage.exe " + source_file + ".CSV"
				+ " 5 > " + out_file + ".CSV").c_str());

		std::cerr << out_file + ".CSV" << std::endl;
	}
	return 0;
}
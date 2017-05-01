#include <iostream>
#include "tkutil.h"

int main(int argc, char* argv[])
{
	unsigned int start, stop;

	try {
		std::cerr << "#----------------------------------------#" << std::endl;
		std::cerr << "# TKAutoPreProcess    T.Kobayashi 2017.4 #" << std::endl;
		std::cerr << "#----------------------------------------#" << std::endl;

		switch (argc) {
		case 1:
		default:
			std::cerr << "TK Auto Pre Process" << std::endl;
			std::cerr << "syntax: " << std::endl;
			std::cerr << "\targument1: start#" << std::endl;
			std::cerr << "\targument2: stop#" << std::endl;
			std::cerr << "note: " << std::endl;
			std::cerr << "\tin case arg.2 is omitted, arg.1 is used as arg.2" << std::endl;
			return 0;
		case 2:
			start = stop = static_cast<unsigned int>(std::stoi(argv[1]));
			break;
		case 3:
			start = static_cast<unsigned int>(std::stoi(argv[1]));
			stop = static_cast<unsigned int>(std::stoi(argv[2]));
			if (start > stop) {
				std::cerr << "argument2 must larger than argument1" << std::endl;
				return 0;
			}
			break;
		}

		for (unsigned int i = start; i <= stop; i++) {
			std::string source_file, out_file;

			source_file = (std::string)"D8T" + TKUTIL::ZeroFill(i, 5);

			if (!TKUTIL::IsExistFile(source_file + ".CSV")) {
				std::cerr << "error: fail to open \"" + source_file + ".CSV\"" << std::endl;
				return 0;
			}

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
	}
	catch (...) {
		std::cerr << "error" << std::endl;
	}
	return 0;
}
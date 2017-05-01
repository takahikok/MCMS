#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "clx/salgorithm.h"
#include "clx/ini.h"
#include "tkutil.h"

#define SETTING_FILE_PATH "TKMakeMapSetting.ini"

#define MAX_TRACE_NUMBER 17

int main(int argc, char* argv[])
{
	try {
		clx::ini* Setting;

		std::cerr << "#----------------------------------------#" << std::endl;
		std::cerr << "# TKMap               T.Kobayashi 2017.4 #" << std::endl;
		std::cerr << "#----------------------------------------#" << std::endl;

		std::string ini_path;

		if (argc == 2)
			ini_path = argv[1];
		else
			ini_path = SETTING_FILE_PATH;

		try {
			Setting = new clx::ini(ini_path);
		}
		catch (...) {
			std::cerr << "error: fail to open \"" + ini_path + "\"" << std::endl;
		}

		std::cerr << "load \"" + ini_path + "\"" << std::endl;

		std::string deliminator = ",";	//white space : " \t"

		std::ofstream ofs((*Setting)["TKMakeMap"]["DestinationFile"]);
		int every = std::stoi((*Setting)["TKMakeMap"]["Every"]);
		int columns_add = std::stoi((*Setting)["TKMakeMap"]["NumberofColumnstoAdd"]);

		std::cerr << "Read " << (*Setting)["TKMakeMap"]["DataSourceNumber"] << " files." << std::endl;

		for (int data_index = 0; data_index < std::stoi((*Setting)["TKMakeMap"]["DataSourceNumber"]); data_index++) {

			if (!TKUTIL::IsExistFile((*Setting)["DataSource" + std::to_string(data_index + 1)]["SourceFile"])) {
				std::cerr << "error: fail to open \""
					+ (*Setting)["DataSource" + std::to_string(data_index + 1)]["SourceFile"]
					+ "\"" << std::endl;
				return 0;
			}

			std::ifstream ifs((*Setting)["DataSource" + std::to_string(data_index + 1)]["SourceFile"], std::ifstream::in);
			std::string line_buf;

			for (;;) {
				std::getline(ifs, line_buf);

				std::vector<std::string> tok;
				clx::split_if(line_buf, tok, clx::is_any_of(deliminator));

				try {
					std::stod(tok[0]);
				}
				catch (std::invalid_argument) {
					continue;
				}
				break;
			}

			std::string additional_column;

			for (int i = 0; i < columns_add; i++)
				additional_column = additional_column
				+ (*Setting)["DataSource" + std::to_string(data_index + 1)]["AddColumn" + std::to_string(i + 1)]
				+ ",";

			for (int i = 0; std::getline(ifs, line_buf); i++) {

				if (i%every)
					continue;

				ofs << additional_column << line_buf << std::endl;

			}

			ofs << std::endl;

			std::cerr << (*Setting)["DataSource" + std::to_string(data_index + 1)]["SourceFile"] << std::endl;

		}
	}
	catch (...) {
		std::cerr << "error" << std::endl;
	}

	return 0;

}





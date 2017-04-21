#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "clx/salgorithm.h"
#include <math.h>


#define MAX_TRACE_NUMBER 17

int main(int argc, char* argv[])
{
	int sample = 5;
	int phase = 0;
	std::string deliminator = ",";

	switch (argc) {
	case 1:
	default:
		std::cerr << "TK Kill Hysteresis" << std::endl;
		std::cerr << "syntax: " << std::endl;
		std::cerr << "\targument1: comma separated source data file" << std::endl;
		std::cerr << "\targument2: sampling number" << std::endl;
		std::cerr << "\targument3: start phase (degree)" << std::endl;
		std::cerr << "\targument4: \",\":comma separated source(default), \"w\":white-space separated source)" << std::endl;
		return 0;
	case 5:
		if (static_cast<std::string>(argv[4]) == "w")
			deliminator = " \t";
		else
			std::cerr << "第4引数を読み込めませんでした" << std::endl;
	case 4:
		try {
			phase = std::stoi(argv[3]) % 360;
		}
		catch (std::invalid_argument) {
			std::cerr << "第3引数を読み込めませんでした" << std::endl;
		}
	case 3:
		try {
			sample = std::stoi(argv[2]);
		}
		catch (std::invalid_argument) {
			std::cerr << "第2引数を読み込めませんでした" << std::endl;
		}
	case 2:
		;
	}

	std::ifstream ifs(static_cast<std::string>(argv[1]));
	std::string line_buf;

	/**
	* データの先頭で読み込みをスキップする行数です。自動的に代入されます。
	*/
	int skip_line = 0;

	int x_number;

	/**
	* 直近数行のデータマトリクスです。
	*/
	std::vector<std::vector<double>> source_data_matrix(sample,
		std::vector<double>(MAX_TRACE_NUMBER, 0.0));


	//ファイルを1行ずつ読み込みます。読み込んだ行は次のループで破棄されます。
	//配列の各要素に分割された上で実数変換されたマトリクスは直近のma_sample行分だけ保持されます。
	for (int i = 0; std::getline(ifs, line_buf); i++) {

		//行内で指定されたセパレータによる区切りを行います。
		std::vector<std::string> tok;
		clx::split_if(line_buf, tok, clx::is_any_of(deliminator));

		
		auto place = [&]()->int
		{
			switch (phase) {
			case 0:
			case 180:
				return abs(i - sample / 2);
			case 90:
			case 270:
				if (i < sample / 2)
					return abs(i - sample / 4);
				else
					return sample / 2 - abs(i - sample * 3 / 4);
			default:
				return 0;
			}
		};

		//セパレートされた各要素に対して実数変換を行います。
		x_number = tok.size();
		for (int x = 0; x < x_number; x++) {

			//実数への変換を試みます。
			try {
				source_data_matrix[place()][x] += std::stod(tok[x]);
			}

			//文字列が含まれるなど、実数への変換に失敗した場合はその行を読み飛ばします。
			//あるいは、ファイル先頭のコメント行は自動的に読み飛ばされます。
			//但し、そのような行はファイル先頭に集中している必要があります。
			catch (std::invalid_argument) {
				skip_line++;
				break;
			}
		}

		//マトリクスが全て有意なデータで埋まるまで読み込みを繰り返します
		if (i < sample + skip_line - 1) {
			//ファイル先頭のコメント行はそのまま出力されます。
			std::cout << line_buf << std::endl;
			continue;
		}

	}

	//ここからがヒステリシス除去計算です。

	std::string out_line;
	//std::vector<double> output_data_line(tok.size(), 0);

	//ヒステリシス除去計算です。
	for (int y = 0; y < sample; y++) {
		for (int x = 0; x < x_number; x++)
			out_line += (std::to_string(source_data_matrix[y][x] / 2) + ",");

		//結果を出力します。
		std::cout << out_line << std::endl;
	}

	return 0;
}





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
			std::cerr << "��4������ǂݍ��߂܂���ł���" << std::endl;
	case 4:
		try {
			phase = std::stoi(argv[3]) % 360;
		}
		catch (std::invalid_argument) {
			std::cerr << "��3������ǂݍ��߂܂���ł���" << std::endl;
		}
	case 3:
		try {
			sample = std::stoi(argv[2]);
		}
		catch (std::invalid_argument) {
			std::cerr << "��2������ǂݍ��߂܂���ł���" << std::endl;
		}
	case 2:
		;
	}

	std::ifstream ifs(static_cast<std::string>(argv[1]));
	std::string line_buf;

	/**
	* �f�[�^�̐擪�œǂݍ��݂��X�L�b�v����s���ł��B�����I�ɑ������܂��B
	*/
	int skip_line = 0;

	int x_number;

	/**
	* ���ߐ��s�̃f�[�^�}�g���N�X�ł��B
	*/
	std::vector<std::vector<double>> source_data_matrix(sample,
		std::vector<double>(MAX_TRACE_NUMBER, 0.0));


	//�t�@�C����1�s���ǂݍ��݂܂��B�ǂݍ��񂾍s�͎��̃��[�v�Ŕj������܂��B
	//�z��̊e�v�f�ɕ������ꂽ��Ŏ����ϊ����ꂽ�}�g���N�X�͒��߂�ma_sample�s�������ێ�����܂��B
	for (int i = 0; std::getline(ifs, line_buf); i++) {

		//�s���Ŏw�肳�ꂽ�Z�p���[�^�ɂ���؂���s���܂��B
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

		//�Z�p���[�g���ꂽ�e�v�f�ɑ΂��Ď����ϊ����s���܂��B
		x_number = tok.size();
		for (int x = 0; x < x_number; x++) {

			//�����ւ̕ϊ������݂܂��B
			try {
				source_data_matrix[place()][x] += std::stod(tok[x]);
			}

			//�����񂪊܂܂��ȂǁA�����ւ̕ϊ��Ɏ��s�����ꍇ�͂��̍s��ǂݔ�΂��܂��B
			//���邢�́A�t�@�C���擪�̃R�����g�s�͎����I�ɓǂݔ�΂���܂��B
			//�A���A���̂悤�ȍs�̓t�@�C���擪�ɏW�����Ă���K�v������܂��B
			catch (std::invalid_argument) {
				skip_line++;
				break;
			}
		}

		//�}�g���N�X���S�ėL�ӂȃf�[�^�Ŗ��܂�܂œǂݍ��݂��J��Ԃ��܂�
		if (i < sample + skip_line - 1) {
			//�t�@�C���擪�̃R�����g�s�͂��̂܂܏o�͂���܂��B
			std::cout << line_buf << std::endl;
			continue;
		}

	}

	//�������炪�q�X�e���V�X�����v�Z�ł��B

	std::string out_line;
	//std::vector<double> output_data_line(tok.size(), 0);

	//�q�X�e���V�X�����v�Z�ł��B
	for (int y = 0; y < sample; y++) {
		for (int x = 0; x < x_number; x++)
			out_line += (std::to_string(source_data_matrix[y][x] / 2) + ",");

		//���ʂ��o�͂��܂��B
		std::cout << out_line << std::endl;
	}

	return 0;
}





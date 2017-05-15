#include "tkfileutil.h"

void TKFILEUTIL::SHOTFILENAME::separateFilePath()
{
	// extension
	{
		std::vector<std::string> tok;

		clx::split_if(file_path, tok, clx::is_any_of("."));
		extension = tok[1];
	}

	// file name
	{
		std::vector<std::string> tok, tok2;

		clx::split_if(file_path, tok, clx::is_any_of("."));
		clx::split_if(tok[0], tok2, clx::is_any_of("\\"));
		file_name = tok2[tok2.size() - 1];
	}

	// path
	{
		std::vector<std::string> tok;

		clx::split_if(file_path, tok, clx::is_any_of("\\"));
		for (int i = 0; i < tok.size() - 1; i++)
			dir = dir + tok[i] + "\\";
	}
}

void TKFILEUTIL::SHOTFILENAME::separateFileName()
{
	std::vector<std::string> tok;

	clx::split_if(file_name, tok, clx::is_any_of("#_"));
	shot_number = std::stoi(tok[0]);
	suffix = tok[1];
}

TKFILEUTIL::SHOTFILENAME::SHOTFILENAME(std::string file_path_) : file_path(file_path_)
{
	separateFilePath();
	separateFileName();
}

unsigned int& TKFILEUTIL::SHOTFILENAME::ShotNumber()
{
	return shot_number;
}

std::string& TKFILEUTIL::SHOTFILENAME::Suffix()
{
	return suffix;
}

std::string& TKFILEUTIL::SHOTFILENAME::Extension()
{
	return extension;
}

std::string TKFILEUTIL::SHOTFILENAME::GetFileName()
{
	return "#" + TKUTIL::ZeroFill(shot_number, 8) + "_" + suffix;
}

std::string TKFILEUTIL::SHOTFILENAME::GetFileNameWithExtension()
{
	return GetFileName() + "." + extension;
}

std::string TKFILEUTIL::SHOTFILENAME::GetDirectory()
{
	return dir;
}

std::string TKFILEUTIL::SHOTFILENAME::GetFilePath()
{
	return dir + GetFileNameWithExtension();
}

std::string TKFILEUTIL::BinaryToCSV(std::string file_path, bool force_over_write)
{
	//TKADCINFO::ADCID adcid;
	std::vector<std::string> tok;

	clx::split_if(file_path, tok, clx::is_any_of("."));

	if (clx::upcase_copy(tok[1]) == "WVF") {
		if (force_over_write || !TKUTIL::IsExistFile(tok[0] + ".CSV"))
			std::system(((std::string)"wvfconv.exe " + tok[0] + " > " + tok[0] + ".CSV").c_str());
	}
	if (clx::upcase_copy(tok[1]) == "WDF") {
		if (force_over_write || !TKUTIL::IsExistFile(tok[0] + ".WVF") || !TKUTIL::IsExistFile(tok[0] + ".HDR"))
			std::system(((std::string)"WDFCon.exe " + tok[0] + ".WDF").c_str());
		if (force_over_write || !TKUTIL::IsExistFile(tok[0] + ".CSV"))
			std::system(((std::string)"wvfconv.exe " + tok[0] + " > " + tok[0] + ".CSV").c_str());
	}
	return tok[0];
}

std::string TKFILEUTIL::ExtractWDF(std::string file_path, bool force_over_write)
{
	std::vector<std::string> tok;

	clx::split_if(file_path, tok, clx::is_any_of("."));

	if (clx::upcase_copy(tok[1]) == "WDF") {
		if (force_over_write || !TKUTIL::IsExistFile(tok[0] + ".WVF") || !TKUTIL::IsExistFile(tok[0] + ".HDR"))
			std::system(((std::string)"WDFCon.exe " + tok[0] + ".WDF").c_str());
	}
	return tok[0];
}

std::vector<std::string> TKFILEUTIL::GetSameShotFileName(std::string file_path)
{
	std::vector<std::string> tok;
	std::string file_name;
	std::vector<std::string> same_shot_file_name;

	clx::split_if(file_path, tok, clx::is_any_of("\\"));
	file_name = tok[tok.size() - 1];

	if (!file_name.find("#")) {
		SHOTFILENAME shot_file(file_path);

		shot_file.Suffix() = "DL750";
		shot_file.Extension() = ".WVF";
		if (TKUTIL::IsExistFile(TKFILEUTIL::RemoveExtension(shot_file.GetFilePath()) + ".WVF")
			|| TKUTIL::IsExistFile(TKFILEUTIL::RemoveExtension(shot_file.GetFilePath()) + ".CSV"))
			same_shot_file_name.push_back(shot_file.GetFilePath());

		shot_file.Suffix() = "DL850";
		shot_file.Extension() = ".WDF";
		if (TKUTIL::IsExistFile(TKFILEUTIL::RemoveExtension(shot_file.GetFilePath()) + ".WDF")
			&& !TKUTIL::IsExistFile(TKFILEUTIL::RemoveExtension(shot_file.GetFilePath()) + ".HDR"))
			TKFILEUTIL::ExtractWDF(shot_file.GetFilePath());
		if (TKUTIL::IsExistFile(TKFILEUTIL::RemoveExtension(shot_file.GetFilePath()) + ".WDF")
			|| TKUTIL::IsExistFile(TKFILEUTIL::RemoveExtension(shot_file.GetFilePath()) + ".WVF")
			|| TKUTIL::IsExistFile(TKFILEUTIL::RemoveExtension(shot_file.GetFilePath()) + ".CSV"))
			same_shot_file_name.push_back(shot_file.GetFilePath());
	} else {
		same_shot_file_name.push_back(file_path);
	}
	return same_shot_file_name;
}

std::string TKFILEUTIL::RemoveExtension(std::string file_path)
{
	std::vector<std::string> tok;
	std::string file_name;

	clx::split_if(file_path, tok, clx::is_any_of("."));
	switch (tok.size()) {
	case 1:
	case 2:
		file_name = tok[0];
		break;
	default:
		for (int i = 0; i < tok.size() - 1; i++)
			file_name = file_name + tok[i] + ".";
	}
	return file_name;
}

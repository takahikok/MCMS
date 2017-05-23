#include "tktemp.h"

std::string TKFILEUTIL::GetTemporaryPath(std::string const project_directry)
{
	const DWORD buf_size = 1024;
	WCHAR buf[buf_size];
	std::string tmp_path;

	GetTempPath(buf_size, buf);
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> convertor;

	tmp_path = convertor.to_bytes(buf) + project_directry;

	if (project_directry != static_cast<std::string>(""))
		_mkdir(tmp_path.c_str());

	return tmp_path;
	//catch (System::Security::SecurityException^ exception) {
	//	//GetTempPathに失敗（セキュリティ）
	//}
	//		MessageBox::Show(gcnew String((*Setting)["Utility"]["TempPath"].c_str()));
}

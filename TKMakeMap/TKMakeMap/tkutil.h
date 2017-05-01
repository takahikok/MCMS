/**
* @file	tkutil.h
* @brief �֗��Ȕėp�֐����ł��B
* @author Kobayashi Takahiko
* @date 2017
*/
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
#ifndef __TKUTIL__
#define __TKUTIL__

namespace TKUTIL
{
#ifdef _MANAGED
	/**
	* @blief
	*	System::String�^��std::string�^�ɕύX���܂��B
	* @param[in] s
	*	�ύX�����System::String�^�̕�����ł��B
	* @return
	*	�ϊ����ꂽstd::string�^�̕����񂪕Ԃ���܂��B
	* @note
	*	���ʌ��ꃉ���^�C���T�|�[�g�iclr�j���ǂݍ��܂ꂽ�ꍇ�̂ݗL���ł��B
	*/
	static std::string SystemStringToString(System::String ^ s);
	//note: (to String) : gcnew System::String(char*);
#endif

	/**
	* @blief
	*	������C�ӌ�����0�Ŗ��߂�������𐶐����܂��B
	* @param[in] number
	*	�ΏۂƂȂ鐮���ł��B
	* @param[in] length
	*	�ŏI�I�Ȍ����ł��B
	* @return
	*	�������ꂽstd::string�^�̕����񂪕Ԃ���܂��B
	*/
	std::string ZeroFill(int const number, int const length);

	/**
	* @blief
	*	�w�肵���t�@�C�������݂��邩�ǂ������m���߂܂��B
	* @param[in] file_name
	*	���݂��m�F����t�@�C�����ł��B
	* @return true:
	*	�t�@�C���͑��݂��܂��B
	* @return false:
	*	�t�@�C���͑��݂��܂���B
	* @note
	*	�J�����Ƃ̂ł��Ȃ��t�@�C���͑��݂��Ȃ��Ƃ݂Ȃ���܂��B
	*/
	bool IsExistFile(std::string const file_name);
}

#ifdef _MANAGED
static std::string TKUTIL::SystemStringToString(System::String ^ s)
{
	std::string os;
	using namespace System::Runtime::InteropServices;
	const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
	os = chars;
	Marshal::FreeHGlobal(System::IntPtr((void*)chars));
	return os;
}
#endif
#endif
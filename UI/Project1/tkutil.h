/**
* @file	tkutil.h
* @brief 便利な汎用関数等です。
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
	*	System::String型をstd::string型に変更します。
	* @param[in] s
	*	変更されるSystem::String型の文字列です。
	* @return
	*	変換されたstd::string型の文字列が返されます。
	* @note
	*	共通言語ランタイムサポート（clr）が読み込まれた場合のみ有効です。
	*/
	static std::string SystemStringToString(System::String ^ s);
	//note: (to String) : gcnew System::String(char*);
#endif

	/**
	* @blief
	*	整数を任意桁数で0で埋めた文字列を生成します。
	* @param[in] number
	*	対象となる整数です。
	* @param[in] length
	*	最終的な桁数です。
	* @return
	*	生成されたstd::string型の文字列が返されます。
	*/
	std::string ZeroFill(int const number, int const length);

	/**
	* @blief
	*	指定したファイルが存在するかどうかを確かめます。
	* @param[in] file_name
	*	存在を確認するファイル名です。
	* @return true:
	*	ファイルは存在します。
	* @return false:
	*	ファイルは存在しません。
	* @note
	*	開くことのできないファイルは存在しないとみなされます。
	*/
	bool IsExistFile(std::string const file_name);
	
	/**
	* @blief
	*	ユーザー定義リテラルを定義します。
	*
	* @note
	* 	この機能を使用しない場合はTKUTIL_NO_USER_LITERALSを定義してください
	*/
	inline namespace Literals
	{
		/**
		* @blief
		*	文字列リテラルに対するサフィックス_sをstd::string型を示すユーザー定義リテラルとして定義します。
		*
		*/
		static std::string operator"" _s(const char* str, std::size_t length)
		{
			return std::string(str, length);
		}
	}

}

#ifndef TKUTIL_NO_USER_LITERALS
using namespace TKUTIL::Literals;
#endif

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
/**
* @file	tkfileutil.h
* @brief 便利な汎用関数等です。
* @author Kobayashi Takahiko
* @date 2017.5.14
*/
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <vector>
#include "clx/salgorithm.h"
#include "tkutil.h"
#ifndef __TKFILEUTIL__
#define __TKFILEUTIL__

namespace TKFILEUTIL
{
	class SHOTFILENAME
	{
	private:
		std::string file_path;		//c:\\data\\#00000005_DL850.WDF
		std::string dir;		//c:\\data\\ 
		std::string file_name;		//#00000005_DL850
		unsigned int shot_number;	//00000005
		std::string suffix;		//DL850
		std::string extension;		//WDF

	private:
		void separateFilePath();
		void separateFileName();
	public:
		SHOTFILENAME(std::string file_path_);
		unsigned int &ShotNumber();
		std::string &Suffix();
		std::string &Extension();
		std::string GetFileName();
		std::string GetFileNameWithExtension();
		std::string GetDirectory();
		std::string GetFilePath();
	};

	/**
	* @blief
	*	YOKOGAWA DL シリーズの BINARY ファイルを ASCII CSV ファイルへ変換します。
	* @param[in] file_path
	*	対象となるBINARYファイルパスです。拡張子を含みます。
	* @param[in] force_over_write
	*	変換後のファイルと同じ名前のファイルが既に存在した場合、変換を行うかを指定します。
	*	デフォルトではfalseで、変換は行われません。
	* @return
	*	生成されたCSVファイルパスが返されます。拡張子を含みません。
	* @note
	*	変換が実行されたかによらず変換後のファイル名が返されます。
	*/
	std::string BinaryToCSV(std::string file_path, bool force_over_write = false);

	/**
	* @blief
	*	YOKOGAWA DL850 の WDF ファイルを WVF + HDR ファイルへ変換します。
	* @param[in] file_path
	*	対象となるWDFファイルパスです。拡張子を含みます。
	* @param[in] force_over_write
	*	変換後のファイルと同じ名前のファイルが既に存在した場合、変換を行うかを指定します。
	*	デフォルトではfalseで、変換は行われません。
	* @return
	*	生成されたWVFファイルパスが返されます。拡張子を含みません。
	* @note
	*	同時に出力されるHDRファイルは波形情報を取得する際に必要となります。
	* @note
	*	変換が実行されたかによらず変換後のファイル名が返されます。
	*/
	std::string ExtractWDF(std::string file_path, bool force_over_write = false);


	/**
	* @blief
	*	同一ショットのファイル名を取得します。
	* @param[in] file_path
	*	対象となるBINARYファイルパスです。拡張子を含みます。
	* @return
	*	同一ショットのBINARYファイルパスのvectorです。拡張子を含みます。
	* @note
	*	同一ショットが他に存在しない場合は元のファイルだけを要素に持つvectorが返されます。
	*/
	std::vector<std::string> GetSameShotFileName(std::string file_path);


	/**
	* @blief
	*	ファイル名またはファイルパスから拡張子を除きます。
	* @return
	*	拡張子を除いたファイル名またはファイルパスです。
	* @note
	*	複数拡張子を持たないファイルでは入力がそのまま返されます。
	* @note
	*	複数拡張子を持つ（.tar.gzのような）ファイルでは末尾の拡張子だけが除かれます。
	*/
	std::string RemoveExtension(std::string file_path);

}
#endif
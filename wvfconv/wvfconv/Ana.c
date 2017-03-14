/* This is G-file %M% Version %I% (%G%) */


/*STARTM-------------------------------------------------------------

+																	+

+	モジュール名:	ana.c											+

+																	+

+	機		能	:	波形データをASCIIに変換							+

+																	+

+	改訂履歴	:													+

+	改訂	担当		日付		内容							+

+	--------------------------------------------------------------	+

+	 																+

+																	+

-ENDM--------------------------------------------------------------*/




/********************************************************************

 *					Include File Declaration						*

 ********************************************************************/

#include		"sokutei.h"			/* basic data type declaration	*/

#include		<string.h>			/* strcat,strcmp,strcpy			*/

#include		<stdio.h>			/* fopen						*/

#include		<stdlib.h>			/* atol							*/

#include		<math.h>			/* atof							*/

#include		<ctype.h>			/* isdigit, isspace				*/

#include		"analize.h"			/* struct, union declaration	*/

#include		"anrzstr.h"			/* defined strings				*/





/********************************************************************

 *					Global Variable Declaration	 					*

 ********************************************************************/

INF		_information;				/* non group infornation struct	*/

ANRZ	_analize;					/* group information struct		*/

ALLTYPE _allType;					/* all data type union			*/

UCHR	_buffer[ MaxBuff ];			/* general purpose buffer		*/

UCHR	_lineBuffer[ LineBuffMax ];	/* general purpose buffer		*/

UCHR	_readBuffer[ LineBuffMax ];	/* general purpose buffer		*/

UCHR	_destBuffer[ Buff ];		/* string data storage buffer	*/

UCHR	_groupBuffer[ Buff ];		/* group name search			*/

UCHR	_groupLimitBuffer[ Buff ];	/* group name limit				*/

INT		_style;						/* output style					*/

UCHR	t1_fname[50];				/* temp file name				*/

UCHR	t2_fname[50];				/* temp file name				*/

UCHR	t_fname[50];				/* temp file name				*/

USHORT	_mergeSw;					/* merge switch					*/

USHORT	_fileSw;					/* file operation switch		*/


FILE*	ascFp;						/* ＡＳＣＩＩファイル			*/

FILE*	binFp;						/* バイナリーファイル			*/

FILE*	t1_fp;						/* 一時ファイル（その１）		*/

FILE*	t2_fp;						/* 一時ファイル（その２）		*/



/********************************************************************

 *					Prototype Declaration							*

 ********************************************************************/

void main( int argc, char *argv[], char **envp );

INT analizeWaveForm( UCHR* fileName );

INT getInformation( INF* infP, FILE* ascFp );

INT analizeAscAndBin( INF* infP, ANRZ* analizeP, FILE* ascFp, FILE* binFp );

INT getGroupInf( INT group, INT* traceNumber, INT* blockNumber, FILE* ascFp );

INT getTraceInf( ANRZ* analizeP, INT group, INT trace, FILE* ascFp );

INT getBlockInf( ANRZ* analizeP, INT group, INT trace, INT block, FILE* ascFp );

INT analizeBin( INF* infP, ANRZ* analizeP, INT group, INT trace, INT block, FILE* ascFp, FILE* binFp );

INT readAndDispWaveForm( INF* infP, ANRZ* analizeP, INT group, INT trace, INT block, FILE* binFp );

void getEndianMode( INF* infP, UCHR endianMode );

FILE* openFile( UCHR* fileName, UCHR mode );

INT referLabel( UCHR* label, UCHR groupMode, INT group, UCHR* buffP, FILE* ascFp );

void makeGroupString( UCHR groupMode, INT group, UCHR* groupBuffP );

INT getData( UCHR* destP, UCHR* srcP, INT trace );

INT referGroup( UCHR groupMode, INT group, FILE* ascFp );

INT work( UCHR* label, UCHR* destP, UCHR groupMode, INT group, INT trace, INT block, FILE* fp );

INT getParameterData( UCHR* label, UCHR* destP, UCHR groupMode, INT group, INT trace, INT block, UCHR mode, FILE* ascFp );

INT getByte( UCHR* dataType );

INT getSize( INT group, INT trace, INT block, INT* size, FILE* ascFp );

INT seekBinFp( INF* infP, INT group, INT trace, INT block, FILE* ascFp, FILE* binFp );

INT getTraceSeekSize( INT group, INT trace, INT block, INT* seekSize, FILE* ascFp );

INT getBlockSeekSize( INF* infP, INT group, INT trace, INT block, INT* seekSize, FILE* ascFp );

void change2Byte( TYPE2* data );

void change4Byte( TYPE4* data );

void change8Byte( TYPE8* data );

INT readBinFile( DREAL* data, INF* infP, ANRZ* analizeP, FILE* binFp );

INT signedWork( DREAL* data, INT byte, INF* infP, ALLTYPE* allTypeP );

INT unsignedWork( DREAL* data, INT byte, INF* infP, ALLTYPE* allTypeP );

INT floatWork( DREAL* data, INT byte, INF* infP, ALLTYPE* allTypeP );

void binToValue( DREAL* result, ANRZ* analizeP, DREAL data );

INT printBitType( DREAL data, ANRZ* analizeP );

INT	readPreviousData();

INT	outputTo();





/*STARTF*****************************************************************

*																		*

*							メイン関数									*

*																		*

*ENDF*******************************************************************/

void	main( int argc, char *argv[], char **envp )

{

	char	opt1[10];


	_style = 3;							/* 出力スタイルの初期化			*/

	_mergeSw = Off;						/* マージスイッチの初期化		*/

	_fileSw = Off;						/* ファイル操作スイッチの初期化 */


	switch( argc )

	{

	  case 2:	/* オプション無指定の場合 */
		  _style = 0;
		  _mergeSw = On;

		if( OK != analizeWaveForm((UCHR*)*(argv + 1)) )

			exit( -1 );					/*Error termination*/

		break;

	  case 3:	/* 出力スタイルのオプション1指定の場合 */

		strncpy( opt1, argv[2], sizeof(opt1) );

		_style = atoi( opt1 ); 

		if( _strnicmp( opt1, _check_m, 1 ) == 0 )	_mergeSw = On;

		if( OK != analizeWaveForm((UCHR*)*(argv + 1)) )

			exit( -1 );					/*Error termination*/

		break;

	  case 4:	/* 出力スタイルのオプション1と2指定の場合 */

		strncpy( opt1, argv[2], sizeof(opt1) );

		_style = atoi( opt1 ); 

		strncpy( opt1, argv[3], sizeof(opt1) );

		if( _strnicmp( opt1, _check_m, 1 ) == 0 )	_mergeSw = On;

		else										_mergeSw = Off;

		if( OK != analizeWaveForm((UCHR*)*(argv + 1)) )

			exit( -1 );					/*Error termination*/

		break;

	  default:	/* パラメータ無しの場合 */

		printf("DL750のバイナリーファイルをASCIIファイルに変換するツール  wvfconv.exe \n");

		printf("                  copyright 2017 (c) Takahiko Kobayashi, Kitajima Lab.\n");
//		printf("                               2017.3.14 Takahiko Kobayashi, Kitajima Lab.\n");
		printf( "【使用方法】\n");

		printf( " ana 波形データ名 [オプション] \n");

		printf( "     [オプション] 出力スタイルを 0/1/2/3 から選択します。\n");

		printf( "                   無指定の場合は 0 のスタイルで出力します。\n");

		printf( "                   0 ... 物理値 \n");

		printf( "                   1 ... 物理値 単位\n");

		printf( "                   2 ... データ番号 物理値 単位\n");

		printf( "                   3 ... データ番号 物理値 単位 生データ \n");

//		printf( "     [オプション2] トレース出力スタイルを 選択します。\n");

//		printf( "                   無指定の場合は トレースを縦に出力します。\n");

//		printf( "                   mを指定すると横展開します。\n");

		printf( "     （注）出力は標準出力\n");

		printf( "           ファイル出力の場合はリダイレクションで指定\n");

		printf( " ana dat0001a                  ... 変換後標準出力\n");

//		printf( " ana dat0001a m                ... 変換後標準出力(横展開)\n");

		printf( " ana dat0001a   > dat0001a.csv ... 変換後dat0001a.csvに出力\n");

		printf("このソフトウェアは教育利用の範囲で下記ソフトウェアを元に製作されました\n");
		printf("バイナリーファイルをＡＳＣＩＩファイルに変換するツール  ana.exe \n");

		printf("                      copyright 1996 (c) Yokogawa Electric Corporation\n");


		exit( -1 );						/*Error termination*/

	}

	exit( 0 );							/*Succsessful termination*/

}





/*STARTF*****************************************************************

*																		*

*	関　数　名	:	analizeWaveForm										*

*																		*

*	機		能	:	解析メイン処理										*

*																		*

*	書　　　式　:	INT	analizeWaveForm( UCHR* fileName )				*

*																		*

*	入力パラメタ:	UCHR*	fileName	: ファイル名					*

*																		*

*	出力パラメタ:	None												*

*																		*

*	返		値	:	有効	OK		無効	ERROR						*

*																		*

*ENDF*******************************************************************/

INT analizeWaveForm( UCHR* fileName )

{

	/* 開始メッセージ */

//	fprintf( stderr, "バイナリーファイルをＡＳＣＩＩファイルに変換するツール  analize.exe \n" );

//	fprintf( stderr, "       **********    ANA.EXE Version 1.04    ********** \n" );
	fprintf(stderr, "");


	/* ＡＳＣＩＩファイルのオープン */

	if( NULL == ( ascFp = openFile( fileName, ( UCHR )AscFile ))){

		printf( "Error ascii file open \n" );

	    return( ERROR );

	}

	/* バイナリーファイルのオープン */

	if( NULL == ( binFp = openFile( fileName, ( UCHR )BinFile ))){

		printf( "Error binary file open \n" );

	    return( ERROR );

	}

	/* 一時ファイルのオープン */

	if( _mergeSw == On ){

		if( tmpnam( t1_fname ) == NULL ){

			printf( "Error temp file create \n" );

			return( ERROR );

		}

		if(( t1_fp = fopen( t1_fname, "w" )) == NULL ){

			remove( t1_fname );

			printf( "Error temp file open \n" );

			return( ERROR );

		}

	}


	/* 情報部（$PublicInfo）の取得 */

	if( OK != getInformation( &_information, ascFp )){

		printf( "Error inforamation \n" );

		return( ERROR );

	}

	/* 波形データの解析 */

	if( OK != analizeAscAndBin( &_information, &_analize, ascFp, binFp )){

		printf( "Error anlalize \n" );

	    return( ERROR );

	}


	/* ＡＳＣＩＩファイルのクローズ */

	if( fclose( ascFp ) == EOF ){

		printf( "Error ascii file close \n" );

		return( ERROR );

	}

	/* バイナリーファイルのクローズ */

	if( fclose( binFp ) == EOF ){

		printf( "Error binary file close \n" );

		return( ERROR );

	}

	

	/* マージオプション時生成した内容の表示 */

	if( _mergeSw == On ){

		strcpy( _buffer, _typeCMD );

		strcat( _buffer, t1_fname );

		system( _buffer );

		remove( t1_fname );

	}


	return( OK );

}


/*STARTF*****************************************************************

*																		*

*	関　数　名	:	analizeAscAndBin									*

*																		*

*	機		能	:	波形データの解析処理								*

*																		*

*	書　　　式　:	INT	analizeAscAndBin( INF* infP, ANRZ* analizeP		*

*										  FILE* ascFp, FILE* binFp )	*

*																		*

*	入力パラメタ:	INF*	infP	: 情報部($PublicInfo)のポインター	*

*					ANRZ*	analizeP:       ($Group)のポインター		*

*					FILE*	ascFp	: ＡＳＣＩＩファイルのポインター	*

*					FILE*	binFp	: 波形データファイルのポインター	*

*																		*

*	出力パラメタ:	ANRZ*	analizeP: 結果								*

*																		*

*	返		値	:	有効	OK		無効	ERROR						*

*																		*

*ENDF*******************************************************************/

INT analizeAscAndBin( INF* infP, ANRZ* analizeP, FILE* ascFp, FILE* binFp )

{

	INT		traceNumber;

	INT		blockNumber;

	INT		j, k;

	UINT	i;


	for( i = 0 ; i < infP->groupNumber ; i++ ){ /* グループの数分ループする */

		/* トレースの数とブロック番号を得る */

		if( OK != getGroupInf( i, &traceNumber, &blockNumber, ascFp )){

			return( ERROR );

		}

		for( j = 0 ; j < traceNumber ; j++ ){

			/* トレース名を得る */

			if( OK != getTraceInf( analizeP, i, j, ascFp )){

			    return( ERROR );

			}

			for( k = 0 ; k < blockNumber ; k++ ){

				/* ブロック情報を得る */

				if( OK != getBlockInf( analizeP, i, j, k, ascFp ))

				    return( ERROR );

				/* バイナリー（波形データ）の解析 */

				if( OK != analizeBin( infP, analizeP, i, j, k, ascFp, binFp ))

				    return( ERROR );

			}

		}

	}

	return( OK );

}


/*STARTF*****************************************************************

*																		*

*	関　数　名	:	getInformation										*

*																		*

*	機		能	:	情報部の取得										*

*																		*

*	書　　　式　:	INT	getInformation( INF* infP, FILE* ascFp )		*

*																		*

*	入力パラメタ:	INF*	infP	: 出力先ポインター					*

*					FILE*	ascFp	: ＡＳＣＩＩファイルのポインター	*

*																		*

*	出力パラメタ:	INF*	infP	: ＡＳＣＩＩファイルからの情報		*

*																		*

*	返		値	:	有効	OK		無効	ERROR						*

*																		*

*ENDF*******************************************************************/

/*

	ここでは、$PublicInfoの部分の情報を取得します。


		FormatVersion		ＡＳＣＩＩファイルのフォーマットバージョン

		Model				モデル名

		DisplayPointNo		表示開始データ点

		DisplayBlockSize	メモリー長

		Endian				エンディアンモード

		DataFormat			波形データの記述方式

		GroupNumber			グループ数

		DataOffset			有効データの先頭からのオフセット値


*/

INT getInformation( INF* infP, FILE* ascFp )

{

	/* 【FormatVersionを得る】 */

	if( OK != work( _FormatVersion, infP->formatVersion, ( UCHR )PublicMode,

					( INT )NoGroupData, 0, ( INT )NoBlockData, ascFp )){

		printf( "Error FormatVersion \n" );

		return( ERROR );	/* 取得できなかった */

	}

	/* 【Modelを得る】 */

	if( OK != work( _Model, infP->model, ( UCHR )PublicMode,

					( INT )NoGroupData, 0, ( INT )NoBlockData, ascFp )){

		printf( "Error Model \n" );

		return( ERROR );	/* 取得できなかった */

	}

	/* 【DisplayPointNoを得る】 */

	if( OK == work( _DisplayPointNo, _destBuffer, ( UCHR )NonPublicMode,

					( INT )NoGroupData, 0, ( INT )NoBlockData, ascFp )){

		infP->displayPointNo = atol(( CHR* )_destBuffer );

		if ( infP->displayPointNo == 0 ) infP->displayPointNo = 1;

	}

	else{

		 infP->displayPointNo = 1;	/* 取得できなかった */

	}

	/* 【DisplayBlockSizeを得る】 */

	if( OK == work( _DisplayBlockSize, _destBuffer, ( UCHR )NonPublicMode,

					( INT )NoGroupData, 0, ( INT )NoBlockData, ascFp )){

		infP->displayBlockSize = atol(( CHR* )_destBuffer );

	}

	else

		infP-> displayBlockSize = NoDispBlock;	/* 取得できなかった */


	/* 【Endianを得る】 */

	if( OK == work( _Endian, _destBuffer, ( UCHR )PublicMode,

					( INT )NoGroupData, 0, ( INT )NoBlockData, ascFp )){

		if( 0 == strcmp(( CHR* )_BigEndian, ( CHR* )_destBuffer )){

			/* Ｂｉｇエンディアンの場合 */

			getEndianMode( infP, ( UCHR )BigEndian );

		}

		else{

			if( 0 == strcmp(( CHR* )_LittleEndian, ( CHR* )_destBuffer )){

			/* Ｌｉｔｔｌｅエンディアンの場合 */

				getEndianMode( infP, ( UCHR )LittleEndian );

			}

			else

			/* どちらでもない場合 */

				printf( "%s Spell Miss\n", _Endian );

		}

	}

	else{

		return( ERROR );	/* 処理の打ち切り */

	}


	/* 【DataFormatを得る】 */

	if( OK == work( _DataFormat, _destBuffer, ( UCHR )PublicMode,

					( INT )NoGroupData, 0, ( INT )NoBlockData, ascFp )){

		if( 0 == strcmp(( CHR* )_Trace, ( CHR* )_destBuffer )){

			/* Traceデータの場合 */

		    infP->dataFormat = ( UCHR )TraceUnit;

		}

		else{

			/* Blockデータの場合 */

			if( 0 == strcmp(( CHR* )_Block, ( CHR* )_destBuffer ))

			    infP->dataFormat = ( UCHR )BlockUnit;

			else

			/* どちらでもない場合 */

				printf( "%s Spell Miss\n", _DataFormat );

		}

	}

	else

		return( ERROR );	/* 処理の打ち切り */


	/* 【GroupNumberを得る】 */

	if( OK == work( _GroupNumber, _destBuffer, ( UCHR )PublicMode,

					( INT )NoGroupData, 0, ( INT )NoGroupData, ascFp )){

		infP->groupNumber = atol(( CHR* )_destBuffer );

	}

	else{

		return( ERROR );	/* 処理の打ち切り */

	}


	/* 【DataOffsetを得る】 */

	if( OK == work( _DataOffset, _destBuffer, ( UCHR )PublicMode,

					( INT )NoGroupData, 0, ( INT )NoGroupData, ascFp )){

		infP->dataOffset = atol(( CHR* )_destBuffer );

	}

	else{

		return( ERROR );	/* 処理の打ち切り */

	}

	

	return( OK );

}


/*STARTF*****************************************************************

*																		*

*	関　数　名	:	getGroupInf											*

*																		*

*	機		能	:	グループ情報を得る									*

*																		*

*	書　　　式　:	INT	getGroupInf( INT group, INT* traceNumber,		*

*									 INT* blockNumber, FILE* ascFp )	*

*																		*

*	入力パラメタ:	INT		group		: グループ番号					*

*					FILE*	ascFp		: ＡＳＣＩＩファイルポインター	*

*																		*

*	出力パラメタ:	INT*	traceNumber	: トレース数					*

*					INT*	blockNumber	: ブロック番号					*

*																		*

*	返		値	:	有効	OK		無効	ERROR						*

*																		*

*ENDF*******************************************************************/

/*

	ここでは、$Groupの部分の情報を取得します。


		TraceNumber		トレース数

		BlockNumber		ブロック番号


*/

INT getGroupInf( INT group, INT* traceNumber, INT* blockNumber, FILE* ascFp )

{

	/* 【TraceNumberを得る】 */

	if( OK == work( _TraceNumber, _destBuffer, ( UCHR )PublicMode,

					group, 0, ( INT )NoBlockData, ascFp )){

		*traceNumber = atol(( CHR* )_destBuffer );

	}

	else{

		return( ERROR );

	}

	/* 【BlockNumberを得る】 */

	if( OK == work( _BlockNumber, _destBuffer, ( UCHR )PublicMode,

					group, 0, ( INT )NoBlockData, ascFp )){

		*blockNumber = atol(( CHR* )_destBuffer );

	}

	else{

		return( ERROR );

	}

	return( OK );

}


/*STARTF*****************************************************************

*																		*

*	関　数　名	:	getTraceInf											*

*																		*

*	機		能	:	グループ情報を得る									*

*																		*

*	書　　　式　:	INT	getTraceInf( ANRZ* analizeP, INT group,			*

*									 INT trace, FILE* ascFp )			*

*																		*

*	入力パラメタ:	ANRZ*	analizeP	: 情報部のポインター			*

*					INT		group		: グループ番号					*

*					INT		trace		: トレース番号					*

*					FILE*	ascFp		: ＡＳＣＩＩファイルのポインター*

*																		*

*	出力パラメタ:	ANRZ*	analize		: 結果							*

*																		*

*	返		値	:	有効	OK		無効	ERROR						*

*																		*

*ENDF*******************************************************************/

/*

	ここでは、$Groupの部分の情報を取得します。


		TraceName		トレース名


*/

INT getTraceInf( ANRZ* analizeP, INT group, INT trace, FILE* ascFp )

{

	/* 【TrceNameを得る】 */

	if( OK != work( _TraceName, analizeP->traceName, ( UCHR )PublicMode,

					group, trace, 0, ascFp )){

		return( ERROR );

	}

	return( OK );

}


/*STARTF*****************************************************************

*																		*

*	関　数　名	:	getBlockInf											*

*																		*

*	機		能	:	グループ情報を得る									*

*																		*

*	書　　　式　:	INT	getBlockInf( ANRZ* analizeP, INT group, 		*

*									 INT trace, INT block, FILE* ascFp )*

*																		*

*	入力パラメタ:	ANRZ*	analizeP	: 情報部のポインター			*

*					INT		group		: グループ番号					*

*					INT		trace		: トレース番号					*

*					INT		block		: ブロック番号					*

*					FILE*	ascFp		: ＡＳＣＩＩファイルのポインター*

*																		*

*	出力パラメタ:	ANRZ*	analize		: 結果							*

*																		*

*	返		値	:	有効	OK		無効	ERROR						*

*																		*

*ENDF*******************************************************************/

/*

	ここでは、$Groupの部分の情報を取得します。


		BlockSize			ブロックサイズ

		VResolution			Ｙ軸変換式の係数

		VOffset				Ｙ軸のオフセット値

		VDataType			データのタイプ

		VUnit				Ｙ軸の単位

		VPlusOverData		エラーデータのしきい値

		VMinusOverData		          〃

		VIllegalData		非表示コードのデータ

		VMaxData			最大値データ

		VMinData			最小値データ

		HResolution			Ｘ軸変換式の係数

		HOffset				Ｘ軸のオフセット値

		HUnit				Ｘ軸の単位

		Date				トリガ日付

		Time				トリガ時刻


*/


INT getBlockInf( ANRZ* analizeP, INT group, INT trace, INT block, FILE* ascFp )

{

	/* 【BlockSizeを得る】 */

	if( OK == work( _BlockSize, _destBuffer, ( UCHR )PublicMode,

					group, trace, block, ascFp )){

	    analizeP->blockSize = atol(( CHR* )_destBuffer );

	}

	else{

		return( ERROR );

	}

	/* 【VResolutionを得る】 */

	if( OK == work( _VResolution, _destBuffer, ( UCHR )PublicMode,

					group, trace, block, ascFp )){

		analizeP->vResolution = atof(( CHR* )_destBuffer );

	}

	else{

		return( ERROR );

	}

	/* 【VOffsetを得る】 */

	if( OK == work( _VOffset, _destBuffer, ( UCHR )PublicMode,

					group, trace, block, ascFp )){

		analizeP->vOffset	= atof(( CHR* )_destBuffer );

	}

	else{

		return( ERROR );

	}

	/* 【VDataTypeを得る】 */

	if( OK != work( _VDataType, analizeP->vDataType, ( UCHR )PublicMode,

					group, trace, block, ascFp ))

		return( ERROR );

	/* 【VUnitを得る】*/

	if( OK != work( _VUnit, analizeP->vUnit, ( UCHR )PublicMode,

					group, trace, block, ascFp ))

	    return( ERROR );

	/* 【VPlusOverDataを得る】*/

	if( OK == work( _VPlusOverData, _destBuffer, ( UCHR )PublicMode,

					group, trace, block, ascFp )){

		analizeP->vPlusOverData = atof(( CHR* )_destBuffer );

	}

	else{

		return( ERROR );

	}

	/* 【VMinusOverDataを得る】 */

	if( OK == work( _VMinusOverData, _destBuffer, ( UCHR )PublicMode,

					group, trace, block, ascFp )){

		analizeP->vMinusOverData = atof(( CHR* )_destBuffer );

	}

	else{

		return( ERROR );

	}

	/* 【VIllegalDataを得る】 */

	if( OK == work( _VIllegalData, _destBuffer, ( UCHR )PublicMode,

					group, trace, block, ascFp )){

		analizeP->vIllegalData = atof(( CHR* )_destBuffer );

	}

	else{

		return( ERROR );

	}

	/* 【VMaxDataを得る】 */

	if( OK == work( _VMaxData, _destBuffer, ( UCHR )PublicMode,

					group, trace, block, ascFp )){

		analizeP->vMaxData = atof(( CHR* )_destBuffer );

	}

	else{

		return( ERROR );

	}

	/* 【VMinDataを得る】 */

	if( OK == work( _VMinData, _destBuffer, ( UCHR )PublicMode,

					group, trace, block, ascFp )){

		analizeP->vMinData = atof(( CHR* )_destBuffer );

	}

	else{

		return( ERROR );

	}

	/* 【HResolutionを得る】 */

	if( OK == work( _HResolution, _destBuffer, ( UCHR )PublicMode,

					group, trace, block, ascFp )){

		analizeP->hResolution = atof(( CHR* )_destBuffer );

	}

	else{

		return( ERROR );

	}

	/* 【HOffsetを得る】 */

	if( OK == work( _HOffset, _destBuffer, ( UCHR )PublicMode,

					group, trace, block, ascFp )){

		analizeP->hOffset	= atof(( CHR* )_destBuffer );

	}

	else{

		return( ERROR );

	}

	/* 【HUnitを得る】 */

	if( OK != work( _HUnit, analizeP->hUnit, ( UCHR )PublicMode,

					group, trace, block, ascFp ))

	    return( ERROR );

	/* 【Dateを得る】 */

	if( OK != work( _Date, analizeP->date, ( UCHR )PublicMode,

					group, trace, block, ascFp ))

		return( ERROR );

	/* 【Timeを得る】 */

	if( OK != work( _Time, analizeP->time, ( UCHR )PublicMode,

					group, trace, block, ascFp ))

		return( ERROR );



	return( OK );

}


/*STARTF*****************************************************************

*																		*

*	関　数　名	:	analizeBin											*

*																		*

*	機		能	:	バイナリー（波形データ）ファイルの解析				*

*																		*

*	書　　　式　:	INT	analizeBin( INF* infP, ANRZ* analizeP,			*

*									INT group, INT trace, INT block,	*

*									FILE* ascFp, FILE*binFp )			*

*																		*

*	入力パラメタ:	INF*	infPP		: 情報部のポインター			*

*					ANRZ*	analizeP	: 情報部のポインター			*

*					INT		group		: グループ番号					*

*					INT		trace		: トレース番号					*

*					INT		block		: ブロック番号					*

*					FILE*	ascFp		: ＡＳＣＩＩファイルのポインター*

*					FILE*	binFp		: バイナリーファイルのポインター*

*																		*

*	出力パラメタ:	None												*

*																		*

*	返		値	:	有効	OK		無効	ERROR						*

*																		*

*ENDF*******************************************************************/

INT analizeBin( INF* infP, ANRZ* analizeP, INT group, INT trace, INT block,

				FILE* ascFp, FILE* binFp )

{

	/* バイナリーファイルの指定場所にシークする */

 	if( OK != seekBinFp( infP, group, trace, block, ascFp, binFp ))

	    return( ERROR );

	return( readAndDispWaveForm( infP, analizeP, group, trace, block, binFp ));

}


/*STARTF*****************************************************************

*																		*

*	関　数　名	:	readAndDispWaveForm									*

*																		*

*	機		能	:	波形データを読み表示								*

*																		*

*	書　　　式　:	INT	readAndDispWaveForm( INF* infP, ANRZ* analizeP,	*

*									 		 INT group, INT trace,		*

*											 INT block, FILE* binFp )	*

*																		*

*	入力パラメタ:	INF*	infP		: 情報部のポインター			*

*					ANRZ*	analizeP	: 情報部のポインター			*

*					INT		group		: グループ番号					*

*					INT		trace		: トレース番号					*

*					INT		block		: ブロック番号					*

*					FILE*	binFp		: バイナリーファイルのポインター*

*																		*

*	出力パラメタ:	None												*

*																		*

*	返		値	:	有効	OK		無効	ERROR						*

*																		*

*ENDF*******************************************************************/

INT readAndDispWaveForm( INF* infP, ANRZ* analizeP, INT group, INT trace, INT block, FILE* binFp )

{

	DREAL	data, result;

	INT		i, loop;


	if( 0 == analizeP->blockSize )	return( OK );


	if( _fileSw == On ){

		/* 一時ファイルのクローズ＆オープン */

		if( _mergeSw == On ){

			if( tmpnam( t2_fname ) == NULL ){					/* 書き込みファイル名を取得する */

				printf( "Error temp file create \n" );

				exit( -1 );

			}

			/* temp1とtem2の入れ替え	*/

			/*     temp1は書き込み専用	*/

			/*     temp2は読み込み専用	*/

			strcpy( t_fname,  t1_fname );

			strcpy( t1_fname, t2_fname );

			strcpy( t2_fname, t_fname  );

			

			if(( t1_fp = fopen( t1_fname, "w" )) == NULL ){		/* 結果を書き込むファイルをオープンする */

				remove( t1_fname );

				printf( "Error temp file open \n" );

				exit( -1 );

			}

			if(( t2_fp = fopen( t2_fname, "r" )) == NULL ){		/* 前回書き込んだファイルをオープンする */

				remove( t2_fname );

				printf( "Error temp file open \n" );

				exit( -1 );

			}

		}

	}


	/* データ数を求める */

	if ( infP->displayBlockSize == NoDispBlock )

	    loop =  analizeP->blockSize;

	else

	    loop =  infP->displayBlockSize;



	for( i = 0 ; i < loop ; i++ ){

		/* データの読み込み */

		if( OK != readBinFile( &data, infP, analizeP, binFp )){

			return( ERROR );

		}

		else{

			binToValue( &result, analizeP, data );	/* 物理値変換 */

			_lineBuffer[0] = '\0';

			if( _style == 0 ){

				/* 物理値のタイプ */

				if( analizeP->vDataType[0] == 'B' ){

					/* ビットデータの場合 */

					if( !i ){

						/* 初回だけの処理（タイトル）*/

						readPreviousData();	/* マージオプションの場合に前回のデータをバッファの先頭にセットする */

						sprintf( &_lineBuffer[strlen(_lineBuffer)], "%s,,,,,,,,,\n", analizeP->traceName );/* トレース名 */

						outputTo();		/* 出力 */

						readPreviousData();	/* マージオプションの場合に前回のデータをバッファの先頭にセットする */

						sprintf( &_lineBuffer[strlen(_lineBuffer)], "Result,,,,,,,,,\n" );/* 物理値 */

						outputTo();		/* 出力 */

						readPreviousData();	/* マージオプションの場合に前回のデータをバッファの先頭にセットする */

						sprintf( &_lineBuffer[strlen(_lineBuffer)], "(bit8),(bit7),(bit6),(bit5),(bit4),(bit3),(bit2),(bit1),\n" );

						outputTo();		/* 出力 */

					}

					readPreviousData();	/* マージオプションの場合に前回のデータをバッファの先頭にセットする */

					printBitType( result, analizeP );	/* ビット文字列の作成 */

					sprintf( &_lineBuffer[strlen(_lineBuffer)], "\n" );

					outputTo();		/* 出力 */

				}

				else{

					/* ビットデータ以外の場合 */

					if( !i ){

						/* 初回だけの処理（タイトル）*/

						readPreviousData();	/* マージオプションの場合に前回のデータをバッファの先頭にセットする */

						sprintf( &_lineBuffer[strlen(_lineBuffer)], "%s,\n", analizeP->traceName );/* トレース名 */

						outputTo();		/* 出力 */

						readPreviousData();	/* マージオプションの場合に前回のデータをバッファの先頭にセットする */

						sprintf( &_lineBuffer[strlen(_lineBuffer)], "Result,\n" );		/* 物理値 */

						outputTo();		/* 出力 */

					}

					readPreviousData();	/* マージオプションの場合に前回のデータをバッファの先頭にセットする */

					sprintf( &_lineBuffer[strlen(_lineBuffer)], "%-14.7E,\n", result );

					outputTo();		/* 出力 */

				}

			}

			else if( _style == 1 ){

				/* 物理値 単位文字のタイプ */

				if( analizeP->vDataType[0] == 'B' ){

					/* ビットデータの場合 */

					if( !i ){

						/* 初回だけの処理（タイトル）*/

						readPreviousData();	/* マージオプションの場合に前回のデータをバッファの先頭にセットする */

						sprintf( &_lineBuffer[strlen(_lineBuffer)], "%s,,,,,,,,,\n", analizeP->traceName );/* トレース名 */

						outputTo();		/* 出力 */

						readPreviousData();	/* マージオプションの場合に前回のデータをバッファの先頭にセットする */

						sprintf( &_lineBuffer[strlen(_lineBuffer)], "Result,,,,,,,,Unit,\n" );/* 物理値 単位 */

						outputTo();		/* 出力 */

						readPreviousData();	/* マージオプションの場合に前回のデータをバッファの先頭にセットする */

						sprintf( &_lineBuffer[strlen(_lineBuffer)], "(bit8),(bit7),(bit6),(bit5),(bit4),(bit3),(bit2),(bit1),\n" );

						outputTo();		/* 出力 */

					}

					readPreviousData();	/* マージオプションの場合に前回のデータをバッファの先頭にセットする */

					printBitType( result, analizeP );	/* ビット文字列の作成 */

					sprintf( &_lineBuffer[strlen(_lineBuffer)], "%s,\n", analizeP->vUnit );	/* 単位文字列の作成 */

					outputTo();		/* 出力 */

				}

				else{

					/* ビットデータ以外の場合 */

					if( !i ){

						/* 初回だけの処理（タイトル）*/

						readPreviousData();	/* マージオプションの場合に前回のデータをバッファの先頭にセットする */

						sprintf( &_lineBuffer[strlen(_lineBuffer)], "%s,,\n", analizeP->traceName );/* トレース名 */

						outputTo();		/* 出力 */

						readPreviousData();	/* マージオプションの場合に前回のデータをバッファの先頭にセットする */

						sprintf( &_lineBuffer[strlen(_lineBuffer)], "Result,Unit,\n" );		/* 物理値 単位 */

						outputTo();		/* 出力 */

						readPreviousData();	/* マージオプションの場合に前回のデータをバッファの先頭にセットする */

						sprintf( &_lineBuffer[strlen(_lineBuffer)], ",,\n" );				/* 物理値 単位 */

						outputTo();		/* 出力 */

					}

					readPreviousData();	/* マージオプションの場合に前回のデータをバッファの先頭にセットする */

					sprintf( &_lineBuffer[strlen(_lineBuffer)], "%-14.7E,%s,\n", result, analizeP->vUnit );

					outputTo();		/* 出力 */

				}

			}

			else if( _style == 2 ){

				/* データ番号 物理値 単位文字のタイプ */

				if( analizeP->vDataType[0] == 'B' ){

					/* ビットデータの場合 */

					if( !i ){

						/* 初回だけの処理（タイトル）*/

						readPreviousData();	/* マージオプションの場合に前回のデータをバッファの先頭にセットする */

						sprintf( &_lineBuffer[strlen(_lineBuffer)], "%s,,,,,,,,,,\n", analizeP->traceName );/* トレース名 */

						outputTo();		/* 出力 */

						readPreviousData();	/* マージオプションの場合に前回のデータをバッファの先頭にセットする */

						sprintf( &_lineBuffer[strlen(_lineBuffer)], "Point,Result,,,,,,,,Unit,\n" );/* 点数 物理値 単位 */

						outputTo();		/* 出力 */

						readPreviousData();	/* マージオプションの場合に前回のデータをバッファの先頭にセットする */

						sprintf( &_lineBuffer[strlen(_lineBuffer)], ",(bit8),(bit7),(bit6),(bit5),(bit4),(bit3),(bit2),(bit1),\n");

						outputTo();		/* 出力 */

					}

					readPreviousData();	/* マージオプションの場合に前回のデータをバッファの先頭にセットする */

					sprintf( &_lineBuffer[strlen(_lineBuffer)], "%ld,\0", i );

					printBitType( result, analizeP );	/* ビット文字列の作成 */

					sprintf( &_lineBuffer[strlen(_lineBuffer)], "%s,\n", analizeP->vUnit );

					outputTo();		/* 出力 */

				}

				else{

					if( !i ){

						/* 初回だけの処理（タイトル）*/

						readPreviousData();	/* マージオプションの場合に前回のデータをバッファの先頭にセットする */

						sprintf( &_lineBuffer[strlen(_lineBuffer)], "%s,,,\n", analizeP->traceName );/* トレース名 */

						outputTo();		/* 出力 */

						readPreviousData();	/* マージオプションの場合に前回のデータをバッファの先頭にセットする */

						sprintf( &_lineBuffer[strlen(_lineBuffer)], "Point,Result,Unit,\n" );	/* 点数 物理値 単位 */

						outputTo();		/* 出力 */

						readPreviousData();	/* マージオプションの場合に前回のデータをバッファの先頭にセットする */

						sprintf( &_lineBuffer[strlen(_lineBuffer)], ",,,\n" );					/* 点数 物理値 単位 */

						outputTo();		/* 出力 */

					}

					readPreviousData();	/* マージオプションの場合に前回のデータをバッファの先頭にセットする */

					sprintf( &_lineBuffer[strlen(_lineBuffer)], "%ld,%-14.7E,%s,\n", i, result, analizeP->vUnit );

					outputTo();		/* 出力 */

				}

			}

			else{

				/* データ番号 物理値 単位文字 生データのタイプ */

				if( analizeP->vDataType[0] == 'B' ){

					/* ビットデータの場合 */

					if( !i ){

						/* 初回だけの処理（タイトル）*/

						readPreviousData();	/* マージオプションの場合に前回のデータをバッファの先頭にセットする */

						sprintf( &_lineBuffer[strlen(_lineBuffer)], "%s,,,,,,,,,,,\n", analizeP->traceName );/* トレース名 */

						outputTo();		/* 出力 */

						readPreviousData();	/* マージオプションの場合に前回のデータをバッファの先頭にセットする */

						sprintf( &_lineBuffer[strlen(_lineBuffer)], "Point,Result,,,,,,,,Unit,Binary,\n" );

																								/* 点数 物理値 単位 元データ */

						outputTo();		/* 出力 */

						readPreviousData();	/* マージオプションの場合に前回のデータをバッファの先頭にセットする */

						sprintf( &_lineBuffer[strlen(_lineBuffer)], ",(bit8),(bit7),(bit6),(bit5),(bit4),(bit3),(bit2),(bit1),\n");

						outputTo();		/* 出力 */

					}

					readPreviousData();	/* マージオプションの場合に前回のデータをバッファの先頭にセットする */

					sprintf( &_lineBuffer[strlen(_lineBuffer)], "%ld,\0", i );

					printBitType( result, analizeP );	/* ビット文字列の作成 */

					sprintf( &_lineBuffer[strlen(_lineBuffer)], "%s,%d(%#x),\n", analizeP->vUnit, (int)result, (int)result );

					outputTo();		/* 出力 */

				}

				else{

					if( !i ){

						/* 初回だけの処理（タイトル）*/

						readPreviousData();	/* マージオプションの場合に前回のデータをバッファの先頭にセットする */

						sprintf( &_lineBuffer[strlen(_lineBuffer)], "%s,,,,\n", analizeP->traceName );/* トレース名 */

						outputTo();		/* 出力 */

						readPreviousData();	/* マージオプションの場合に前回のデータをバッファの先頭にセットする */

						sprintf( &_lineBuffer[strlen(_lineBuffer)], "Point,Result,Unit,Binary,\n" );/* 点数 物理値 単位 元データ */

						outputTo();		/* 出力 */

						readPreviousData();	/* マージオプションの場合に前回のデータをバッファの先頭にセットする */

						sprintf( &_lineBuffer[strlen(_lineBuffer)], ",,,,\n" );						/* 点数 物理値 単位 元データ */

						outputTo();		/* 出力 */

					}

					readPreviousData();	/* マージオプションの場合に前回のデータをバッファの先頭にセットする */

					sprintf( &_lineBuffer[strlen(_lineBuffer)], "%ld,%-14.7E,%s,%-14.7E,\n", i, result, analizeP->vUnit, data );

					outputTo();		/* 出力 */

				}

			}

		}

	}

	if( _mergeSw == On ){

		if( fclose( t1_fp ) == EOF ){				/* 書き込みファイルのクローズ */

			printf( "Error temp file close \n" );

			exit( -1 );

		}

	}

	if( _mergeSw == On && _fileSw == On ){

		if( fclose( t2_fp ) == EOF ){				/* 読み込みファイルのクローズ */

			printf( "Error temp file close \n" );

			exit( -1 );

		}

		remove( t2_fname );

	}

	_fileSw = On;

	return( OK );

}


/*STARTF*****************************************************************

*																		*

*	関　数　名	:	printBitType										*

*																		*

*	機		能	:	ビットタイプの印字									*

*																		*

*	書　　　式　:	INT	printBitType( DREAL data, ANRZ* analizeP )		*

*																		*

*	入力パラメタ:	DREAL	data		: 印字データ					*

*					ANRZ*	analizeP	: 情報部のポインター			*

*																		*

*	出力パラメタ:	None												*

*																		*

*	返		値	:	有効	OK		無効	ERROR						*

*																		*

*ENDF*******************************************************************/

INT printBitType( DREAL data, ANRZ* analizeP )

{

	UINT		bitData;

	INT			i;


	bitData = (UINT)data;

	for( i = 0; i < BitCount; i++ ){

		if( bitData & 0x80 ){

			sprintf( &_lineBuffer[strlen( _lineBuffer )], "1,\0" );

		}

		else{

			sprintf( &_lineBuffer[strlen( _lineBuffer )], "0,\0" );

		}

		bitData <<= 1;

	}

	return( OK );

}


/*STARTF*****************************************************************

*																		*

*	関　数　名	:	readPreviousData									*

*																		*

*	機		能	:	前回生成したＡＳＣＩＩファイルから読む				*

*																		*

*	書　　　式　:	INT	readPreviousData( )								*

*																		*

*	入力パラメタ:	None												*

*																		*

*	出力パラメタ:	前回のデータを_lineBufferの先頭に読み込む			*

*																		*

*	返		値	:	有効	OK		無効	ERROR						*

*																		*

*ENDF*******************************************************************/

INT	readPreviousData()

{

INT	sts;


	if( _mergeSw == On && _fileSw == On ){

		if( fgets( _readBuffer, sizeof(_readBuffer), t2_fp ) == NULL ){

			sts = ERROR;

		}

		else{

			strcpy( _lineBuffer, _readBuffer );

			_lineBuffer[strlen(_lineBuffer)-1] = '\0';

			sts = OK;

		}

	}

	return( sts );

}


/*STARTF*****************************************************************

*																		*

*	関　数　名	:	outputTo											*

*																		*

*	機		能	:	標準出力とファイル出力								*

*																		*

*	書　　　式　:	INT	outputTo()										*

*																		*

*	入力パラメタ:	None												*

*																		*

*	出力パラメタ:	None												*

*																		*

*	返		値	:	有効	OK		無効	ERROR						*

*																		*

*ENDF*******************************************************************/

INT	outputTo()

{

	if( _mergeSw == On ){

		fputs( _lineBuffer, t1_fp );/* マージオプション時にファイルに出力 */

	}

	else{

		printf( "%s", _lineBuffer );/* 標準出力 */

	}

	_lineBuffer[0] = '\0';

	return( OK );

}


/*STARTF*****************************************************************

*																		*

*	関　数　名	:	getEndianMode										*

*																		*

*	機		能	:	エンディアンモードを得る							*

*						（コンパイルのパラメータ切り替え）				*

*																		*

*	書　　　式　:	INT	getEndianMode( INF* infP, UCHR endianMode )		*

*																		*

*	入力パラメタ:	INF*	infP		: 情報部のポインター			*

*					UCHR	endianMode	: エンディアンモード			*

*																		*

*	出力パラメタ:	INF*	infP		: 結果							*

*																		*

*	返		値	:	有効	OK		無効	ERROR						*

*																		*

*ENDF*******************************************************************/

void getEndianMode( INF* infP, UCHR endianMode )

{

	if(( UCHR )BigEndian == endianMode ){

		/* Ｂｉｇエンディアンの場合 */

		#ifdef BIGENDIAN

			infP->endianMode = ( UCHR )Equal;

		  #else

			infP->endianMode = ( UCHR )NotEqual;

		#endif

	}

	else{

		/* Ｌｉｔｔｌｅエンディアンの場合 */

		#ifdef BIGENDIAN

			infP->endianMode = ( UCHR )NotEqual;

		  #else

			infP->endianMode = ( UCHR )Equal;

		#endif

	}

}


/*STARTF*****************************************************************

*																		*

*	関　数　名	:	openFile											*

*																		*

*	機		能	:	ファイルオープン処理								*

*																		*

*	書　　　式　:	INT	openFile( UCHR* fileName, UCHR mode )			*

*																		*

*	入力パラメタ:	UCHR*	fileName	: ファイル名					*

*					UCHR	mode		: モード						*

*																		*

*	出力パラメタ:	None												*

*																		*

*ENDF*******************************************************************/

FILE* openFile( UCHR* fileName, UCHR mode )

{

	FILE*	fp;

	static	UCHR	openFileName[Buff];


	strcpy(( CHR* )&openFileName[0], ( CHR* )fileName );

	if(( UCHR )AscFile == mode )

		strcat(( CHR* )&openFileName[0], ( CHR* )_ascExt );

	else

		strcat(( CHR* )&openFileName[0], ( CHR* )_binExt );

	if( NULL == ( fp = fopen(( CHR* )&openFileName[0], "rb+" )))

		printf( "\7\nCannot Find Such File : %s\n\n", &openFileName[0] );

	return( fp );

}


/*STARTF*****************************************************************

*																		*

*	関　数　名	:	referLabel											*

*																		*

*	機		能	:	ラベル文字列で検索									*

*																		*

*	書　　　式　:	INT	referLabel( UCHR* label, UCHR groupMode,		*

*									INT group, UCHR* buffP,				*

*									FILE* ascFp )						*

*																		*

*	入力パラメタ:	UCHR*	label		: ラベル文字列ポインター		*

*					UCHR	groupMode	: 検索場所						*

*					INT		group		: グループ番号					*

*					UCHR*	buffP		: 検索対象バッファポインター	*

*					FILE*	ascFp		: ＡＳＣＩＩファイルポインター	*

*																		*

*	出力パラメタ:	None												*

*																		*

*	返		値	:	有効	TRUE		無効	FALSE					*

*																		*

*ENDF*******************************************************************/

INT referLabel( UCHR* label, UCHR groupMode, INT group, UCHR* buffP, FILE* ascFp )

{

	static	UCHR	labelBuffer[Buff];

	UCHR*	frontP;

	UCHR*	labelP;


	frontP = buffP;		/* バッファポインターセーブ */

	/* 次のグループ名文字列の生成 */

	makeGroupString( groupMode, group + 2, &_groupLimitBuffer[0] );


	while( NULL != fgets(( CHR* )buffP, ( SHORT )MaxBuff, ascFp )){

		labelP = &labelBuffer[0];

		while( '\n' !=	*buffP ){	/* 改行が現れるまで繰り返す */

			if( 0 != isspace(( SHORT )*buffP ))

				buffP++;			/* スペースの場合にはポインターを進める */

			else

				break;				/* スペース以外の場合に抜ける */

		}


		/* コメント行の場合にはスキップする */

		if(( '/' == *buffP ) && ( '/' == *( buffP + 1 )))	continue;


		/* スペースが現れるまで文字列をローカルバッファ（labelBuffer）にコピーする */

		while( 0 == isspace(( SHORT )*buffP )){

			*labelP++ = *buffP++;

		}

		*labelP = '\0';


		/* 取得した文字列と指定されたラベル文字列を比較する */

		if( 0 == strcmp(( CHR* )labelBuffer, ( CHR* )label )){

			return( TRUE );

		}

		/* 次のグループ名まで来たら抜ける */

		if( 0 == strcmp(( CHR* )labelBuffer, ( CHR* )_groupLimitBuffer )){

			break;

		}

		buffP = frontP;

	}

	return( FALSE );

}


/*STARTF*****************************************************************

*																		*

*	関　数　名	:	makeGroupString										*

*																		*

*	機		能	:	グループ名の文字列生成								*

*																		*

*	書　　　式　:	INT	makeGroupString( UCHR groupMode, INT group, 	*

*										 UCHR* groupBuffP )				*

*																		*

*	入力パラメタ:	UCHR	groupMode	: 作成種($Public or $MediaInfo)	*

*					INT		group		: グループ番号					*

*																		*

*	出力パラメタ:	UCHR*	groupBuffp	: 結果							*

*																		*

*	返		値	:														*

*																		*

*ENDF*******************************************************************/

void makeGroupString( UCHR groupMode, INT group, UCHR* groupBuffP )

{

	UCHR		count[20];	/*group counter*/


	if(( UCHR )PublicMode == groupMode ){

		/* $Group領域用の文字列生成 */

		strcpy(( CHR* )groupBuffP, ( CHR* )_Group );

		sprintf(( CHR* )count, "%d", group );

		strcat(( CHR* )groupBuffP, ( CHR* )count );

	}

	else if(( UCHR )PrivateMode == groupMode ){

		/* $Private領域用の文字列生成 */

		strcpy(( CHR* )groupBuffP, ( CHR* )_PrivateInfo );

	}

	else{

		/* $MGroup領域用の文字列生成 */

	    strcpy(( CHR* )groupBuffP, ( CHR* )_MGroup );

		sprintf(( CHR* )count, "%d", group );

		strcat(( CHR* )groupBuffP, ( CHR* )count );

	}

}


/*STARTF*****************************************************************

*																		*

*	関　数　名	:	getData												*

*																		*

*	機		能	:	パラメータの読み込み								*

*																		*

*	書　　　式　:	INT	getData( UCHR* destP, UCHR* srcP, INT trace )	*

*																		*

*	入力パラメタ:	UCHR*	destP	: ディスティネーションのポインター	*

*					UCHR*	srcP	: ソースのポインター				*

*					INT		trace	: トレース番号						*

*																		*

*	出力パラメタ:	UCHR*	destP	: 結果								*

*																		*

*	返		値	:	有効	OK		無効	ERROR						*

*																		*

*ENDF*******************************************************************/

INT getData( UCHR* destP, UCHR* srcP, INT trace )

{

	UCHR	tmpCh = '\n';

	INT	count = 0;


	if(( INT )NoTraceData == trace )	return( OK );

	while( '\n' !=	*srcP ){

		if( 0 != isspace(( SHORT )*srcP ))

			srcP++;

		else

			break;

	}

	while( 1 ){

		if( 0 == isspace(( SHORT )*srcP )){

			if(( ' ' == tmpCh ) || ( '\t' == tmpCh ))

			    count++;

		}

		if( trace + 1 == count )	break;

		if( '\n' == *srcP )		return( ERROR );

		tmpCh = *srcP++;

	}

	while( 1 ){

		if( 0 != isspace(( SHORT )*srcP ))

			break;

		else

			*destP++ = *srcP++;

	}

	*destP = '\0';

	return( OK );

}


/*STARTF*****************************************************************

*																		*

*	関　数　名	:	referGroup											*

*																		*

*	機		能	:	グループ番号での検索								*

*																		*

*	書　　　式　:	INT	referGroup( UCHR groupMode, INT group,			*

*									FILE* ascFp )						*

*																		*

*	入力パラメタ:	UCHR	groupMode	: 検索場所（$Public/$MediaInfo）*

*					INT		group		: グループ番号					*

*					FILE*	ascFp		: ＡＳＣＩＩファイルポインター	*

*																		*

*	出力パラメタ:	None												*

*																		*

*	返		値	:	有効	OK		無効	ERROR						*

*																		*

*ENDF*******************************************************************/

INT referGroup( UCHR groupMode, INT group, FILE* ascFp )

{

	/* グループ名の生成 */

	makeGroupString( groupMode, group + 1, &_groupBuffer[0] );

	/* 生成したグループ名で検索 */

	if( FALSE == referLabel( &_groupBuffer[0], groupMode, group, _buffer, ascFp ))

	{

		printf( "Can't Find %s\n", _groupBuffer ); 

		return( ERROR );

	}

	return( OK );

}


/*STARTF*****************************************************************

*																		*

*	関　数　名	:	work												*

*																		*

*	機		能	:	ＡＳＣＩＩファイルから指定された情報を抜き出す		*

*																		*

*	書　　　式　:	INT	work( UCHR* label, UCHR* destP, UCHR groupMode	*

*							  INT group, INT trace, INT block,			*

*							  FILE* ascFp )								*

*																		*

*	入力パラメタ:	UCHR*	label		: パラメータラベルのポインター	*

*					UCHR*	destP		: 格納先ポインター				*

*					UCHR	groupMode	: 検索場所						*

*					INT		group		: グループ番号（０～）			*

*					INT		trace		: トレース番号（０～）			*

*					INT		block		: ブロック番号（０～）			*

*					FILR*	ascFp		: ＡＳＣＩＩファイルポインター	*

*																		*

*	出力パラメタ:	UCHR*	destP		: 結果							*

*																		*

*	返		値	:	有効	OK		無効	ERROR						*

*																		*

*ENDF*******************************************************************/

INT work( UCHR* label, UCHR* destP, UCHR groupMode, INT group,

		  INT trace, INT block, FILE* ascFp )

{

	/* ラベル名で検索 */

	if( OK != getParameterData( label, destP, groupMode, group,

								trace, block, NumberMode, ascFp )){

		/* ブロック番号で検索 */

		if( OK != getParameterData( label, destP, groupMode, group,

									trace, block, NoNumberMode, ascFp )){

			/* 見つからなかった */

			if ( groupMode == PublicMode ){

			    printf( "Can't Find %s : Group%d Trace%d Block%d\n",

							label, group + 1, trace + 1, block + 1 );

			}

			return( ERROR );

		}

	}

	return( OK );

}


/*STARTF*****************************************************************

*																		*

*	関　数　名	:	getParameterData									*

*																		*

*	機		能	:	ＡＳＣＩＩファイルから指定された情報を抜き出す		*

*																		*

*	書　　　式　:	INT	work( UCHR* label, UCHR* destP, UCHR groupMode	*

*							  INT group, INT trace, INT block,			*

*							  UCHR mode, FILE* ascFp )					*

*																		*

*	入力パラメタ:	UCHR*	label		: パラメータラベルのポインター	*

*					UCHR*	destP		: 格納先ポインター				*

*					UCHR	groupMode	: 検索場所						*

*					INT		group		: グループ番号（０～）			*

*					INT		trace		: トレース番号（０～）			*

*					INT		block		: ブロック番号（０～）			*

*					UCHR	mode		: 検索モード					*

*					FILR*	ascFp		: ＡＳＣＩＩファイルポインター	*

*																		*

*	出力パラメタ:	UCHR*	destP		: 結果							*

*																		*

*	返		値	:	有効	OK		無効	ERROR						*

*																		*

*ENDF*******************************************************************/

INT getParameterData( UCHR* label, UCHR* destP, UCHR groupMode, INT group,

					  INT trace, INT block, UCHR mode, FILE* ascFp )

{

	static		UCHR	labelBuffer[Buff];

	UCHR		count[20];


	fseek( ascFp, 0L, SEEK_SET );	/* ＡＳＣＩＩファイルの先頭に移動 */


	if(( INT )NoGroupData != group ){

		/* グループ名で検索 */

		if( OK != referGroup( groupMode, group, ascFp )){

			return( ERROR );								/* 見つからなかった */

		}

	}


	/* ブロック名の生成 */

	strcpy(( CHR* )labelBuffer, ( CHR* )label );

	if(( UCHR )NumberMode == mode ){

		sprintf(( CHR* )count, "%d", block + 1 );

		strcat(( CHR* )labelBuffer, ( CHR* )count );

	}


	/* ブロック名で検索 */

	if( FALSE != referLabel( &labelBuffer[0], groupMode, group, _buffer, ascFp )){

		if( OK != getData( destP, _buffer, trace )){

			return( ERROR );

		}

	}

	else{

		return( ERROR );

	}

	return( OK );

}


/*STARTF*****************************************************************

*																		*

*	関　数　名	:	getByte												*

*																		*

*	機		能	:	データタイプからバイト数を計算する					*

*																		*

*	書　　　式　:	INT	getByte( UCHR* dataType )						*

*																		*

*	入力パラメタ:	UCHR*	dataType	: データタイプ文字列のポインター*

*																		*

*	出力パラメタ:	None												*

*																		*

*	返		値	:	バイト数											*

*																		*

*ENDF*******************************************************************/

INT getByte( UCHR* dataType )

{

    UCHR	digitBuff[Buff];

	UCHR*	digitP;

	INT		byte;

	USHORT	typeSw;


	digitP = &digitBuff[0];

	if( *dataType == 'B' )

		typeSw = BitType;

	else

		typeSw = NotBitType;

	

	while( *dataType ){

		if( 0 != isdigit(( SHORT )*dataType )){

			*digitP++ = *dataType;

		}

		dataType++;

	}

	*digitP = '\0';

	if( typeSw == BitType ){

		byte = (atol(( CHR* )&digitBuff[0]))/BitCount;

	}

	else{

		byte = atol(( CHR* )&digitBuff[0] );

	}

	return( byte );

}


/*STARTF*****************************************************************

*																		*

*	関　数　名	:	getSize												*

*																		*

*	機		能	:	ブロックサイズを得る								*

*																		*

*	書　　　式　:	INT	getSize( INT group,INT trace, INT block,		*

*								 INT* size, FILE* ascFp )				*

*																		*

*	入力パラメタ:	INT		group		: グループ番号					*

*					INT		trace		: トレース番号					*

*					INT		block		: ブロック番号					*

*					FILE*	ascFp		: ＡＳＣＩＩファイルのポインター*

*																		*

*	出力パラメタ:	INT*	size		: ブロックサイズ(Byte)			*

*																		*

*	返		値	:	有効	OK		無効	ERROR						*

*																		*

*ENDF*******************************************************************/

INT getSize( INT group, INT trace, INT block, INT* size, FILE* ascFp )

{

	INT		blockSize;

	INT		byte;


	/* ブロックサイズを得る*/

	if( OK == work( _BlockSize, _destBuffer, ( UCHR )PublicMode,

					group, trace, block, ascFp ))

		blockSize = atol(( CHR* )_destBuffer );

	else

		return( ERROR );

	/* データタイプを得る */

	if( OK != work( _VDataType, _destBuffer, ( UCHR )PublicMode,

					group, trace, block, ascFp ))

		return( ERROR );

	byte = getByte( &_destBuffer[0] );

	*size += byte * blockSize;

	return( OK );

}


/*STARTF*****************************************************************

*																		*

*	関　数　名	:	seekBinFp											*

*																		*

*	機		能	:	バイナリーファイルの指定場所にシークする			*

*																		*

*	書　　　式　:	INT	seekBinFp( INF* infP, INT group,INT trace,		*

*								   INT block, FILE* ascFp, FILE* binFp )*

*																		*

*	入力パラメタ:	INF*	infP		: 情報部のポインター			*

*					INT		group		: グループ番号					*

*					INT		trace		: トレース番号					*

*					INT		block		: ブロック番号					*

*					FILE*	ascFp		: ＡＳＣＩＩファイルのポインター*

*					FILE*	binFp		: バイナリーファイルのポインター*

*																		*

*	出力パラメタ:	None												*

*																		*

*	返		値	:	有効	OK		無効	ERROR						*

*																		*

*ENDF*******************************************************************/

INT seekBinFp( INF* infP, INT group, INT trace, INT block, FILE* ascFp, FILE* binFp )

{

	INT		seekSize = 0;


	/* トレースタイプの場合 */

	if(( UCHR )TraceUnit == infP->dataFormat ){

		/* シークサイズを求める */

		if( OK != getTraceSeekSize( group, trace, block, &seekSize, ascFp ))

		    return( ERROR );

	}

	/* ブロックタイプの場合 */

	else{

		/* シークサイズを求める */

		if( OK != getBlockSeekSize( infP, group, trace, block, &seekSize, ascFp ))

		    return( ERROR );

	}

	/* 求まったシークサイズにオフセット量の調整を行う */

	seekSize += infP->dataOffset;

	/* シークする */

	fseek( binFp, seekSize, SEEK_SET );

	return( OK );

}


/*STARTF*****************************************************************

*																		*

*	関　数　名	:	getTraceSeekSize									*

*																		*

*	機		能	:	シークサイズ（トレースタイプ）を求める				*

*																		*

*	書　　　式　:	INT	getTraceSeekSize( INT group, INT trace,			*

*										  INT block, INT* seekSize,		*

										  FILE* ascFp )					*

*																		*

*	入力パラメタ:	INT		group		: グループ番号					*

*					INT		trace		: トレース番号					*

*					INT		block		: ブロック番号					*

*					FILE*	ascFp		: ＡＳＣＩＩファイルのポインター*

*																		*

*	出力パラメタ:	INT*	seekSize	: シークサイズ					*

*																		*

*	返		値	:	有効	OK		無効	ERROR						*

*																		*

*ENDF*******************************************************************/

INT getTraceSeekSize( INT group, INT trace, INT block, INT* seekSize, FILE* ascFp )

{

	INT		i, j, k;

	INT		blockNumber;

	INT		traceNumber;


	for( i = 0 ; i < group ; i++ ){

		/* トレース番号を得る */

		if( OK == work( _TraceNumber, _destBuffer, ( UCHR )PublicMode,

						i, 0, ( INT )NoBlockData, ascFp ))

			traceNumber = atol(( CHR* )_destBuffer );

		else

			return( ERROR );

		/* ブロック番号を得る */

		if( OK == work( _BlockNumber, _destBuffer, ( UCHR )PublicMode,

						i, 0, ( INT )NoBlockData, ascFp ))

			blockNumber = atol(( CHR* )_destBuffer );

		else

			return( ERROR );

		for( j = 0 ; j < traceNumber ; j++ ){

			for( k = 0 ; k < blockNumber ; k++ ){

	 			getSize( i, j, k, seekSize, ascFp );

			}

		}

	}


	/* ブロック番号を得る */

	if( OK == work( _BlockNumber, _destBuffer, ( UCHR )PublicMode,

					group, 0, ( INT )NoBlockData, ascFp ))

		blockNumber = atol(( CHR* )_destBuffer );

	else

		return( ERROR );

	for( j = 0 ; j < trace ; j++ ){

		for( k = 0 ; k < blockNumber ; k++ ){

			getSize( group, j, k, seekSize, ascFp );

		}

	}

	for( k = 0 ; k < block ; k++ ){

		getSize( group, trace, k, seekSize, ascFp );

	}

	return( OK );

}


/*STARTF*****************************************************************

*																		*

*	関　数　名	:	getBlockSeekSize									*

*																		*

*	機		能	:	シークサイズ（ブロックタイプ）を求める				*

*																		*

*	書　　　式　:	INT	getBlockSeekSize( INF* infP, INT group,			*

*										  INT trace, INT block,			*

*										  INT* seekSize, FILE* ascFp )	*

*																		*

*	入力パラメタ:	INF*	infP		: 情報部のポインター			*

*					INT		group		: グループ番号					*

*					INT		trace		: トレース番号					*

*					INT		block		: ブロック番号					*

*					FILE*	ascFp		: ＡＳＣＩＩファイルのポインター*

*																		*

*	出力パラメタ:	INT*	seekSize	: シークサイズ					*

*																		*

*	返		値	:	有効	OK		無効	ERROR						*

*																		*

*ENDF*******************************************************************/

INT getBlockSeekSize( INF* infP, INT group, INT trace, INT block, INT* seekSize, FILE* ascFp )

{

	INT		ii, j, k;

	UINT	i;

	INT		traceNumber;


	for( k = 0 ; k < block ; k++ ){

	    for( i = 0 ; i < infP->groupNumber ; i++ ){

			/* トレース番号を得る */

			if( OK == work( _TraceNumber, _destBuffer, ( UCHR )PublicMode,

							i, 0, ( INT )NoBlockData, ascFp ))

				traceNumber = atol(( CHR* )_destBuffer );

			else

				return( ERROR );

			for( j = 0 ; j < traceNumber ; j++ ){

			    getSize( i, j, k, seekSize, ascFp );

			}

		}

	}

	for( ii = 0 ; ii < group ; ii++ ){

		/* トレース番号を得る */

		if( OK == work( _TraceNumber, _destBuffer, ( UCHR )PublicMode,

						ii, 0, ( INT )NoBlockData, ascFp ))

			traceNumber = atol(( CHR* )_destBuffer );

		else

			return( ERROR );

		for( j = 0 ; j < traceNumber ; j++ ){

		    getSize( ii, j, block, seekSize, ascFp );

		}

	}

	for( j = 0 ; j < trace ; j++ ){

	    getSize( group, j, block, seekSize, ascFp );

	}

	return( OK );

}


/*STARTF*****************************************************************

*																		*

*	関　数　名	:	change2Byte											*

*																		*

*	機		能	:	ローバイトとハイバイトの入れ替え					*

*																		*

*	書　　　式　:	INT	change2Byte( TYPE2* data )						*

*																		*

*	入力パラメタ:	None												*

*																		*

*	出力パラメタ:	TYPE2*	data		: 結果							*

*																		*

*	返		値	:														*

*																		*

*ENDF*******************************************************************/

void change2Byte( TYPE2* data )

{

	UCHR	tmpLo, tmpHi;


	tmpLo = data->dataLo;

	tmpHi = data->dataHi;

	data->dataLo = tmpHi;

	data->dataHi = tmpLo;

}


/*STARTF*****************************************************************

*																		*

*	関　数　名	:	change4Byte											*

*																		*

*	機		能	:	ローバイトとハイバイトの入れ替え					*

*																		*

*	書　　　式　:	INT	change4Byte( TYPE4* data )						*

*																		*

*	入力パラメタ:	None												*

*																		*

*	出力パラメタ:	TYPE4*	data		: 結果							*

*																		*

*	返		値	:														*

*																		*

*ENDF*******************************************************************/

void change4Byte( TYPE4* data )

{

	UCHR	tmpLo1, tmpHi1, tmpLo2, tmpHi2;


	tmpLo1 = data->dataLo1;

	tmpHi1 = data->dataHi1;

	tmpLo2 = data->dataLo2;

	tmpHi2 = data->dataHi2;

	data->dataLo1 = tmpHi2;

	data->dataHi1 = tmpLo2;

	data->dataLo2 = tmpHi1;

	data->dataHi2 = tmpLo1;

}


/*STARTF*****************************************************************

*																		*

*	関　数　名	:	change8Byte											*

*																		*

*	機		能	:	ローバイトとハイバイトの入れ替え					*

*																		*

*	書　　　式　:	INT	change8Byte( TYPE4* data )						*

*																		*

*	入力パラメタ:	None												*

*																		*

*	出力パラメタ:	TYPE8*	data		: 結果							*

*																		*

*	返		値	:														*

*																		*

*ENDF*******************************************************************/

void change8Byte( TYPE8* data )

{

	UCHR	tmpLo1, tmpHi1;

	UCHR	tmpLo2, tmpHi2;

	UCHR	tmpLo3, tmpHi3;

	UCHR	tmpLo4, tmpHi4;


	tmpLo1 = data->dataLo1;

	tmpHi1 = data->dataHi1;

	tmpLo2 = data->dataLo2;

	tmpHi2 = data->dataHi2;

	tmpLo3 = data->dataLo3;

	tmpHi3 = data->dataHi3;

	tmpLo4 = data->dataLo4;

	tmpHi4 = data->dataHi4;

	data->dataLo1 = tmpHi4;

	data->dataHi1 = tmpLo4;

	data->dataLo2 = tmpHi3;

	data->dataHi2 = tmpLo3;

	data->dataLo3 = tmpHi2;

	data->dataHi3 = tmpLo2;

	data->dataLo4 = tmpHi1;

	data->dataHi4 = tmpLo1;

}


/*STARTF*****************************************************************

*																		*

*	関　数　名	:	readBinFile											*

*																		*

*	機		能	:	バイナリーファイルの読み込み						*

*																		*

*	書　　　式　:	INT	readBinFile( DREAL* data, INF* infP,	 		*

*									 ANRZ* analizeP, FILE* binFp )		*

*																		*

*	入力パラメタ:	INF*	infP		: 情報部のポインター			*

*					ANRZ*	analizeP	: 情報部のポインター			*

*					FILE*	binFp		: バイナリーファイルのポインター*

*																		*

*	出力パラメタ:	DREAL*	data		: 結果							*

*																		*

*	返		値	:	有効	OK		無効	ERROR						*

*																		*

*ENDF*******************************************************************/

INT readBinFile( DREAL* data, INF* infP, ANRZ* analizeP, FILE* binFp )

{

	int			byte;

	ALLTYPE*	allTypeP;


	allTypeP = &_allType;

	byte = (int)getByte( analizeP->vDataType );

	if( byte > ( int )fread( allTypeP, 1, byte, binFp )){

		printf( "Cannot Read This File\n" );

		return( ERROR );

	}

	if( 'I' == analizeP->vDataType[0] ){

		/* データタイプの先頭１バイトがＩの場合 */

		if( 'S' == analizeP->vDataType[1] ){

		    /* 次がＳの場合 */

			if( OK != signedWork( data, byte, infP, allTypeP ))

				return( ERROR );

		    }

		else if( 'U' == analizeP->vDataType[1] ){

		    /* 次がＵの場合 */

			if( OK != unsignedWork( data, byte, infP, allTypeP ))

				return( ERROR );

		}

	}

	else if( 'B' == analizeP->vDataType[0] ){

		/* データタイプの先頭１バイトがBの場合 */

		if( OK != unsignedWork( data, byte, infP, allTypeP ))

				return( ERROR );

	}

	else{

		if( 'F' == analizeP->vDataType[0] ){

		/* データタイプの先頭１バイトがＦの場合 */

			if( OK != floatWork( data, byte, infP, allTypeP ))

				return( ERROR );

		}

		else

			return( ERROR );

	}

	return( OK );

}


/*STARTF*****************************************************************

*																		*

*	関　数　名	:	signedWork											*

*																		*

*	機		能	:	signedデータをdoubleに拡張							*

*																		*

*	書　　　式　:	INT	signedWork( DREAL* data, INT byte, INF* infP,	*

*									ALLTYPE* allType )					*

*																		*

*	入力パラメタ:	INT			byte		: データのバイト数			*

*					INF*		infP		: 情報部のポインター		*

*					ALLTYPE*	allTypeP	: データのポインター		*

*																		*

*	出力パラメタ:	DREAL*		data		: 結果						*

*																		*

*	返		値	:	有効	OK		無効	ERROR						*

*																		*

*ENDF*******************************************************************/

INT signedWork( DREAL* data, INT byte, INF* infP, ALLTYPE* allTypeP )

{

	switch( byte ){

	  case 1:	/* CHRタイプ */

	    *data = ( DREAL )allTypeP->chData;

		break;

	  case 2:	/* SHORTタイプ */

		if(( UCHR )NotEqual == infP->endianMode )

		    change2Byte(( TYPE2* )&allTypeP->shData );

		*data = ( DREAL )allTypeP->shData;

		break;

	  case 4:	/* INTタイプ */

		if(( UCHR )NotEqual == infP->endianMode )

			change4Byte(( TYPE4* )&allTypeP->intData );

		*data = ( DREAL )allTypeP->intData;

		break;

	  default:

		printf( "Cannot Exist DataType\n" );

		return( ERROR );

	}

	return( OK );

}


/*STARTF*****************************************************************

*																		*

*	関　数　名	:	unsignedWork										*

*																		*

*	機		能	:	unsignedデータをdoubleに拡張						*

*																		*

*	書　　　式　:	INT	unsignedWork( DREAL* data, INT byte, INF* infP,	*

*									ALLTYPE* allType )					*

*																		*

*	入力パラメタ:	INT			byte		: データのバイト数			*

*					INF*		infP		: 情報部のポインター		*

*					ALLTYPE*	allTypeP	: データのポインター		*

*																		*

*	出力パラメタ:	DREAL*		data		: 結果						*

*																		*

*	返		値	:	有効	OK		無効	ERROR						*

*																		*

*ENDF*******************************************************************/

INT unsignedWork( DREAL* data, INT byte, INF* infP, ALLTYPE* allTypeP )

{

	switch( byte ){

	  case 1:	/* UCHRタイプ */

	    *data = ( DREAL )allTypeP->uchData;

		break;

	  case 2:	/* USHORTタイプ */

		if(( UCHR )NotEqual == infP->endianMode )

		    change2Byte(( TYPE2* )&allTypeP->ushData );

		*data = ( DREAL )allTypeP->ushData;

		break;

	  case 4:	/* UINTタイプ */

		if(( UCHR )NotEqual == infP->endianMode )

			change4Byte(( TYPE4* )&allTypeP->uintData );

		*data = ( DREAL )allTypeP->uintData;

		break;

	  default:

		printf( "Cannot Exist DataType\n" );

		return( ERROR );

	}

	return( OK );

}


/*STARTF*****************************************************************

*																		*

*	関　数　名	:	floatWork											*

*																		*

*	機		能	:	floatデータをdoubleに拡張							*

*																		*

*	書　　　式　:	INT	floatWork( DREAL* data, INT byte, INF* infP,	*

*								   ALLTYPE* allType )					*

*																		*

*	入力パラメタ:	INT			byte		: データのバイト数			*

*					INF*		infP		: 情報部のポインター		*

*					ALLTYPE*	allTypeP	: データのポインター		*

*																		*

*	出力パラメタ:	DREAL*		data		: 結果						*

*																		*

*	返		値	:	有効	OK		無効	ERROR						*

*																		*

*ENDF*******************************************************************/

INT floatWork( DREAL* data, INT byte, INF* infP, ALLTYPE* allTypeP )

{

	switch( byte ){

	  case 4:	/* SREALタイプ */

		if(( UCHR )NotEqual == infP->endianMode )

			change4Byte(( TYPE4* )&allTypeP->srData );

		*data = ( DREAL )allTypeP->srData;

		break;

	  case 8:	/* DREALタイプ */

		if(( UCHR )NotEqual == infP->endianMode )

			change8Byte(( TYPE8* )&allTypeP->drData );

		*data = ( DREAL )allTypeP->drData;

		break;

	  default:

		printf( "Cannot Exist DataType\n" );

		return( ERROR );

	}

	return( OK );

}


/*STARTF*****************************************************************

*																		*

*	関　数　名	:	binToValue											*

*																		*

*	機		能	:	バイナリーデータを物理値に変換						*

*																		*

*	書　　　式　:	INT	binToValue( DREAL* result, ANRZ* analizeP, 		*

*									DREAL data )						*

*																		*

*	入力パラメタ:	ANRZ*	analizeP	: 情報部のポインター			*

*					DREAL	data		: バイナリーデータ				*

*																		*

*	出力パラメタ:	DREAL*	result		: 結果（物理値）				*

*																		*

*	返		値	:	有効	OK		無効	ERROR						*

*																		*

*ENDF*******************************************************************/

void binToValue( DREAL* result, ANRZ* analizeP, DREAL data )

{


	*result = analizeP->vResolution * data + analizeP->vOffset;


}


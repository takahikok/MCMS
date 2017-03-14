/* This is G-file %M% Version %I% (%G%) */


/*STARTM-------------------------------------------------------------

+																	+

+	モジュール名:	analize.h										+

+																	+

+	機		能	:	ヘッダーファイル								+

+																	+

+	改訂履歴	:													+

+	改訂	担当		日付		内容							+

+	--------------------------------------------------------------	+

+	 																+

+																	+

-ENDM--------------------------------------------------------------*/



#define			AscFile			0		/* ＡＳＣＩＩファイル */

#define			BinFile			1		/* バイナリーファイル */


#define			MaxBuff 		200		/* バッファサイズ */

#define			Buff			80		/* バッファサイズ */

#define			LineBuffMax		4096	/* バッファサイズ */


#define			BigEndian		0		/* エンディアンモード（Big) */

#define			LittleEndian	1		/*         〃         (Little) */

#define			Equal			0		/*         〃         (Same) */

#define			NotEqual		1		/*         〃         (Different) */


#define			TraceUnit		0		/* トレースデータタイプ */

#define			BlockUnit		1		/* ブロックデータタイプ */


#define			NoGroupData		-2		/* 検索モード（グループ番号で） */

#define			NoTraceData		-1		/*     〃    （トレース番号で） */

#define			NoBlockData		-1		/*     〃    （ブロック番号で） */


#define			PublicMode		0		/* 検索場所($PublicInfo)*/

#define 		PrivateMode		1		/*     〃  ($PrivateInfo) */

#define 		NonPublicMode	2		/*     〃  ($PublicInfo以外で) */


#define			MediaMode		1		/* Media Block search */

#define			NumberMode		0		/* Block number addition */

#define			NoNumberMode	1		/* No Block number addition */

#define 		NoDispBlock		0		/* Display Block Size not found */


#define			BitCount		8		/* ビット数 */


#define			BitType			0		/* データタイプがビットタイプである */

#define			NotBitType		1		/* データタイプがビットタイプでない */


#define			Off				0

#define			On				1


typedef struct {

	UCHR		traceName[ Buff ];

	INT			blockSize;

	DREAL		vResolution;

	DREAL		vOffset;

	UCHR		vDataType[ Buff ];

	UCHR		vUnit[ Buff ];

	DREAL		vPlusOverData;

	DREAL		vMinusOverData;

	DREAL		vIllegalData;

	DREAL		vMaxData;

	DREAL		vMinData;

	DREAL		hResolution;

	DREAL		hOffset;

	UCHR		hUnit[ Buff ];

	UCHR		date[ Buff ];

	UCHR		time[ Buff ];

	USHORT		maskData;

	USHORT		linearMode;

	DREAL		linearSlope;

	DREAL		linearIntercept;

	UCHR		linearUnit[ Buff ];

} ANRZ;




typedef struct {

	UCHR		formatVersion[ Buff ];	/* ファイルフォーマットバージョン */

	UCHR		model[ Buff ];			/* モデル名 */

	UCHR		endianMode;				/* エンディアンモード */

	UCHR		dataFormat;				/* データフォーマット(Trace/Block) */

	UINT		groupNumber;			/* グループ数 */

	UINT		dataOffset;				/* 有効データの先頭からのオフセット値 */

	UINT		displayPointNo;			/* 表示開始データ点 */

	UINT		displayBlockSize;		/* メモリー長 */

} INF;


typedef struct {

	UCHR		dataLo;

	UCHR		dataHi;

} TYPE2;


typedef struct {

	UCHR		dataLo1;

	UCHR		dataHi1;

	UCHR		dataLo2;

	UCHR		dataHi2;

} TYPE4;


typedef struct {

	UCHR		dataLo1;

	UCHR		dataHi1;

	UCHR		dataLo2;

	UCHR		dataHi2;

	UCHR		dataLo3;

	UCHR		dataHi3;

	UCHR		dataLo4;

	UCHR		dataHi4;

} TYPE8;


typedef union {

	/*Preparation of all data type*/

	CHR			chData;

	UCHR		uchData;

	SHORT		shData;

	USHORT		ushData;

	INT			intData;

	UINT		uintData;

	SREAL		srData;

	DREAL		drData;

} ALLTYPE;


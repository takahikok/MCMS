/* This is G-file %M% Version %I% (%G%) */


/*STARTM-------------------------------------------------------------

+																	+

+	���W���[����:	analize.h										+

+																	+

+	�@		�\	:	�w�b�_�[�t�@�C��								+

+																	+

+	��������	:													+

+	����	�S��		���t		���e							+

+	--------------------------------------------------------------	+

+	 																+

+																	+

-ENDM--------------------------------------------------------------*/



#define			AscFile			0		/* �`�r�b�h�h�t�@�C�� */

#define			BinFile			1		/* �o�C�i���[�t�@�C�� */


#define			MaxBuff 		200		/* �o�b�t�@�T�C�Y */

#define			Buff			80		/* �o�b�t�@�T�C�Y */

#define			LineBuffMax		4096	/* �o�b�t�@�T�C�Y */


#define			BigEndian		0		/* �G���f�B�A�����[�h�iBig) */

#define			LittleEndian	1		/*         �V         (Little) */

#define			Equal			0		/*         �V         (Same) */

#define			NotEqual		1		/*         �V         (Different) */


#define			TraceUnit		0		/* �g���[�X�f�[�^�^�C�v */

#define			BlockUnit		1		/* �u���b�N�f�[�^�^�C�v */


#define			NoGroupData		-2		/* �������[�h�i�O���[�v�ԍ��Łj */

#define			NoTraceData		-1		/*     �V    �i�g���[�X�ԍ��Łj */

#define			NoBlockData		-1		/*     �V    �i�u���b�N�ԍ��Łj */


#define			PublicMode		0		/* �����ꏊ($PublicInfo)*/

#define 		PrivateMode		1		/*     �V  ($PrivateInfo) */

#define 		NonPublicMode	2		/*     �V  ($PublicInfo�ȊO��) */


#define			MediaMode		1		/* Media Block search */

#define			NumberMode		0		/* Block number addition */

#define			NoNumberMode	1		/* No Block number addition */

#define 		NoDispBlock		0		/* Display Block Size not found */


#define			BitCount		8		/* �r�b�g�� */


#define			BitType			0		/* �f�[�^�^�C�v���r�b�g�^�C�v�ł��� */

#define			NotBitType		1		/* �f�[�^�^�C�v���r�b�g�^�C�v�łȂ� */


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

	UCHR		formatVersion[ Buff ];	/* �t�@�C���t�H�[�}�b�g�o�[�W���� */

	UCHR		model[ Buff ];			/* ���f���� */

	UCHR		endianMode;				/* �G���f�B�A�����[�h */

	UCHR		dataFormat;				/* �f�[�^�t�H�[�}�b�g(Trace/Block) */

	UINT		groupNumber;			/* �O���[�v�� */

	UINT		dataOffset;				/* �L���f�[�^�̐擪����̃I�t�Z�b�g�l */

	UINT		displayPointNo;			/* �\���J�n�f�[�^�_ */

	UINT		displayBlockSize;		/* �������[�� */

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


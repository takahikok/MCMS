

/*******************************************

 *	Basic data type declaration	   *

 *******************************************/


#ifdef	TRUE

#undef	TRUE

#endif

#define TRUE	   1


#ifdef	FALSE

#undef	FALSE

#endif

#define FALSE	   0


#ifdef	OK

#undef	OK

#endif

#define OK	   0		/* function return value: OK	*/


#ifdef	ERROR

#undef	ERROR

#endif

#define ERROR	   (~0) 	/* function return value: Error	*/


#ifdef	TBLEND

#undef	TBLEND

#endif

#define TBLEND	   (~0) 	/* Table end */


#ifdef	NULL

#undef	NULL

#endif

#define NULL	   ((void*)0)	/* NULL POINTER */

/*
 note:
 __int** ���̌^�� Visual Studio �Ǝ��̌^�Ȃ̂�
 VS�ȊO�̃R���p�C�����g�p����ꍇ�͓K���Ȍ^�ɕϊ����Ă��������B
 ���^�̑傫���͏����n�ɂ���ĈႢ�����邱�Ƃɒ��ӂ��Ă��������I�I
 �@�R���p�C���� C99 �ɑΉ����Ă���� int16_t ���̎����ɂ��Ȃ��^���g�p����ׂ��ł��B
 */

typedef unsigned char		 UCHR;		/* From 0 to 255 */

typedef unsigned __int16	 USHORT;	/* From 0 to 65535 */

typedef unsigned __int32	 UINT;		/* From 0 to 4294967295 */

typedef char			 CHR;		/* From -128 to 127 */

typedef __int16			 SHORT;		/* From -32768 to 32767 */

typedef __int32			 INT;/* From -2147483648 to 2147483647 */

typedef unsigned char		 *STR;		/* strings */

typedef void			 *VP;		/* pointer to void */

typedef void			 *(FP)();  /* void function pointer */

typedef unsigned char		 BYTE;		/* 8 bit */

typedef unsigned __int16	 WORD;		/* 16 bit */

typedef unsigned __int32	 DWORD;		/* 32 bit */

typedef float                    SREAL;    /* IEEE short real [4bytes] */

typedef double                   DREAL;    /* IEEE double real [8bytes] */


/*

 *	The folling can not be defined in MCC 68k

 */


/* typedef unsigned long	ULONG;*//* From 0 to 18446744073709552935 */

/* typedef signed long		LONG;	*//* From -1844... to 1844.. */

/* typedef long double		TREAL; *//* IEEE temporary real [10bytes] */


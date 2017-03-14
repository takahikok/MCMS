/* This is G-file %M% Version %I% (%G%) */


/*STARTM-------------------------------------------------------------

+																	+

+	���W���[����:	ana.c											+

+																	+

+	�@		�\	:	�g�`�f�[�^��ASCII�ɕϊ�							+

+																	+

+	��������	:													+

+	����	�S��		���t		���e							+

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


FILE*	ascFp;						/* �`�r�b�h�h�t�@�C��			*/

FILE*	binFp;						/* �o�C�i���[�t�@�C��			*/

FILE*	t1_fp;						/* �ꎞ�t�@�C���i���̂P�j		*/

FILE*	t2_fp;						/* �ꎞ�t�@�C���i���̂Q�j		*/



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

*							���C���֐�									*

*																		*

*ENDF*******************************************************************/

void	main( int argc, char *argv[], char **envp )

{

	char	opt1[10];


	_style = 3;							/* �o�̓X�^�C���̏�����			*/

	_mergeSw = Off;						/* �}�[�W�X�C�b�`�̏�����		*/

	_fileSw = Off;						/* �t�@�C������X�C�b�`�̏����� */


	switch( argc )

	{

	  case 2:	/* �I�v�V�������w��̏ꍇ */
		  _style = 0;
		  _mergeSw = On;

		if( OK != analizeWaveForm((UCHR*)*(argv + 1)) )

			exit( -1 );					/*Error termination*/

		break;

	  case 3:	/* �o�̓X�^�C���̃I�v�V����1�w��̏ꍇ */

		strncpy( opt1, argv[2], sizeof(opt1) );

		_style = atoi( opt1 ); 

		if( _strnicmp( opt1, _check_m, 1 ) == 0 )	_mergeSw = On;

		if( OK != analizeWaveForm((UCHR*)*(argv + 1)) )

			exit( -1 );					/*Error termination*/

		break;

	  case 4:	/* �o�̓X�^�C���̃I�v�V����1��2�w��̏ꍇ */

		strncpy( opt1, argv[2], sizeof(opt1) );

		_style = atoi( opt1 ); 

		strncpy( opt1, argv[3], sizeof(opt1) );

		if( _strnicmp( opt1, _check_m, 1 ) == 0 )	_mergeSw = On;

		else										_mergeSw = Off;

		if( OK != analizeWaveForm((UCHR*)*(argv + 1)) )

			exit( -1 );					/*Error termination*/

		break;

	  default:	/* �p�����[�^�����̏ꍇ */

		printf("DL750�̃o�C�i���[�t�@�C����ASCII�t�@�C���ɕϊ�����c�[��  wvfconv.exe \n");

		printf("                  copyright 2017 (c) Takahiko Kobayashi, Kitajima Lab.\n");
//		printf("                               2017.3.14 Takahiko Kobayashi, Kitajima Lab.\n");
		printf( "�y�g�p���@�z\n");

		printf( " ana �g�`�f�[�^�� [�I�v�V����] \n");

		printf( "     [�I�v�V����] �o�̓X�^�C���� 0/1/2/3 ����I�����܂��B\n");

		printf( "                   ���w��̏ꍇ�� 0 �̃X�^�C���ŏo�͂��܂��B\n");

		printf( "                   0 ... �����l \n");

		printf( "                   1 ... �����l �P��\n");

		printf( "                   2 ... �f�[�^�ԍ� �����l �P��\n");

		printf( "                   3 ... �f�[�^�ԍ� �����l �P�� ���f�[�^ \n");

//		printf( "     [�I�v�V����2] �g���[�X�o�̓X�^�C���� �I�����܂��B\n");

//		printf( "                   ���w��̏ꍇ�� �g���[�X���c�ɏo�͂��܂��B\n");

//		printf( "                   m���w�肷��Ɖ��W�J���܂��B\n");

		printf( "     �i���j�o�͕͂W���o��\n");

		printf( "           �t�@�C���o�͂̏ꍇ�̓��_�C���N�V�����Ŏw��\n");

		printf( " ana dat0001a                  ... �ϊ���W���o��\n");

//		printf( " ana dat0001a m                ... �ϊ���W���o��(���W�J)\n");

		printf( " ana dat0001a   > dat0001a.csv ... �ϊ���dat0001a.csv�ɏo��\n");

		printf("���̃\�t�g�E�F�A�͋��痘�p�͈̔͂ŉ��L�\�t�g�E�F�A�����ɐ��삳��܂���\n");
		printf("�o�C�i���[�t�@�C�����`�r�b�h�h�t�@�C���ɕϊ�����c�[��  ana.exe \n");

		printf("                      copyright 1996 (c) Yokogawa Electric Corporation\n");


		exit( -1 );						/*Error termination*/

	}

	exit( 0 );							/*Succsessful termination*/

}





/*STARTF*****************************************************************

*																		*

*	�ց@���@��	:	analizeWaveForm										*

*																		*

*	�@		�\	:	��̓��C������										*

*																		*

*	���@�@�@���@:	INT	analizeWaveForm( UCHR* fileName )				*

*																		*

*	���̓p�����^:	UCHR*	fileName	: �t�@�C����					*

*																		*

*	�o�̓p�����^:	None												*

*																		*

*	��		�l	:	�L��	OK		����	ERROR						*

*																		*

*ENDF*******************************************************************/

INT analizeWaveForm( UCHR* fileName )

{

	/* �J�n���b�Z�[�W */

//	fprintf( stderr, "�o�C�i���[�t�@�C�����`�r�b�h�h�t�@�C���ɕϊ�����c�[��  analize.exe \n" );

//	fprintf( stderr, "       **********    ANA.EXE Version 1.04    ********** \n" );
	fprintf(stderr, "");


	/* �`�r�b�h�h�t�@�C���̃I�[�v�� */

	if( NULL == ( ascFp = openFile( fileName, ( UCHR )AscFile ))){

		printf( "Error ascii file open \n" );

	    return( ERROR );

	}

	/* �o�C�i���[�t�@�C���̃I�[�v�� */

	if( NULL == ( binFp = openFile( fileName, ( UCHR )BinFile ))){

		printf( "Error binary file open \n" );

	    return( ERROR );

	}

	/* �ꎞ�t�@�C���̃I�[�v�� */

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


	/* ��񕔁i$PublicInfo�j�̎擾 */

	if( OK != getInformation( &_information, ascFp )){

		printf( "Error inforamation \n" );

		return( ERROR );

	}

	/* �g�`�f�[�^�̉�� */

	if( OK != analizeAscAndBin( &_information, &_analize, ascFp, binFp )){

		printf( "Error anlalize \n" );

	    return( ERROR );

	}


	/* �`�r�b�h�h�t�@�C���̃N���[�Y */

	if( fclose( ascFp ) == EOF ){

		printf( "Error ascii file close \n" );

		return( ERROR );

	}

	/* �o�C�i���[�t�@�C���̃N���[�Y */

	if( fclose( binFp ) == EOF ){

		printf( "Error binary file close \n" );

		return( ERROR );

	}

	

	/* �}�[�W�I�v�V�����������������e�̕\�� */

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

*	�ց@���@��	:	analizeAscAndBin									*

*																		*

*	�@		�\	:	�g�`�f�[�^�̉�͏���								*

*																		*

*	���@�@�@���@:	INT	analizeAscAndBin( INF* infP, ANRZ* analizeP		*

*										  FILE* ascFp, FILE* binFp )	*

*																		*

*	���̓p�����^:	INF*	infP	: ���($PublicInfo)�̃|�C���^�[	*

*					ANRZ*	analizeP:       ($Group)�̃|�C���^�[		*

*					FILE*	ascFp	: �`�r�b�h�h�t�@�C���̃|�C���^�[	*

*					FILE*	binFp	: �g�`�f�[�^�t�@�C���̃|�C���^�[	*

*																		*

*	�o�̓p�����^:	ANRZ*	analizeP: ����								*

*																		*

*	��		�l	:	�L��	OK		����	ERROR						*

*																		*

*ENDF*******************************************************************/

INT analizeAscAndBin( INF* infP, ANRZ* analizeP, FILE* ascFp, FILE* binFp )

{

	INT		traceNumber;

	INT		blockNumber;

	INT		j, k;

	UINT	i;


	for( i = 0 ; i < infP->groupNumber ; i++ ){ /* �O���[�v�̐������[�v���� */

		/* �g���[�X�̐��ƃu���b�N�ԍ��𓾂� */

		if( OK != getGroupInf( i, &traceNumber, &blockNumber, ascFp )){

			return( ERROR );

		}

		for( j = 0 ; j < traceNumber ; j++ ){

			/* �g���[�X���𓾂� */

			if( OK != getTraceInf( analizeP, i, j, ascFp )){

			    return( ERROR );

			}

			for( k = 0 ; k < blockNumber ; k++ ){

				/* �u���b�N���𓾂� */

				if( OK != getBlockInf( analizeP, i, j, k, ascFp ))

				    return( ERROR );

				/* �o�C�i���[�i�g�`�f�[�^�j�̉�� */

				if( OK != analizeBin( infP, analizeP, i, j, k, ascFp, binFp ))

				    return( ERROR );

			}

		}

	}

	return( OK );

}


/*STARTF*****************************************************************

*																		*

*	�ց@���@��	:	getInformation										*

*																		*

*	�@		�\	:	��񕔂̎擾										*

*																		*

*	���@�@�@���@:	INT	getInformation( INF* infP, FILE* ascFp )		*

*																		*

*	���̓p�����^:	INF*	infP	: �o�͐�|�C���^�[					*

*					FILE*	ascFp	: �`�r�b�h�h�t�@�C���̃|�C���^�[	*

*																		*

*	�o�̓p�����^:	INF*	infP	: �`�r�b�h�h�t�@�C������̏��		*

*																		*

*	��		�l	:	�L��	OK		����	ERROR						*

*																		*

*ENDF*******************************************************************/

/*

	�����ł́A$PublicInfo�̕����̏����擾���܂��B


		FormatVersion		�`�r�b�h�h�t�@�C���̃t�H�[�}�b�g�o�[�W����

		Model				���f����

		DisplayPointNo		�\���J�n�f�[�^�_

		DisplayBlockSize	�������[��

		Endian				�G���f�B�A�����[�h

		DataFormat			�g�`�f�[�^�̋L�q����

		GroupNumber			�O���[�v��

		DataOffset			�L���f�[�^�̐擪����̃I�t�Z�b�g�l


*/

INT getInformation( INF* infP, FILE* ascFp )

{

	/* �yFormatVersion�𓾂�z */

	if( OK != work( _FormatVersion, infP->formatVersion, ( UCHR )PublicMode,

					( INT )NoGroupData, 0, ( INT )NoBlockData, ascFp )){

		printf( "Error FormatVersion \n" );

		return( ERROR );	/* �擾�ł��Ȃ����� */

	}

	/* �yModel�𓾂�z */

	if( OK != work( _Model, infP->model, ( UCHR )PublicMode,

					( INT )NoGroupData, 0, ( INT )NoBlockData, ascFp )){

		printf( "Error Model \n" );

		return( ERROR );	/* �擾�ł��Ȃ����� */

	}

	/* �yDisplayPointNo�𓾂�z */

	if( OK == work( _DisplayPointNo, _destBuffer, ( UCHR )NonPublicMode,

					( INT )NoGroupData, 0, ( INT )NoBlockData, ascFp )){

		infP->displayPointNo = atol(( CHR* )_destBuffer );

		if ( infP->displayPointNo == 0 ) infP->displayPointNo = 1;

	}

	else{

		 infP->displayPointNo = 1;	/* �擾�ł��Ȃ����� */

	}

	/* �yDisplayBlockSize�𓾂�z */

	if( OK == work( _DisplayBlockSize, _destBuffer, ( UCHR )NonPublicMode,

					( INT )NoGroupData, 0, ( INT )NoBlockData, ascFp )){

		infP->displayBlockSize = atol(( CHR* )_destBuffer );

	}

	else

		infP-> displayBlockSize = NoDispBlock;	/* �擾�ł��Ȃ����� */


	/* �yEndian�𓾂�z */

	if( OK == work( _Endian, _destBuffer, ( UCHR )PublicMode,

					( INT )NoGroupData, 0, ( INT )NoBlockData, ascFp )){

		if( 0 == strcmp(( CHR* )_BigEndian, ( CHR* )_destBuffer )){

			/* �a�����G���f�B�A���̏ꍇ */

			getEndianMode( infP, ( UCHR )BigEndian );

		}

		else{

			if( 0 == strcmp(( CHR* )_LittleEndian, ( CHR* )_destBuffer )){

			/* �k�����������G���f�B�A���̏ꍇ */

				getEndianMode( infP, ( UCHR )LittleEndian );

			}

			else

			/* �ǂ���ł��Ȃ��ꍇ */

				printf( "%s Spell Miss\n", _Endian );

		}

	}

	else{

		return( ERROR );	/* �����̑ł��؂� */

	}


	/* �yDataFormat�𓾂�z */

	if( OK == work( _DataFormat, _destBuffer, ( UCHR )PublicMode,

					( INT )NoGroupData, 0, ( INT )NoBlockData, ascFp )){

		if( 0 == strcmp(( CHR* )_Trace, ( CHR* )_destBuffer )){

			/* Trace�f�[�^�̏ꍇ */

		    infP->dataFormat = ( UCHR )TraceUnit;

		}

		else{

			/* Block�f�[�^�̏ꍇ */

			if( 0 == strcmp(( CHR* )_Block, ( CHR* )_destBuffer ))

			    infP->dataFormat = ( UCHR )BlockUnit;

			else

			/* �ǂ���ł��Ȃ��ꍇ */

				printf( "%s Spell Miss\n", _DataFormat );

		}

	}

	else

		return( ERROR );	/* �����̑ł��؂� */


	/* �yGroupNumber�𓾂�z */

	if( OK == work( _GroupNumber, _destBuffer, ( UCHR )PublicMode,

					( INT )NoGroupData, 0, ( INT )NoGroupData, ascFp )){

		infP->groupNumber = atol(( CHR* )_destBuffer );

	}

	else{

		return( ERROR );	/* �����̑ł��؂� */

	}


	/* �yDataOffset�𓾂�z */

	if( OK == work( _DataOffset, _destBuffer, ( UCHR )PublicMode,

					( INT )NoGroupData, 0, ( INT )NoGroupData, ascFp )){

		infP->dataOffset = atol(( CHR* )_destBuffer );

	}

	else{

		return( ERROR );	/* �����̑ł��؂� */

	}

	

	return( OK );

}


/*STARTF*****************************************************************

*																		*

*	�ց@���@��	:	getGroupInf											*

*																		*

*	�@		�\	:	�O���[�v���𓾂�									*

*																		*

*	���@�@�@���@:	INT	getGroupInf( INT group, INT* traceNumber,		*

*									 INT* blockNumber, FILE* ascFp )	*

*																		*

*	���̓p�����^:	INT		group		: �O���[�v�ԍ�					*

*					FILE*	ascFp		: �`�r�b�h�h�t�@�C���|�C���^�[	*

*																		*

*	�o�̓p�����^:	INT*	traceNumber	: �g���[�X��					*

*					INT*	blockNumber	: �u���b�N�ԍ�					*

*																		*

*	��		�l	:	�L��	OK		����	ERROR						*

*																		*

*ENDF*******************************************************************/

/*

	�����ł́A$Group�̕����̏����擾���܂��B


		TraceNumber		�g���[�X��

		BlockNumber		�u���b�N�ԍ�


*/

INT getGroupInf( INT group, INT* traceNumber, INT* blockNumber, FILE* ascFp )

{

	/* �yTraceNumber�𓾂�z */

	if( OK == work( _TraceNumber, _destBuffer, ( UCHR )PublicMode,

					group, 0, ( INT )NoBlockData, ascFp )){

		*traceNumber = atol(( CHR* )_destBuffer );

	}

	else{

		return( ERROR );

	}

	/* �yBlockNumber�𓾂�z */

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

*	�ց@���@��	:	getTraceInf											*

*																		*

*	�@		�\	:	�O���[�v���𓾂�									*

*																		*

*	���@�@�@���@:	INT	getTraceInf( ANRZ* analizeP, INT group,			*

*									 INT trace, FILE* ascFp )			*

*																		*

*	���̓p�����^:	ANRZ*	analizeP	: ��񕔂̃|�C���^�[			*

*					INT		group		: �O���[�v�ԍ�					*

*					INT		trace		: �g���[�X�ԍ�					*

*					FILE*	ascFp		: �`�r�b�h�h�t�@�C���̃|�C���^�[*

*																		*

*	�o�̓p�����^:	ANRZ*	analize		: ����							*

*																		*

*	��		�l	:	�L��	OK		����	ERROR						*

*																		*

*ENDF*******************************************************************/

/*

	�����ł́A$Group�̕����̏����擾���܂��B


		TraceName		�g���[�X��


*/

INT getTraceInf( ANRZ* analizeP, INT group, INT trace, FILE* ascFp )

{

	/* �yTrceName�𓾂�z */

	if( OK != work( _TraceName, analizeP->traceName, ( UCHR )PublicMode,

					group, trace, 0, ascFp )){

		return( ERROR );

	}

	return( OK );

}


/*STARTF*****************************************************************

*																		*

*	�ց@���@��	:	getBlockInf											*

*																		*

*	�@		�\	:	�O���[�v���𓾂�									*

*																		*

*	���@�@�@���@:	INT	getBlockInf( ANRZ* analizeP, INT group, 		*

*									 INT trace, INT block, FILE* ascFp )*

*																		*

*	���̓p�����^:	ANRZ*	analizeP	: ��񕔂̃|�C���^�[			*

*					INT		group		: �O���[�v�ԍ�					*

*					INT		trace		: �g���[�X�ԍ�					*

*					INT		block		: �u���b�N�ԍ�					*

*					FILE*	ascFp		: �`�r�b�h�h�t�@�C���̃|�C���^�[*

*																		*

*	�o�̓p�����^:	ANRZ*	analize		: ����							*

*																		*

*	��		�l	:	�L��	OK		����	ERROR						*

*																		*

*ENDF*******************************************************************/

/*

	�����ł́A$Group�̕����̏����擾���܂��B


		BlockSize			�u���b�N�T�C�Y

		VResolution			�x���ϊ����̌W��

		VOffset				�x���̃I�t�Z�b�g�l

		VDataType			�f�[�^�̃^�C�v

		VUnit				�x���̒P��

		VPlusOverData		�G���[�f�[�^�̂������l

		VMinusOverData		          �V

		VIllegalData		��\���R�[�h�̃f�[�^

		VMaxData			�ő�l�f�[�^

		VMinData			�ŏ��l�f�[�^

		HResolution			�w���ϊ����̌W��

		HOffset				�w���̃I�t�Z�b�g�l

		HUnit				�w���̒P��

		Date				�g���K���t

		Time				�g���K����


*/


INT getBlockInf( ANRZ* analizeP, INT group, INT trace, INT block, FILE* ascFp )

{

	/* �yBlockSize�𓾂�z */

	if( OK == work( _BlockSize, _destBuffer, ( UCHR )PublicMode,

					group, trace, block, ascFp )){

	    analizeP->blockSize = atol(( CHR* )_destBuffer );

	}

	else{

		return( ERROR );

	}

	/* �yVResolution�𓾂�z */

	if( OK == work( _VResolution, _destBuffer, ( UCHR )PublicMode,

					group, trace, block, ascFp )){

		analizeP->vResolution = atof(( CHR* )_destBuffer );

	}

	else{

		return( ERROR );

	}

	/* �yVOffset�𓾂�z */

	if( OK == work( _VOffset, _destBuffer, ( UCHR )PublicMode,

					group, trace, block, ascFp )){

		analizeP->vOffset	= atof(( CHR* )_destBuffer );

	}

	else{

		return( ERROR );

	}

	/* �yVDataType�𓾂�z */

	if( OK != work( _VDataType, analizeP->vDataType, ( UCHR )PublicMode,

					group, trace, block, ascFp ))

		return( ERROR );

	/* �yVUnit�𓾂�z*/

	if( OK != work( _VUnit, analizeP->vUnit, ( UCHR )PublicMode,

					group, trace, block, ascFp ))

	    return( ERROR );

	/* �yVPlusOverData�𓾂�z*/

	if( OK == work( _VPlusOverData, _destBuffer, ( UCHR )PublicMode,

					group, trace, block, ascFp )){

		analizeP->vPlusOverData = atof(( CHR* )_destBuffer );

	}

	else{

		return( ERROR );

	}

	/* �yVMinusOverData�𓾂�z */

	if( OK == work( _VMinusOverData, _destBuffer, ( UCHR )PublicMode,

					group, trace, block, ascFp )){

		analizeP->vMinusOverData = atof(( CHR* )_destBuffer );

	}

	else{

		return( ERROR );

	}

	/* �yVIllegalData�𓾂�z */

	if( OK == work( _VIllegalData, _destBuffer, ( UCHR )PublicMode,

					group, trace, block, ascFp )){

		analizeP->vIllegalData = atof(( CHR* )_destBuffer );

	}

	else{

		return( ERROR );

	}

	/* �yVMaxData�𓾂�z */

	if( OK == work( _VMaxData, _destBuffer, ( UCHR )PublicMode,

					group, trace, block, ascFp )){

		analizeP->vMaxData = atof(( CHR* )_destBuffer );

	}

	else{

		return( ERROR );

	}

	/* �yVMinData�𓾂�z */

	if( OK == work( _VMinData, _destBuffer, ( UCHR )PublicMode,

					group, trace, block, ascFp )){

		analizeP->vMinData = atof(( CHR* )_destBuffer );

	}

	else{

		return( ERROR );

	}

	/* �yHResolution�𓾂�z */

	if( OK == work( _HResolution, _destBuffer, ( UCHR )PublicMode,

					group, trace, block, ascFp )){

		analizeP->hResolution = atof(( CHR* )_destBuffer );

	}

	else{

		return( ERROR );

	}

	/* �yHOffset�𓾂�z */

	if( OK == work( _HOffset, _destBuffer, ( UCHR )PublicMode,

					group, trace, block, ascFp )){

		analizeP->hOffset	= atof(( CHR* )_destBuffer );

	}

	else{

		return( ERROR );

	}

	/* �yHUnit�𓾂�z */

	if( OK != work( _HUnit, analizeP->hUnit, ( UCHR )PublicMode,

					group, trace, block, ascFp ))

	    return( ERROR );

	/* �yDate�𓾂�z */

	if( OK != work( _Date, analizeP->date, ( UCHR )PublicMode,

					group, trace, block, ascFp ))

		return( ERROR );

	/* �yTime�𓾂�z */

	if( OK != work( _Time, analizeP->time, ( UCHR )PublicMode,

					group, trace, block, ascFp ))

		return( ERROR );



	return( OK );

}


/*STARTF*****************************************************************

*																		*

*	�ց@���@��	:	analizeBin											*

*																		*

*	�@		�\	:	�o�C�i���[�i�g�`�f�[�^�j�t�@�C���̉��				*

*																		*

*	���@�@�@���@:	INT	analizeBin( INF* infP, ANRZ* analizeP,			*

*									INT group, INT trace, INT block,	*

*									FILE* ascFp, FILE*binFp )			*

*																		*

*	���̓p�����^:	INF*	infPP		: ��񕔂̃|�C���^�[			*

*					ANRZ*	analizeP	: ��񕔂̃|�C���^�[			*

*					INT		group		: �O���[�v�ԍ�					*

*					INT		trace		: �g���[�X�ԍ�					*

*					INT		block		: �u���b�N�ԍ�					*

*					FILE*	ascFp		: �`�r�b�h�h�t�@�C���̃|�C���^�[*

*					FILE*	binFp		: �o�C�i���[�t�@�C���̃|�C���^�[*

*																		*

*	�o�̓p�����^:	None												*

*																		*

*	��		�l	:	�L��	OK		����	ERROR						*

*																		*

*ENDF*******************************************************************/

INT analizeBin( INF* infP, ANRZ* analizeP, INT group, INT trace, INT block,

				FILE* ascFp, FILE* binFp )

{

	/* �o�C�i���[�t�@�C���̎w��ꏊ�ɃV�[�N���� */

 	if( OK != seekBinFp( infP, group, trace, block, ascFp, binFp ))

	    return( ERROR );

	return( readAndDispWaveForm( infP, analizeP, group, trace, block, binFp ));

}


/*STARTF*****************************************************************

*																		*

*	�ց@���@��	:	readAndDispWaveForm									*

*																		*

*	�@		�\	:	�g�`�f�[�^��ǂݕ\��								*

*																		*

*	���@�@�@���@:	INT	readAndDispWaveForm( INF* infP, ANRZ* analizeP,	*

*									 		 INT group, INT trace,		*

*											 INT block, FILE* binFp )	*

*																		*

*	���̓p�����^:	INF*	infP		: ��񕔂̃|�C���^�[			*

*					ANRZ*	analizeP	: ��񕔂̃|�C���^�[			*

*					INT		group		: �O���[�v�ԍ�					*

*					INT		trace		: �g���[�X�ԍ�					*

*					INT		block		: �u���b�N�ԍ�					*

*					FILE*	binFp		: �o�C�i���[�t�@�C���̃|�C���^�[*

*																		*

*	�o�̓p�����^:	None												*

*																		*

*	��		�l	:	�L��	OK		����	ERROR						*

*																		*

*ENDF*******************************************************************/

INT readAndDispWaveForm( INF* infP, ANRZ* analizeP, INT group, INT trace, INT block, FILE* binFp )

{

	DREAL	data, result;

	INT		i, loop;


	if( 0 == analizeP->blockSize )	return( OK );


	if( _fileSw == On ){

		/* �ꎞ�t�@�C���̃N���[�Y���I�[�v�� */

		if( _mergeSw == On ){

			if( tmpnam( t2_fname ) == NULL ){					/* �������݃t�@�C�������擾���� */

				printf( "Error temp file create \n" );

				exit( -1 );

			}

			/* temp1��tem2�̓���ւ�	*/

			/*     temp1�͏������ݐ�p	*/

			/*     temp2�͓ǂݍ��ݐ�p	*/

			strcpy( t_fname,  t1_fname );

			strcpy( t1_fname, t2_fname );

			strcpy( t2_fname, t_fname  );

			

			if(( t1_fp = fopen( t1_fname, "w" )) == NULL ){		/* ���ʂ��������ރt�@�C�����I�[�v������ */

				remove( t1_fname );

				printf( "Error temp file open \n" );

				exit( -1 );

			}

			if(( t2_fp = fopen( t2_fname, "r" )) == NULL ){		/* �O�񏑂����񂾃t�@�C�����I�[�v������ */

				remove( t2_fname );

				printf( "Error temp file open \n" );

				exit( -1 );

			}

		}

	}


	/* �f�[�^�������߂� */

	if ( infP->displayBlockSize == NoDispBlock )

	    loop =  analizeP->blockSize;

	else

	    loop =  infP->displayBlockSize;



	for( i = 0 ; i < loop ; i++ ){

		/* �f�[�^�̓ǂݍ��� */

		if( OK != readBinFile( &data, infP, analizeP, binFp )){

			return( ERROR );

		}

		else{

			binToValue( &result, analizeP, data );	/* �����l�ϊ� */

			_lineBuffer[0] = '\0';

			if( _style == 0 ){

				/* �����l�̃^�C�v */

				if( analizeP->vDataType[0] == 'B' ){

					/* �r�b�g�f�[�^�̏ꍇ */

					if( !i ){

						/* ���񂾂��̏����i�^�C�g���j*/

						readPreviousData();	/* �}�[�W�I�v�V�����̏ꍇ�ɑO��̃f�[�^���o�b�t�@�̐擪�ɃZ�b�g���� */

						sprintf( &_lineBuffer[strlen(_lineBuffer)], "%s,,,,,,,,,\n", analizeP->traceName );/* �g���[�X�� */

						outputTo();		/* �o�� */

						readPreviousData();	/* �}�[�W�I�v�V�����̏ꍇ�ɑO��̃f�[�^���o�b�t�@�̐擪�ɃZ�b�g���� */

						sprintf( &_lineBuffer[strlen(_lineBuffer)], "Result,,,,,,,,,\n" );/* �����l */

						outputTo();		/* �o�� */

						readPreviousData();	/* �}�[�W�I�v�V�����̏ꍇ�ɑO��̃f�[�^���o�b�t�@�̐擪�ɃZ�b�g���� */

						sprintf( &_lineBuffer[strlen(_lineBuffer)], "(bit8),(bit7),(bit6),(bit5),(bit4),(bit3),(bit2),(bit1),\n" );

						outputTo();		/* �o�� */

					}

					readPreviousData();	/* �}�[�W�I�v�V�����̏ꍇ�ɑO��̃f�[�^���o�b�t�@�̐擪�ɃZ�b�g���� */

					printBitType( result, analizeP );	/* �r�b�g������̍쐬 */

					sprintf( &_lineBuffer[strlen(_lineBuffer)], "\n" );

					outputTo();		/* �o�� */

				}

				else{

					/* �r�b�g�f�[�^�ȊO�̏ꍇ */

					if( !i ){

						/* ���񂾂��̏����i�^�C�g���j*/

						readPreviousData();	/* �}�[�W�I�v�V�����̏ꍇ�ɑO��̃f�[�^���o�b�t�@�̐擪�ɃZ�b�g���� */

						sprintf( &_lineBuffer[strlen(_lineBuffer)], "%s,\n", analizeP->traceName );/* �g���[�X�� */

						outputTo();		/* �o�� */

						readPreviousData();	/* �}�[�W�I�v�V�����̏ꍇ�ɑO��̃f�[�^���o�b�t�@�̐擪�ɃZ�b�g���� */

						sprintf( &_lineBuffer[strlen(_lineBuffer)], "Result,\n" );		/* �����l */

						outputTo();		/* �o�� */

					}

					readPreviousData();	/* �}�[�W�I�v�V�����̏ꍇ�ɑO��̃f�[�^���o�b�t�@�̐擪�ɃZ�b�g���� */

					sprintf( &_lineBuffer[strlen(_lineBuffer)], "%-14.7E,\n", result );

					outputTo();		/* �o�� */

				}

			}

			else if( _style == 1 ){

				/* �����l �P�ʕ����̃^�C�v */

				if( analizeP->vDataType[0] == 'B' ){

					/* �r�b�g�f�[�^�̏ꍇ */

					if( !i ){

						/* ���񂾂��̏����i�^�C�g���j*/

						readPreviousData();	/* �}�[�W�I�v�V�����̏ꍇ�ɑO��̃f�[�^���o�b�t�@�̐擪�ɃZ�b�g���� */

						sprintf( &_lineBuffer[strlen(_lineBuffer)], "%s,,,,,,,,,\n", analizeP->traceName );/* �g���[�X�� */

						outputTo();		/* �o�� */

						readPreviousData();	/* �}�[�W�I�v�V�����̏ꍇ�ɑO��̃f�[�^���o�b�t�@�̐擪�ɃZ�b�g���� */

						sprintf( &_lineBuffer[strlen(_lineBuffer)], "Result,,,,,,,,Unit,\n" );/* �����l �P�� */

						outputTo();		/* �o�� */

						readPreviousData();	/* �}�[�W�I�v�V�����̏ꍇ�ɑO��̃f�[�^���o�b�t�@�̐擪�ɃZ�b�g���� */

						sprintf( &_lineBuffer[strlen(_lineBuffer)], "(bit8),(bit7),(bit6),(bit5),(bit4),(bit3),(bit2),(bit1),\n" );

						outputTo();		/* �o�� */

					}

					readPreviousData();	/* �}�[�W�I�v�V�����̏ꍇ�ɑO��̃f�[�^���o�b�t�@�̐擪�ɃZ�b�g���� */

					printBitType( result, analizeP );	/* �r�b�g������̍쐬 */

					sprintf( &_lineBuffer[strlen(_lineBuffer)], "%s,\n", analizeP->vUnit );	/* �P�ʕ�����̍쐬 */

					outputTo();		/* �o�� */

				}

				else{

					/* �r�b�g�f�[�^�ȊO�̏ꍇ */

					if( !i ){

						/* ���񂾂��̏����i�^�C�g���j*/

						readPreviousData();	/* �}�[�W�I�v�V�����̏ꍇ�ɑO��̃f�[�^���o�b�t�@�̐擪�ɃZ�b�g���� */

						sprintf( &_lineBuffer[strlen(_lineBuffer)], "%s,,\n", analizeP->traceName );/* �g���[�X�� */

						outputTo();		/* �o�� */

						readPreviousData();	/* �}�[�W�I�v�V�����̏ꍇ�ɑO��̃f�[�^���o�b�t�@�̐擪�ɃZ�b�g���� */

						sprintf( &_lineBuffer[strlen(_lineBuffer)], "Result,Unit,\n" );		/* �����l �P�� */

						outputTo();		/* �o�� */

						readPreviousData();	/* �}�[�W�I�v�V�����̏ꍇ�ɑO��̃f�[�^���o�b�t�@�̐擪�ɃZ�b�g���� */

						sprintf( &_lineBuffer[strlen(_lineBuffer)], ",,\n" );				/* �����l �P�� */

						outputTo();		/* �o�� */

					}

					readPreviousData();	/* �}�[�W�I�v�V�����̏ꍇ�ɑO��̃f�[�^���o�b�t�@�̐擪�ɃZ�b�g���� */

					sprintf( &_lineBuffer[strlen(_lineBuffer)], "%-14.7E,%s,\n", result, analizeP->vUnit );

					outputTo();		/* �o�� */

				}

			}

			else if( _style == 2 ){

				/* �f�[�^�ԍ� �����l �P�ʕ����̃^�C�v */

				if( analizeP->vDataType[0] == 'B' ){

					/* �r�b�g�f�[�^�̏ꍇ */

					if( !i ){

						/* ���񂾂��̏����i�^�C�g���j*/

						readPreviousData();	/* �}�[�W�I�v�V�����̏ꍇ�ɑO��̃f�[�^���o�b�t�@�̐擪�ɃZ�b�g���� */

						sprintf( &_lineBuffer[strlen(_lineBuffer)], "%s,,,,,,,,,,\n", analizeP->traceName );/* �g���[�X�� */

						outputTo();		/* �o�� */

						readPreviousData();	/* �}�[�W�I�v�V�����̏ꍇ�ɑO��̃f�[�^���o�b�t�@�̐擪�ɃZ�b�g���� */

						sprintf( &_lineBuffer[strlen(_lineBuffer)], "Point,Result,,,,,,,,Unit,\n" );/* �_�� �����l �P�� */

						outputTo();		/* �o�� */

						readPreviousData();	/* �}�[�W�I�v�V�����̏ꍇ�ɑO��̃f�[�^���o�b�t�@�̐擪�ɃZ�b�g���� */

						sprintf( &_lineBuffer[strlen(_lineBuffer)], ",(bit8),(bit7),(bit6),(bit5),(bit4),(bit3),(bit2),(bit1),\n");

						outputTo();		/* �o�� */

					}

					readPreviousData();	/* �}�[�W�I�v�V�����̏ꍇ�ɑO��̃f�[�^���o�b�t�@�̐擪�ɃZ�b�g���� */

					sprintf( &_lineBuffer[strlen(_lineBuffer)], "%ld,\0", i );

					printBitType( result, analizeP );	/* �r�b�g������̍쐬 */

					sprintf( &_lineBuffer[strlen(_lineBuffer)], "%s,\n", analizeP->vUnit );

					outputTo();		/* �o�� */

				}

				else{

					if( !i ){

						/* ���񂾂��̏����i�^�C�g���j*/

						readPreviousData();	/* �}�[�W�I�v�V�����̏ꍇ�ɑO��̃f�[�^���o�b�t�@�̐擪�ɃZ�b�g���� */

						sprintf( &_lineBuffer[strlen(_lineBuffer)], "%s,,,\n", analizeP->traceName );/* �g���[�X�� */

						outputTo();		/* �o�� */

						readPreviousData();	/* �}�[�W�I�v�V�����̏ꍇ�ɑO��̃f�[�^���o�b�t�@�̐擪�ɃZ�b�g���� */

						sprintf( &_lineBuffer[strlen(_lineBuffer)], "Point,Result,Unit,\n" );	/* �_�� �����l �P�� */

						outputTo();		/* �o�� */

						readPreviousData();	/* �}�[�W�I�v�V�����̏ꍇ�ɑO��̃f�[�^���o�b�t�@�̐擪�ɃZ�b�g���� */

						sprintf( &_lineBuffer[strlen(_lineBuffer)], ",,,\n" );					/* �_�� �����l �P�� */

						outputTo();		/* �o�� */

					}

					readPreviousData();	/* �}�[�W�I�v�V�����̏ꍇ�ɑO��̃f�[�^���o�b�t�@�̐擪�ɃZ�b�g���� */

					sprintf( &_lineBuffer[strlen(_lineBuffer)], "%ld,%-14.7E,%s,\n", i, result, analizeP->vUnit );

					outputTo();		/* �o�� */

				}

			}

			else{

				/* �f�[�^�ԍ� �����l �P�ʕ��� ���f�[�^�̃^�C�v */

				if( analizeP->vDataType[0] == 'B' ){

					/* �r�b�g�f�[�^�̏ꍇ */

					if( !i ){

						/* ���񂾂��̏����i�^�C�g���j*/

						readPreviousData();	/* �}�[�W�I�v�V�����̏ꍇ�ɑO��̃f�[�^���o�b�t�@�̐擪�ɃZ�b�g���� */

						sprintf( &_lineBuffer[strlen(_lineBuffer)], "%s,,,,,,,,,,,\n", analizeP->traceName );/* �g���[�X�� */

						outputTo();		/* �o�� */

						readPreviousData();	/* �}�[�W�I�v�V�����̏ꍇ�ɑO��̃f�[�^���o�b�t�@�̐擪�ɃZ�b�g���� */

						sprintf( &_lineBuffer[strlen(_lineBuffer)], "Point,Result,,,,,,,,Unit,Binary,\n" );

																								/* �_�� �����l �P�� ���f�[�^ */

						outputTo();		/* �o�� */

						readPreviousData();	/* �}�[�W�I�v�V�����̏ꍇ�ɑO��̃f�[�^���o�b�t�@�̐擪�ɃZ�b�g���� */

						sprintf( &_lineBuffer[strlen(_lineBuffer)], ",(bit8),(bit7),(bit6),(bit5),(bit4),(bit3),(bit2),(bit1),\n");

						outputTo();		/* �o�� */

					}

					readPreviousData();	/* �}�[�W�I�v�V�����̏ꍇ�ɑO��̃f�[�^���o�b�t�@�̐擪�ɃZ�b�g���� */

					sprintf( &_lineBuffer[strlen(_lineBuffer)], "%ld,\0", i );

					printBitType( result, analizeP );	/* �r�b�g������̍쐬 */

					sprintf( &_lineBuffer[strlen(_lineBuffer)], "%s,%d(%#x),\n", analizeP->vUnit, (int)result, (int)result );

					outputTo();		/* �o�� */

				}

				else{

					if( !i ){

						/* ���񂾂��̏����i�^�C�g���j*/

						readPreviousData();	/* �}�[�W�I�v�V�����̏ꍇ�ɑO��̃f�[�^���o�b�t�@�̐擪�ɃZ�b�g���� */

						sprintf( &_lineBuffer[strlen(_lineBuffer)], "%s,,,,\n", analizeP->traceName );/* �g���[�X�� */

						outputTo();		/* �o�� */

						readPreviousData();	/* �}�[�W�I�v�V�����̏ꍇ�ɑO��̃f�[�^���o�b�t�@�̐擪�ɃZ�b�g���� */

						sprintf( &_lineBuffer[strlen(_lineBuffer)], "Point,Result,Unit,Binary,\n" );/* �_�� �����l �P�� ���f�[�^ */

						outputTo();		/* �o�� */

						readPreviousData();	/* �}�[�W�I�v�V�����̏ꍇ�ɑO��̃f�[�^���o�b�t�@�̐擪�ɃZ�b�g���� */

						sprintf( &_lineBuffer[strlen(_lineBuffer)], ",,,,\n" );						/* �_�� �����l �P�� ���f�[�^ */

						outputTo();		/* �o�� */

					}

					readPreviousData();	/* �}�[�W�I�v�V�����̏ꍇ�ɑO��̃f�[�^���o�b�t�@�̐擪�ɃZ�b�g���� */

					sprintf( &_lineBuffer[strlen(_lineBuffer)], "%ld,%-14.7E,%s,%-14.7E,\n", i, result, analizeP->vUnit, data );

					outputTo();		/* �o�� */

				}

			}

		}

	}

	if( _mergeSw == On ){

		if( fclose( t1_fp ) == EOF ){				/* �������݃t�@�C���̃N���[�Y */

			printf( "Error temp file close \n" );

			exit( -1 );

		}

	}

	if( _mergeSw == On && _fileSw == On ){

		if( fclose( t2_fp ) == EOF ){				/* �ǂݍ��݃t�@�C���̃N���[�Y */

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

*	�ց@���@��	:	printBitType										*

*																		*

*	�@		�\	:	�r�b�g�^�C�v�̈�									*

*																		*

*	���@�@�@���@:	INT	printBitType( DREAL data, ANRZ* analizeP )		*

*																		*

*	���̓p�����^:	DREAL	data		: �󎚃f�[�^					*

*					ANRZ*	analizeP	: ��񕔂̃|�C���^�[			*

*																		*

*	�o�̓p�����^:	None												*

*																		*

*	��		�l	:	�L��	OK		����	ERROR						*

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

*	�ց@���@��	:	readPreviousData									*

*																		*

*	�@		�\	:	�O�񐶐������`�r�b�h�h�t�@�C������ǂ�				*

*																		*

*	���@�@�@���@:	INT	readPreviousData( )								*

*																		*

*	���̓p�����^:	None												*

*																		*

*	�o�̓p�����^:	�O��̃f�[�^��_lineBuffer�̐擪�ɓǂݍ���			*

*																		*

*	��		�l	:	�L��	OK		����	ERROR						*

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

*	�ց@���@��	:	outputTo											*

*																		*

*	�@		�\	:	�W���o�͂ƃt�@�C���o��								*

*																		*

*	���@�@�@���@:	INT	outputTo()										*

*																		*

*	���̓p�����^:	None												*

*																		*

*	�o�̓p�����^:	None												*

*																		*

*	��		�l	:	�L��	OK		����	ERROR						*

*																		*

*ENDF*******************************************************************/

INT	outputTo()

{

	if( _mergeSw == On ){

		fputs( _lineBuffer, t1_fp );/* �}�[�W�I�v�V�������Ƀt�@�C���ɏo�� */

	}

	else{

		printf( "%s", _lineBuffer );/* �W���o�� */

	}

	_lineBuffer[0] = '\0';

	return( OK );

}


/*STARTF*****************************************************************

*																		*

*	�ց@���@��	:	getEndianMode										*

*																		*

*	�@		�\	:	�G���f�B�A�����[�h�𓾂�							*

*						�i�R���p�C���̃p�����[�^�؂�ւ��j				*

*																		*

*	���@�@�@���@:	INT	getEndianMode( INF* infP, UCHR endianMode )		*

*																		*

*	���̓p�����^:	INF*	infP		: ��񕔂̃|�C���^�[			*

*					UCHR	endianMode	: �G���f�B�A�����[�h			*

*																		*

*	�o�̓p�����^:	INF*	infP		: ����							*

*																		*

*	��		�l	:	�L��	OK		����	ERROR						*

*																		*

*ENDF*******************************************************************/

void getEndianMode( INF* infP, UCHR endianMode )

{

	if(( UCHR )BigEndian == endianMode ){

		/* �a�����G���f�B�A���̏ꍇ */

		#ifdef BIGENDIAN

			infP->endianMode = ( UCHR )Equal;

		  #else

			infP->endianMode = ( UCHR )NotEqual;

		#endif

	}

	else{

		/* �k�����������G���f�B�A���̏ꍇ */

		#ifdef BIGENDIAN

			infP->endianMode = ( UCHR )NotEqual;

		  #else

			infP->endianMode = ( UCHR )Equal;

		#endif

	}

}


/*STARTF*****************************************************************

*																		*

*	�ց@���@��	:	openFile											*

*																		*

*	�@		�\	:	�t�@�C���I�[�v������								*

*																		*

*	���@�@�@���@:	INT	openFile( UCHR* fileName, UCHR mode )			*

*																		*

*	���̓p�����^:	UCHR*	fileName	: �t�@�C����					*

*					UCHR	mode		: ���[�h						*

*																		*

*	�o�̓p�����^:	None												*

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

*	�ց@���@��	:	referLabel											*

*																		*

*	�@		�\	:	���x��������Ō���									*

*																		*

*	���@�@�@���@:	INT	referLabel( UCHR* label, UCHR groupMode,		*

*									INT group, UCHR* buffP,				*

*									FILE* ascFp )						*

*																		*

*	���̓p�����^:	UCHR*	label		: ���x��������|�C���^�[		*

*					UCHR	groupMode	: �����ꏊ						*

*					INT		group		: �O���[�v�ԍ�					*

*					UCHR*	buffP		: �����Ώۃo�b�t�@�|�C���^�[	*

*					FILE*	ascFp		: �`�r�b�h�h�t�@�C���|�C���^�[	*

*																		*

*	�o�̓p�����^:	None												*

*																		*

*	��		�l	:	�L��	TRUE		����	FALSE					*

*																		*

*ENDF*******************************************************************/

INT referLabel( UCHR* label, UCHR groupMode, INT group, UCHR* buffP, FILE* ascFp )

{

	static	UCHR	labelBuffer[Buff];

	UCHR*	frontP;

	UCHR*	labelP;


	frontP = buffP;		/* �o�b�t�@�|�C���^�[�Z�[�u */

	/* ���̃O���[�v��������̐��� */

	makeGroupString( groupMode, group + 2, &_groupLimitBuffer[0] );


	while( NULL != fgets(( CHR* )buffP, ( SHORT )MaxBuff, ascFp )){

		labelP = &labelBuffer[0];

		while( '\n' !=	*buffP ){	/* ���s�������܂ŌJ��Ԃ� */

			if( 0 != isspace(( SHORT )*buffP ))

				buffP++;			/* �X�y�[�X�̏ꍇ�ɂ̓|�C���^�[��i�߂� */

			else

				break;				/* �X�y�[�X�ȊO�̏ꍇ�ɔ����� */

		}


		/* �R�����g�s�̏ꍇ�ɂ̓X�L�b�v���� */

		if(( '/' == *buffP ) && ( '/' == *( buffP + 1 )))	continue;


		/* �X�y�[�X�������܂ŕ���������[�J���o�b�t�@�ilabelBuffer�j�ɃR�s�[���� */

		while( 0 == isspace(( SHORT )*buffP )){

			*labelP++ = *buffP++;

		}

		*labelP = '\0';


		/* �擾����������Ǝw�肳�ꂽ���x����������r���� */

		if( 0 == strcmp(( CHR* )labelBuffer, ( CHR* )label )){

			return( TRUE );

		}

		/* ���̃O���[�v���܂ŗ����甲���� */

		if( 0 == strcmp(( CHR* )labelBuffer, ( CHR* )_groupLimitBuffer )){

			break;

		}

		buffP = frontP;

	}

	return( FALSE );

}


/*STARTF*****************************************************************

*																		*

*	�ց@���@��	:	makeGroupString										*

*																		*

*	�@		�\	:	�O���[�v���̕����񐶐�								*

*																		*

*	���@�@�@���@:	INT	makeGroupString( UCHR groupMode, INT group, 	*

*										 UCHR* groupBuffP )				*

*																		*

*	���̓p�����^:	UCHR	groupMode	: �쐬��($Public or $MediaInfo)	*

*					INT		group		: �O���[�v�ԍ�					*

*																		*

*	�o�̓p�����^:	UCHR*	groupBuffp	: ����							*

*																		*

*	��		�l	:														*

*																		*

*ENDF*******************************************************************/

void makeGroupString( UCHR groupMode, INT group, UCHR* groupBuffP )

{

	UCHR		count[20];	/*group counter*/


	if(( UCHR )PublicMode == groupMode ){

		/* $Group�̈�p�̕����񐶐� */

		strcpy(( CHR* )groupBuffP, ( CHR* )_Group );

		sprintf(( CHR* )count, "%d", group );

		strcat(( CHR* )groupBuffP, ( CHR* )count );

	}

	else if(( UCHR )PrivateMode == groupMode ){

		/* $Private�̈�p�̕����񐶐� */

		strcpy(( CHR* )groupBuffP, ( CHR* )_PrivateInfo );

	}

	else{

		/* $MGroup�̈�p�̕����񐶐� */

	    strcpy(( CHR* )groupBuffP, ( CHR* )_MGroup );

		sprintf(( CHR* )count, "%d", group );

		strcat(( CHR* )groupBuffP, ( CHR* )count );

	}

}


/*STARTF*****************************************************************

*																		*

*	�ց@���@��	:	getData												*

*																		*

*	�@		�\	:	�p�����[�^�̓ǂݍ���								*

*																		*

*	���@�@�@���@:	INT	getData( UCHR* destP, UCHR* srcP, INT trace )	*

*																		*

*	���̓p�����^:	UCHR*	destP	: �f�B�X�e�B�l�[�V�����̃|�C���^�[	*

*					UCHR*	srcP	: �\�[�X�̃|�C���^�[				*

*					INT		trace	: �g���[�X�ԍ�						*

*																		*

*	�o�̓p�����^:	UCHR*	destP	: ����								*

*																		*

*	��		�l	:	�L��	OK		����	ERROR						*

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

*	�ց@���@��	:	referGroup											*

*																		*

*	�@		�\	:	�O���[�v�ԍ��ł̌���								*

*																		*

*	���@�@�@���@:	INT	referGroup( UCHR groupMode, INT group,			*

*									FILE* ascFp )						*

*																		*

*	���̓p�����^:	UCHR	groupMode	: �����ꏊ�i$Public/$MediaInfo�j*

*					INT		group		: �O���[�v�ԍ�					*

*					FILE*	ascFp		: �`�r�b�h�h�t�@�C���|�C���^�[	*

*																		*

*	�o�̓p�����^:	None												*

*																		*

*	��		�l	:	�L��	OK		����	ERROR						*

*																		*

*ENDF*******************************************************************/

INT referGroup( UCHR groupMode, INT group, FILE* ascFp )

{

	/* �O���[�v���̐��� */

	makeGroupString( groupMode, group + 1, &_groupBuffer[0] );

	/* ���������O���[�v���Ō��� */

	if( FALSE == referLabel( &_groupBuffer[0], groupMode, group, _buffer, ascFp ))

	{

		printf( "Can't Find %s\n", _groupBuffer ); 

		return( ERROR );

	}

	return( OK );

}


/*STARTF*****************************************************************

*																		*

*	�ց@���@��	:	work												*

*																		*

*	�@		�\	:	�`�r�b�h�h�t�@�C������w�肳�ꂽ���𔲂��o��		*

*																		*

*	���@�@�@���@:	INT	work( UCHR* label, UCHR* destP, UCHR groupMode	*

*							  INT group, INT trace, INT block,			*

*							  FILE* ascFp )								*

*																		*

*	���̓p�����^:	UCHR*	label		: �p�����[�^���x���̃|�C���^�[	*

*					UCHR*	destP		: �i�[��|�C���^�[				*

*					UCHR	groupMode	: �����ꏊ						*

*					INT		group		: �O���[�v�ԍ��i�O�`�j			*

*					INT		trace		: �g���[�X�ԍ��i�O�`�j			*

*					INT		block		: �u���b�N�ԍ��i�O�`�j			*

*					FILR*	ascFp		: �`�r�b�h�h�t�@�C���|�C���^�[	*

*																		*

*	�o�̓p�����^:	UCHR*	destP		: ����							*

*																		*

*	��		�l	:	�L��	OK		����	ERROR						*

*																		*

*ENDF*******************************************************************/

INT work( UCHR* label, UCHR* destP, UCHR groupMode, INT group,

		  INT trace, INT block, FILE* ascFp )

{

	/* ���x�����Ō��� */

	if( OK != getParameterData( label, destP, groupMode, group,

								trace, block, NumberMode, ascFp )){

		/* �u���b�N�ԍ��Ō��� */

		if( OK != getParameterData( label, destP, groupMode, group,

									trace, block, NoNumberMode, ascFp )){

			/* ������Ȃ����� */

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

*	�ց@���@��	:	getParameterData									*

*																		*

*	�@		�\	:	�`�r�b�h�h�t�@�C������w�肳�ꂽ���𔲂��o��		*

*																		*

*	���@�@�@���@:	INT	work( UCHR* label, UCHR* destP, UCHR groupMode	*

*							  INT group, INT trace, INT block,			*

*							  UCHR mode, FILE* ascFp )					*

*																		*

*	���̓p�����^:	UCHR*	label		: �p�����[�^���x���̃|�C���^�[	*

*					UCHR*	destP		: �i�[��|�C���^�[				*

*					UCHR	groupMode	: �����ꏊ						*

*					INT		group		: �O���[�v�ԍ��i�O�`�j			*

*					INT		trace		: �g���[�X�ԍ��i�O�`�j			*

*					INT		block		: �u���b�N�ԍ��i�O�`�j			*

*					UCHR	mode		: �������[�h					*

*					FILR*	ascFp		: �`�r�b�h�h�t�@�C���|�C���^�[	*

*																		*

*	�o�̓p�����^:	UCHR*	destP		: ����							*

*																		*

*	��		�l	:	�L��	OK		����	ERROR						*

*																		*

*ENDF*******************************************************************/

INT getParameterData( UCHR* label, UCHR* destP, UCHR groupMode, INT group,

					  INT trace, INT block, UCHR mode, FILE* ascFp )

{

	static		UCHR	labelBuffer[Buff];

	UCHR		count[20];


	fseek( ascFp, 0L, SEEK_SET );	/* �`�r�b�h�h�t�@�C���̐擪�Ɉړ� */


	if(( INT )NoGroupData != group ){

		/* �O���[�v���Ō��� */

		if( OK != referGroup( groupMode, group, ascFp )){

			return( ERROR );								/* ������Ȃ����� */

		}

	}


	/* �u���b�N���̐��� */

	strcpy(( CHR* )labelBuffer, ( CHR* )label );

	if(( UCHR )NumberMode == mode ){

		sprintf(( CHR* )count, "%d", block + 1 );

		strcat(( CHR* )labelBuffer, ( CHR* )count );

	}


	/* �u���b�N���Ō��� */

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

*	�ց@���@��	:	getByte												*

*																		*

*	�@		�\	:	�f�[�^�^�C�v����o�C�g�����v�Z����					*

*																		*

*	���@�@�@���@:	INT	getByte( UCHR* dataType )						*

*																		*

*	���̓p�����^:	UCHR*	dataType	: �f�[�^�^�C�v������̃|�C���^�[*

*																		*

*	�o�̓p�����^:	None												*

*																		*

*	��		�l	:	�o�C�g��											*

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

*	�ց@���@��	:	getSize												*

*																		*

*	�@		�\	:	�u���b�N�T�C�Y�𓾂�								*

*																		*

*	���@�@�@���@:	INT	getSize( INT group,INT trace, INT block,		*

*								 INT* size, FILE* ascFp )				*

*																		*

*	���̓p�����^:	INT		group		: �O���[�v�ԍ�					*

*					INT		trace		: �g���[�X�ԍ�					*

*					INT		block		: �u���b�N�ԍ�					*

*					FILE*	ascFp		: �`�r�b�h�h�t�@�C���̃|�C���^�[*

*																		*

*	�o�̓p�����^:	INT*	size		: �u���b�N�T�C�Y(Byte)			*

*																		*

*	��		�l	:	�L��	OK		����	ERROR						*

*																		*

*ENDF*******************************************************************/

INT getSize( INT group, INT trace, INT block, INT* size, FILE* ascFp )

{

	INT		blockSize;

	INT		byte;


	/* �u���b�N�T�C�Y�𓾂�*/

	if( OK == work( _BlockSize, _destBuffer, ( UCHR )PublicMode,

					group, trace, block, ascFp ))

		blockSize = atol(( CHR* )_destBuffer );

	else

		return( ERROR );

	/* �f�[�^�^�C�v�𓾂� */

	if( OK != work( _VDataType, _destBuffer, ( UCHR )PublicMode,

					group, trace, block, ascFp ))

		return( ERROR );

	byte = getByte( &_destBuffer[0] );

	*size += byte * blockSize;

	return( OK );

}


/*STARTF*****************************************************************

*																		*

*	�ց@���@��	:	seekBinFp											*

*																		*

*	�@		�\	:	�o�C�i���[�t�@�C���̎w��ꏊ�ɃV�[�N����			*

*																		*

*	���@�@�@���@:	INT	seekBinFp( INF* infP, INT group,INT trace,		*

*								   INT block, FILE* ascFp, FILE* binFp )*

*																		*

*	���̓p�����^:	INF*	infP		: ��񕔂̃|�C���^�[			*

*					INT		group		: �O���[�v�ԍ�					*

*					INT		trace		: �g���[�X�ԍ�					*

*					INT		block		: �u���b�N�ԍ�					*

*					FILE*	ascFp		: �`�r�b�h�h�t�@�C���̃|�C���^�[*

*					FILE*	binFp		: �o�C�i���[�t�@�C���̃|�C���^�[*

*																		*

*	�o�̓p�����^:	None												*

*																		*

*	��		�l	:	�L��	OK		����	ERROR						*

*																		*

*ENDF*******************************************************************/

INT seekBinFp( INF* infP, INT group, INT trace, INT block, FILE* ascFp, FILE* binFp )

{

	INT		seekSize = 0;


	/* �g���[�X�^�C�v�̏ꍇ */

	if(( UCHR )TraceUnit == infP->dataFormat ){

		/* �V�[�N�T�C�Y�����߂� */

		if( OK != getTraceSeekSize( group, trace, block, &seekSize, ascFp ))

		    return( ERROR );

	}

	/* �u���b�N�^�C�v�̏ꍇ */

	else{

		/* �V�[�N�T�C�Y�����߂� */

		if( OK != getBlockSeekSize( infP, group, trace, block, &seekSize, ascFp ))

		    return( ERROR );

	}

	/* ���܂����V�[�N�T�C�Y�ɃI�t�Z�b�g�ʂ̒������s�� */

	seekSize += infP->dataOffset;

	/* �V�[�N���� */

	fseek( binFp, seekSize, SEEK_SET );

	return( OK );

}


/*STARTF*****************************************************************

*																		*

*	�ց@���@��	:	getTraceSeekSize									*

*																		*

*	�@		�\	:	�V�[�N�T�C�Y�i�g���[�X�^�C�v�j�����߂�				*

*																		*

*	���@�@�@���@:	INT	getTraceSeekSize( INT group, INT trace,			*

*										  INT block, INT* seekSize,		*

										  FILE* ascFp )					*

*																		*

*	���̓p�����^:	INT		group		: �O���[�v�ԍ�					*

*					INT		trace		: �g���[�X�ԍ�					*

*					INT		block		: �u���b�N�ԍ�					*

*					FILE*	ascFp		: �`�r�b�h�h�t�@�C���̃|�C���^�[*

*																		*

*	�o�̓p�����^:	INT*	seekSize	: �V�[�N�T�C�Y					*

*																		*

*	��		�l	:	�L��	OK		����	ERROR						*

*																		*

*ENDF*******************************************************************/

INT getTraceSeekSize( INT group, INT trace, INT block, INT* seekSize, FILE* ascFp )

{

	INT		i, j, k;

	INT		blockNumber;

	INT		traceNumber;


	for( i = 0 ; i < group ; i++ ){

		/* �g���[�X�ԍ��𓾂� */

		if( OK == work( _TraceNumber, _destBuffer, ( UCHR )PublicMode,

						i, 0, ( INT )NoBlockData, ascFp ))

			traceNumber = atol(( CHR* )_destBuffer );

		else

			return( ERROR );

		/* �u���b�N�ԍ��𓾂� */

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


	/* �u���b�N�ԍ��𓾂� */

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

*	�ց@���@��	:	getBlockSeekSize									*

*																		*

*	�@		�\	:	�V�[�N�T�C�Y�i�u���b�N�^�C�v�j�����߂�				*

*																		*

*	���@�@�@���@:	INT	getBlockSeekSize( INF* infP, INT group,			*

*										  INT trace, INT block,			*

*										  INT* seekSize, FILE* ascFp )	*

*																		*

*	���̓p�����^:	INF*	infP		: ��񕔂̃|�C���^�[			*

*					INT		group		: �O���[�v�ԍ�					*

*					INT		trace		: �g���[�X�ԍ�					*

*					INT		block		: �u���b�N�ԍ�					*

*					FILE*	ascFp		: �`�r�b�h�h�t�@�C���̃|�C���^�[*

*																		*

*	�o�̓p�����^:	INT*	seekSize	: �V�[�N�T�C�Y					*

*																		*

*	��		�l	:	�L��	OK		����	ERROR						*

*																		*

*ENDF*******************************************************************/

INT getBlockSeekSize( INF* infP, INT group, INT trace, INT block, INT* seekSize, FILE* ascFp )

{

	INT		ii, j, k;

	UINT	i;

	INT		traceNumber;


	for( k = 0 ; k < block ; k++ ){

	    for( i = 0 ; i < infP->groupNumber ; i++ ){

			/* �g���[�X�ԍ��𓾂� */

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

		/* �g���[�X�ԍ��𓾂� */

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

*	�ց@���@��	:	change2Byte											*

*																		*

*	�@		�\	:	���[�o�C�g�ƃn�C�o�C�g�̓���ւ�					*

*																		*

*	���@�@�@���@:	INT	change2Byte( TYPE2* data )						*

*																		*

*	���̓p�����^:	None												*

*																		*

*	�o�̓p�����^:	TYPE2*	data		: ����							*

*																		*

*	��		�l	:														*

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

*	�ց@���@��	:	change4Byte											*

*																		*

*	�@		�\	:	���[�o�C�g�ƃn�C�o�C�g�̓���ւ�					*

*																		*

*	���@�@�@���@:	INT	change4Byte( TYPE4* data )						*

*																		*

*	���̓p�����^:	None												*

*																		*

*	�o�̓p�����^:	TYPE4*	data		: ����							*

*																		*

*	��		�l	:														*

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

*	�ց@���@��	:	change8Byte											*

*																		*

*	�@		�\	:	���[�o�C�g�ƃn�C�o�C�g�̓���ւ�					*

*																		*

*	���@�@�@���@:	INT	change8Byte( TYPE4* data )						*

*																		*

*	���̓p�����^:	None												*

*																		*

*	�o�̓p�����^:	TYPE8*	data		: ����							*

*																		*

*	��		�l	:														*

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

*	�ց@���@��	:	readBinFile											*

*																		*

*	�@		�\	:	�o�C�i���[�t�@�C���̓ǂݍ���						*

*																		*

*	���@�@�@���@:	INT	readBinFile( DREAL* data, INF* infP,	 		*

*									 ANRZ* analizeP, FILE* binFp )		*

*																		*

*	���̓p�����^:	INF*	infP		: ��񕔂̃|�C���^�[			*

*					ANRZ*	analizeP	: ��񕔂̃|�C���^�[			*

*					FILE*	binFp		: �o�C�i���[�t�@�C���̃|�C���^�[*

*																		*

*	�o�̓p�����^:	DREAL*	data		: ����							*

*																		*

*	��		�l	:	�L��	OK		����	ERROR						*

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

		/* �f�[�^�^�C�v�̐擪�P�o�C�g���h�̏ꍇ */

		if( 'S' == analizeP->vDataType[1] ){

		    /* �����r�̏ꍇ */

			if( OK != signedWork( data, byte, infP, allTypeP ))

				return( ERROR );

		    }

		else if( 'U' == analizeP->vDataType[1] ){

		    /* �����t�̏ꍇ */

			if( OK != unsignedWork( data, byte, infP, allTypeP ))

				return( ERROR );

		}

	}

	else if( 'B' == analizeP->vDataType[0] ){

		/* �f�[�^�^�C�v�̐擪�P�o�C�g��B�̏ꍇ */

		if( OK != unsignedWork( data, byte, infP, allTypeP ))

				return( ERROR );

	}

	else{

		if( 'F' == analizeP->vDataType[0] ){

		/* �f�[�^�^�C�v�̐擪�P�o�C�g���e�̏ꍇ */

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

*	�ց@���@��	:	signedWork											*

*																		*

*	�@		�\	:	signed�f�[�^��double�Ɋg��							*

*																		*

*	���@�@�@���@:	INT	signedWork( DREAL* data, INT byte, INF* infP,	*

*									ALLTYPE* allType )					*

*																		*

*	���̓p�����^:	INT			byte		: �f�[�^�̃o�C�g��			*

*					INF*		infP		: ��񕔂̃|�C���^�[		*

*					ALLTYPE*	allTypeP	: �f�[�^�̃|�C���^�[		*

*																		*

*	�o�̓p�����^:	DREAL*		data		: ����						*

*																		*

*	��		�l	:	�L��	OK		����	ERROR						*

*																		*

*ENDF*******************************************************************/

INT signedWork( DREAL* data, INT byte, INF* infP, ALLTYPE* allTypeP )

{

	switch( byte ){

	  case 1:	/* CHR�^�C�v */

	    *data = ( DREAL )allTypeP->chData;

		break;

	  case 2:	/* SHORT�^�C�v */

		if(( UCHR )NotEqual == infP->endianMode )

		    change2Byte(( TYPE2* )&allTypeP->shData );

		*data = ( DREAL )allTypeP->shData;

		break;

	  case 4:	/* INT�^�C�v */

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

*	�ց@���@��	:	unsignedWork										*

*																		*

*	�@		�\	:	unsigned�f�[�^��double�Ɋg��						*

*																		*

*	���@�@�@���@:	INT	unsignedWork( DREAL* data, INT byte, INF* infP,	*

*									ALLTYPE* allType )					*

*																		*

*	���̓p�����^:	INT			byte		: �f�[�^�̃o�C�g��			*

*					INF*		infP		: ��񕔂̃|�C���^�[		*

*					ALLTYPE*	allTypeP	: �f�[�^�̃|�C���^�[		*

*																		*

*	�o�̓p�����^:	DREAL*		data		: ����						*

*																		*

*	��		�l	:	�L��	OK		����	ERROR						*

*																		*

*ENDF*******************************************************************/

INT unsignedWork( DREAL* data, INT byte, INF* infP, ALLTYPE* allTypeP )

{

	switch( byte ){

	  case 1:	/* UCHR�^�C�v */

	    *data = ( DREAL )allTypeP->uchData;

		break;

	  case 2:	/* USHORT�^�C�v */

		if(( UCHR )NotEqual == infP->endianMode )

		    change2Byte(( TYPE2* )&allTypeP->ushData );

		*data = ( DREAL )allTypeP->ushData;

		break;

	  case 4:	/* UINT�^�C�v */

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

*	�ց@���@��	:	floatWork											*

*																		*

*	�@		�\	:	float�f�[�^��double�Ɋg��							*

*																		*

*	���@�@�@���@:	INT	floatWork( DREAL* data, INT byte, INF* infP,	*

*								   ALLTYPE* allType )					*

*																		*

*	���̓p�����^:	INT			byte		: �f�[�^�̃o�C�g��			*

*					INF*		infP		: ��񕔂̃|�C���^�[		*

*					ALLTYPE*	allTypeP	: �f�[�^�̃|�C���^�[		*

*																		*

*	�o�̓p�����^:	DREAL*		data		: ����						*

*																		*

*	��		�l	:	�L��	OK		����	ERROR						*

*																		*

*ENDF*******************************************************************/

INT floatWork( DREAL* data, INT byte, INF* infP, ALLTYPE* allTypeP )

{

	switch( byte ){

	  case 4:	/* SREAL�^�C�v */

		if(( UCHR )NotEqual == infP->endianMode )

			change4Byte(( TYPE4* )&allTypeP->srData );

		*data = ( DREAL )allTypeP->srData;

		break;

	  case 8:	/* DREAL�^�C�v */

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

*	�ց@���@��	:	binToValue											*

*																		*

*	�@		�\	:	�o�C�i���[�f�[�^�𕨗��l�ɕϊ�						*

*																		*

*	���@�@�@���@:	INT	binToValue( DREAL* result, ANRZ* analizeP, 		*

*									DREAL data )						*

*																		*

*	���̓p�����^:	ANRZ*	analizeP	: ��񕔂̃|�C���^�[			*

*					DREAL	data		: �o�C�i���[�f�[�^				*

*																		*

*	�o�̓p�����^:	DREAL*	result		: ���ʁi�����l�j				*

*																		*

*	��		�l	:	�L��	OK		����	ERROR						*

*																		*

*ENDF*******************************************************************/

void binToValue( DREAL* result, ANRZ* analizeP, DREAL data )

{


	*result = analizeP->vResolution * data + analizeP->vOffset;


}


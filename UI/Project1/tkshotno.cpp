#include "tkshotno.h"

static char shot_num_file_path[256];

int TKSNIncrementShotNo(void)
{
	return 0;
}

int TKSNGetShotNo(void)
{
	return 0;
}

int TKSNSetShotNo(void)
{
	return 0;
}

int TKSNGetShotNoFilePath(char* file_path)
{
	return strcpy_s(shot_num_file_path, file_path);
}

int TKSNSetShotNoFilePath(char* file_path)
{
	return strcpy_s(shot_num_file_path, file_path);
}

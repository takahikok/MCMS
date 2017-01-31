#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef __TKSHOTNO__
#define __TKSHOTNO__

int TKSNIncrementShotNo(void);
int TKSNGetShotNo(void);
int TKSNSetShotNo(void);
int TKSNGetShotNoFilePath(char* file_path);
int TKSNSetShotNoFilePath(char* file_path);


#endif
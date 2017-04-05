
#ifndef __TKSHOTNO__
#define __TKSHOTNO__


//shot number 
namespace TKSHOTNO
{
	unsigned int GetLastShotNumber();
	unsigned int GetNextShotNumber();
	unsigned int SetLastShotNumber(unsigned int new_local_shot_number);
	unsigned int IncrementShotNumber();
	unsigned int SetShotNumberMax(unsigned int new_local_shot_number_max);
	unsigned int GetShotNumberMax();
}


#endif
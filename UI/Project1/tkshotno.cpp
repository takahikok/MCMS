#include "tkshotno.h"

static unsigned int next_shot_number;
static unsigned int next_shot_number_max;

unsigned int TKSHOTNO::GetLastShotNumber()
{
	return next_shot_number - 1;
}

unsigned int TKSHOTNO::GetNextShotNumber()
{
	return next_shot_number;
}

unsigned int TKSHOTNO::SetLastShotNumber(unsigned int new_local_shot_number)
{
	return next_shot_number = new_local_shot_number + 1;
}

unsigned int TKSHOTNO::IncrementShotNumber()
{
	next_shot_number++;
	if (next_shot_number > next_shot_number_max)
		next_shot_number = 1;
	return next_shot_number;
}

unsigned int TKSHOTNO::SetShotNumberMax(unsigned int new_local_shot_number_max)
{
	return next_shot_number_max = new_local_shot_number_max;
}

unsigned int TKSHOTNO::GetShotNumberMax()
{
	return next_shot_number_max;
}


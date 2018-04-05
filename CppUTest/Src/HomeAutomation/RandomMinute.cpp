#include <stdlib.h>
#include <time.h>
#include <HomeAutomation/RandomMinute.h>

static int s_bound;

void RandomMinute_create(int bound)
{
	srand((unsigned) time(NULL));
	s_bound = bound;
}

void RandomMinute_destroy()
{

}

static int RandomMinute_get_impl()
{
	return s_bound - rand()%(2 * s_bound + 1);
}

int (*RandomMinute_get)() = RandomMinute_get_impl;

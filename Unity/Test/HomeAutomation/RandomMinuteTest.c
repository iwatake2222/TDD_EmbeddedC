#include <stdlib.h>
#include <string.h>
#include <HomeAutomation/RandomMinute.h>
#include <unity_fixture.h>

TEST_GROUP(RandomMinute);

enum {
	BOUND = 30,
};
int s_minute;

TEST_SETUP(RandomMinute)
{
	RandomMinute_create(BOUND);
	srand(1);
}

TEST_TEAR_DOWN(RandomMinute)
{
	RandomMinute_destroy();
}

void assertMinuteIsRange()
{
	if (s_minute < -BOUND || BOUND < s_minute) {
		printf("bad minute value: %d\n", s_minute);
		TEST_FAIL_MESSAGE("minute out of range");
	}
}


TEST(RandomMinute, GetIsInRange)
{
	for (int i = 0; i < 100; i++) {
		s_minute = RandomMinute_get();
		assertMinuteIsRange();
	}
}

TEST(RandomMinute, AllValuesPossible)
{
	int hit[2 * BOUND + 1];
	memset(hit, 0, sizeof(hit));

	for (int i = 0; i < 300; i++) {
		s_minute = RandomMinute_get();
		assertMinuteIsRange();
		hit[s_minute + BOUND]++;
	}

	for (int i = 0; i < 2 * BOUND + 1; i++) {
		CHECK(hit[i] > 0);
	}
}

/*** TEST_RUNNER (Don't forget to call RUN_TEST_GROUP) ***/
TEST_GROUP_RUNNER(RandomMinute)
{
	RUN_TEST_CASE(RandomMinute, GetIsInRange);
	RUN_TEST_CASE(RandomMinute, AllValuesPossible);
}


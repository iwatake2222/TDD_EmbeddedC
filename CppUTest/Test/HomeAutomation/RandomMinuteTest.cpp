#include <stdlib.h>
#include <string.h>
#include <HomeAutomation/RandomMinute.h>
#include <CppUTest/TestHarness.h>

enum {
	BOUND = 30,
};

TEST_GROUP(RandomMinute)
{
	int m_minute;
	void setup()
	{
		RandomMinute_create(BOUND);
		srand(1);
	}

	void teardown()
	{
		RandomMinute_destroy();
	}

	void assertMinuteIsRange()
	{
		if (m_minute < -BOUND || BOUND < m_minute) {
			printf("bad minute value: %d\n", m_minute);
			FAIL("minute out of range");
		}
	}

};

TEST(RandomMinute, GetIsInRange)
{
	for (int i = 0; i < 100; i++) {
		m_minute = RandomMinute_get();
		assertMinuteIsRange();
	}
}

TEST(RandomMinute, AllValuesPossible)
{
	int hit[2 * BOUND + 1];
	memset(hit, 0, sizeof(hit));

	for (int i = 0; i < 300; i++) {
		m_minute = RandomMinute_get();
		assertMinuteIsRange();
		hit[m_minute + BOUND]++;
	}

	for (int i = 0; i < 2 * BOUND + 1; i++) {
		CHECK(hit[i] > 0);
	}
}



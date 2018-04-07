#include <stdlib.h>
#include <string.h>
#include <HomeAutomation/RandomMinute.h>
#include "gtest/gtest.h"

enum {
	BOUND = 30,
};

class RandomMinuteTest : public ::testing::Test
{
protected:
	virtual void SetUp()
	{
		RandomMinute_create(BOUND);
		srand(1);
	}
	
	virtual void TearDown()
	{
		RandomMinute_destroy();
	}

	void assertMinuteIsRange()
	{
		if (m_minute < -BOUND || BOUND < m_minute) {
			printf("bad minute value: %d\n", m_minute);
			FAIL() << "minute out of range";
		}
	}

	int m_minute;
};



TEST_F(RandomMinuteTest, GetIsInRange)
{
	for (int i = 0; i < 100; i++) {
		m_minute = RandomMinute_get();
		assertMinuteIsRange();
	}
}

TEST_F(RandomMinuteTest, AllValuesPossible)
{
	int hit[2 * BOUND + 1];
	memset(hit, 0, sizeof(hit));

	for (int i = 0; i < 300; i++) {
		m_minute = RandomMinute_get();
		assertMinuteIsRange();
		hit[m_minute + BOUND]++;
	}

	for (int i = 0; i < 2 * BOUND + 1; i++) {
		EXPECT_TRUE(hit[i] > 0);
	}
}



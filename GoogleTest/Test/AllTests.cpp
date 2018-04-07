#include <stdio.h>
#include "gtest/gtest.h"

TEST(SampleTest, SimpleCheck) {
  EXPECT_EQ(3,  3);
}

int main(int argc, char * argv[])
{
	printf("This is test code.\n");
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

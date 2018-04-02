#include <unity_fixture.h>

TEST_GROUP_RUNNER(sprintf)
{
	RUN_TEST_CASE(sprintf, NoFormatOperations);
	RUN_TEST_CASE(sprintf, InsertString);
}
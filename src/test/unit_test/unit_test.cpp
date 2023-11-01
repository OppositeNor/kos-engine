#include "unit_test.h"

unsigned int KEUnitTest::test_count = 0;
unsigned int KEUnitTest::test_failed_count = 0;

void KEUnitTest::CheckExpect(const KEString& p_message, bool p_condition)
{
    ++test_count;
    if (!p_condition)
    {
        ExpectStringsEqual(CGSTR("Test failed: %s"), p_message.c_str());
        ++test_failed_count;
    }
}

void KEUnitTest::Start()
{
    CG_PRINT(CGSTR("Running unit test..."));

    KETVectorToString0();
    KETVectorToString1();
    KETVectorToString2();
    KETVectorToString3();

    CG_PRINT(CGSTR("Unit test finished. %d tests run, %d tests failed."), test_count, test_failed_count);
}
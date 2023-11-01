#include "unit_test.h"

unsigned int KEUnitTest::test_count = 0;
unsigned int KEUnitTest::test_failed_count = 0;

void KEUnitTest::CheckExpect(bool p_condition, const KEString& p_message, const char* p_file, int p_line)
{
    ++test_count;
    if (!p_condition)
    {
        CG_PRINT(CGSTR("Test failed at file: %hs, line: %d.\nOutput: %s"), p_file, p_line, p_message.c_str());
        ++test_failed_count;
    }
}

void KEUnitTest::Start()
{
    CG_PRINT(CGSTR("Running unit test..."));

    KETVectorConstruct0();
    KETVectorConstruct1();
    KETVectorConstruct2();
    KETVectorConstruct3();

    KETVectorToString0();
    KETVectorToString1();
    KETVectorToString2();
    KETVectorToString3();

    KETVectorCross0();
    KETVectorCross1();
    KETVectorCross2();
    KETVectorCross3();
    KETVectorCross4();

    KETMatrixConstruct0();
    KETMatrixConstruct1();
    KETMatrixConstruct2();
    KETMatrixConstruct3();

    KETMatrixToString0();
    KETMatrixToString1();
    KETMatrixToString2();
    KETMatrixToString3();
    

    if (test_failed_count == 0)
        CG_PRINT(CGSTR("Unit test finished. %d test run, All tests passed."), test_count);
    else
        CG_PRINT(CGSTR("Unit test finished. %d tests run, %d tests failed."), test_count, test_failed_count);
}
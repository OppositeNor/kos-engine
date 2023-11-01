#pragma once

#define CG_MODIFY_OUTPUT_MESSAGE

#undef CG_PRINT
#define CG_PRINT(...) CGPrint(CGSTR("KosEngine"), CGSTR("Output"), __VA_ARGS__)
#undef CG_PRINT_WITH_FUNCTION
#define CG_PRINT_WITH_FUNCTION(...) CGPrintWithFunction(CGSTR("KosEngine"), CGSTR("Output"), __FUNCTION__, __VA_ARGS__)
#undef CG_ERROR
#define CG_ERROR(...) CGError()
#undef CG_WARNING
#define CG_WARNING(...)

#include "kos_engine/defs.hpp"
#include "cos_graphics/log.h"

/**
 * @brief Unit test class.
 * This class is used for unit testing.
 */
class KEUnitTest
{
public:

    /**
     * @brief Start the unit test.
     */
    static void Start();

private:

    /**
     * @brief The number of tests that have been run.
     */
    static unsigned int test_count;
    /**
     * @brief The number of tests that have failed.
     */
    static unsigned int test_failed_count;

    /**
     * @brief Check if the condition is true. If not, fail a test and print out a message.
     * @param p_message The message to print out.
     * @param p_condition The condition of the test.
     */
    static void CheckExpect(const KEString& p_message, bool p_condition);

    template <typename T1, typename T2>
    inline static void ExpectValuesEqual(T1&& val_1, T2&& val_2)
    {
        CheckExpect(CGSTR("Expected to get value: ") + KE_TO_STRING(val_2) + 
            CGSTR(", but get ") + KE_TO_STRING(val_1) + CGSTR(" instead."), val_1 == val_2);
    }
    inline static void ExpectStringsEqual(const KEString& p_str_1, const KEString& p_str_2)
    {
        CheckExpect(CGSTR("Expected to get string: \"") + p_str_2 + 
            CGSTR("\", but get \"") + p_str_1 + CGSTR("\" instead."), p_str_1 == p_str_2);
    }

    /** Vector Test Start **/

    static void KETVectorToString0();
    static void KETVectorToString1();
    static void KETVectorToString2();
    static void KETVectorToString3();

    /** Vector Test End **/
};
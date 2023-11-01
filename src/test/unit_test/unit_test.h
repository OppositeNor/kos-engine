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
#include "cos_graphics/utils.h"
#include <functional>

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
    static void CheckExpect(bool p_condition, const KEString& p_message);

    /**
     * @brief Check if two values are equal.
     * 
     * @tparam T1 Type of value 1.
     * @tparam T2 Type of value 2.
     * @param val_1 Value 1.
     * @param val_2 Value 2.
     */
    template <typename T1, typename T2>
    inline static void ExpectValuesEqual(T1&& val_1, T2&& val_2)
    {
        CheckExpect(val_1 == val_2, CGSTR("Expected to get value: ") + KE_TO_STRING(val_2) + 
            CGSTR(", but get ") + KE_TO_STRING(val_1) + CGSTR(" instead."));
    }
    /**
     * @brief Check if two strings are equal.
     * 
     * @param p_str_1 The first string.
     * @param p_str_2 The second string.
     */
    inline static void ExpectStringsEqual(const KEString& p_str_1, const KEString& p_str_2)
    {
        CheckExpect(p_str_1 == p_str_2, CGSTR("Expected to get string: \"") + p_str_2 + 
            CGSTR("\", but get \"") + p_str_1 + CGSTR("\" instead."));
    }
    /**
     * @brief Test if an expression throws an exception.
     * 
     * @param p_func The expression to test.
     */
    static void ExpectExpressionThrow(const std::function<void()>& p_func)
    {
        bool is_throw = false;
        try
        {
            p_func();
        }
        catch (...)
        {
            return;
        }
        CheckExpect(true, CGSTR("Expected to throw an exception, but not."));
    }
    /**
     * @brief Test if an expression throws an exception with a specific message.
     * 
     * @param p_func The expression to test.
     * @param p_throw_msg The expected message.
     */
    static void ExpectExpressionThrow(const std::function<void()>& p_func, const KEString& p_throw_msg)
    {
        bool is_throw = false;
        try
        {
            p_func();
        }
        catch (const std::exception& e)
        {
            CGChar buff[1024];
            CharToCGChar(e.what(), buff, 1024);
            KEString str = KEString(buff);
            CheckExpect(str == p_throw_msg, CGSTR("Expected to throw an exeption with message: ") + p_throw_msg + 
                CGSTR(", but get \"") + str + CGSTR("\" instead."));
            return;
        }
        catch (...)
        {
            CheckExpect(true, CGSTR("Expected to throw an exeption with message: ") + p_throw_msg + 
                CGSTR(", but get an exception with unknown message instead."));
            return;
        }
        CheckExpect(is_throw, CGSTR("Expected to throw an exception, but not."));
    }

    template <typename T>
    static void ExpectExpressionThrow(const std::function<void()>& p_func)
    {
        bool is_throw = false;
        try
        {
            p_func();
        }
        catch (const T& e)
        {
            return;
        }
        catch (...)
        {
            CGChar buff[1024];
            CharToCGChar(typeid(T).name(), buff, 1024);
            CheckExpect(true, CGSTR("Expected to throw an exeption with type: ") + KEString(buff) + 
                CGSTR(", but get an exception with unknown type instead."));
            return;
        }
        CheckExpect(is_throw, CGSTR("Expected to throw an exception, but not."));
    }

    /** Vector Test Start **/

    static void KETVectorConstruct0();
    static void KETVectorConstruct1();
    static void KETVectorConstruct2();
    static void KETVectorConstruct3();

    static void KETVectorToString0();
    static void KETVectorToString1();
    static void KETVectorToString2();
    static void KETVectorToString3();

    /** Vector Test End **/
};
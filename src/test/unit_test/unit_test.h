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

#define KE_CHECK_EXPECT(p_condition, p_message) KEUnitTest::CheckExpect(p_condition, p_message, __FILE__, __LINE__)
#define KE_EXPECT_VALUES_EQUAL(val_1, val_2) KEUnitTest::ExpectValuesEqual(val_1, val_2, __FILE__, __LINE__)
#define KE_EXPECT_STRINGS_EQUAL(str_1, str_2) KEUnitTest::ExpectStringsEqual(str_1, str_2, __FILE__, __LINE__)
#define KE_EXPECT_EXPRESSION_THROW(p_func) KEUnitTest::ExpectExpressionThrow(p_func, __FILE__, __LINE__)
#define KE_EXPECT_EXPRESSION_THROW_MSG(p_func, p_throw_msg) KEUnitTest::ExpectExpressionThrow(p_func, p_throw_msg, __FILE__, __LINE__)
#define KE_EXPECT_EXPRESSION_THROW_TYPE(p_func, p_type) KEUnitTest::ExpectExpressionThrow<p_type>(p_func, __FILE__, __LINE__)

KE_DECL_HAS_METHOD(operator KEString(), ke_has_to_string)

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
    static void CheckExpect(bool p_condition, const KEString& p_message, const char* p_file, int p_line);

    /**
     * @brief Check if two values are equal.
     * 
     * @tparam T1 Type of value 1.
     * @tparam T2 Type of value 2.
     * @param val_1 Value 1.
     * @param val_2 Value 2.
     */
    template <typename T1, typename T2>
    KE_FORCE_INLINE static auto ExpectValuesEqual(T1&& val_1, T2&& val_2, const char* p_file, int p_line)
        ->decltype((void)(val_1 == val_2), (void)((KEString)val_1), void())
    {
        CheckExpect(val_1 == val_2, CGSTR("Expected to get value: ") + (KEString)(val_2) + 
            CGSTR(", but get ") + (KEString)(val_1) + CGSTR(" instead."), p_file, p_line);
    }

    /**
     * @brief Check if two values are equal.
     * 
     * @tparam T1 Type of value 1.
     * @tparam T2 Type of value 2.
     * @param val_1 Value 1.
     * @param val_2 Value 2.
     */
    template <typename T1, typename T2>
    KE_FORCE_INLINE static auto ExpectValuesEqual(T1&& val_1, T2&& val_2, const char* p_file, int p_line)
        ->decltype((void)(val_1 == val_2), (void)(KE_TO_STRING(val_1)), void())
    {
        CheckExpect(val_1 == val_2, CGSTR("Expected to get value: ") + KE_TO_STRING(val_2) + 
            CGSTR(", but get ") + KE_TO_STRING(val_1) + CGSTR(" instead."), p_file, p_line);
    }
    
    /**
     * @brief This function is called when the two values are not comparable or a KEString operator is missing.
     * 
     * @param ... 
     */
    KE_FORCE_INLINE static void ExpectValuesEqual(...)
    {
        CG_PRINT(CGSTR("Warning: The value is not comparable or missing a KEString operator."));
    }

    /**
     * @brief Check if two strings are equal.
     * 
     * @param p_str_1 The first string.
     * @param p_str_2 The second string.
     */
    KE_FORCE_INLINE static void ExpectStringsEqual(const KEString& p_str_1, const KEString& p_str_2, const char* p_file, int p_line)
    {
        CheckExpect(p_str_1 == p_str_2, CGSTR("Expected to get string: \"") + p_str_2 + 
            CGSTR("\", but get \"") + p_str_1 + CGSTR("\" instead."), p_file, p_line);
    }
    /**
     * @brief Test if an expression throws an exception.
     * 
     * @param p_func The expression to test.
     */
    static void ExpectExpressionThrow(const std::function<void()>& p_func, const char* p_file, int p_line)
    {
        bool is_throw = false;
        try
        {
            p_func();
        }
        catch (...)
        {
            CheckExpect(true, CGSTR("Passes."), p_file, p_line);
            return;
        }
        CheckExpect(true, CGSTR("Expected to throw an exception, but not."), p_file, p_line);
    }
    /**
     * @brief Test if an expression throws an exception with a specific message.
     * 
     * @param p_func The expression to test.
     * @param p_throw_msg The expected message.
     */
    static void ExpectExpressionThrow(const std::function<void()>& p_func, const KEString& p_throw_msg, const char* p_file, int p_line)
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
                CGSTR(", but get \"") + str + CGSTR("\" instead."), p_file, p_line);
            return;
        }
        catch (...)
        {
            CheckExpect(false, CGSTR("Expected to throw an exeption with message: ") + p_throw_msg + 
                CGSTR(", but get an exception with unknown message instead."), p_file, p_line);
            return;
        }
        CheckExpect(is_throw, CGSTR("Expected to throw an exception, but not."), p_file, p_line);
    }

    template <typename T>
    static void ExpectExpressionThrow(const std::function<void()>& p_func, const char* p_file, int p_line)
    {
        bool is_throw = false;
        try
        {
            p_func();
        }
        catch (const T& e)
        {
            CheckExpect(true, CGSTR("Passes."), p_file, p_line);
            return;
        }
        catch (...)
        {
            CGChar buff[1024];
            CharToCGChar(typeid(T).name(), buff, 1024);
            CheckExpect(false, CGSTR("Expected to throw an exeption with type: ") + KEString(buff) + 
                CGSTR(", but get an exception with other type instead."), p_file, p_line);
            return;
        }
        CheckExpect(is_throw, CGSTR("Expected to throw an exception, but not."), p_file, p_line);
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
    static void KETVectorCross0();
    static void KETVectorCross1();
    static void KETVectorCross2();
    static void KETVectorCross3();
    static void KETVectorCross4();

    /** Vector Test End **/

    /** Matrix Test Start **/

    static void KETMatrixConstruct0();
    static void KETMatrixConstruct1();
    static void KETMatrixConstruct2();
    static void KETMatrixConstruct3();
    static void KETMatrixToString0();
    static void KETMatrixToString1();
    static void KETMatrixToString2();
    static void KETMatrixToString3();
    static void KETMatrixAdd0();
    static void KETMatrixAdd1();
    static void KETMatrixAdd2();
    static void KETMatrixAdd3();
    static void KETMatrixSub0();
    static void KETMatrixSub1();
    static void KETMatrixSub2();
    static void KETMatrixSub3();
    static void KETMatrixMul0();
    static void KETMatrixMul1();
    static void KETMatrixMul2();
    static void KETMatrixMul3();
    static void KETMatrixMul4();
    static void KETMatrixMul5();
    static void KETMatrixMul6();
    static void KETMatrixMul7();

    /** Matrix Test End **/

    /** Shape Test Start **/
    static void KETShapeCircleConstruct0();
    static void KETShapeCircleConstruct1();
    static void KETShapeCircleConstruct2();
    static void KETShapeCircleConstruct3();
    static void KETShapeRect0();
    static void KETShapeRect1();
    static void KETShapeRect2();
    static void KETShapeRect3();
    
    /** Shape Test End **/
};
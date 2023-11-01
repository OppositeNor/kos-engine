#include "kos_engine/math/vector.hpp"
#include "../unit_test.h"

void KEUnitTest::KETVectorConstruct0()
{
    KEVector<2> v = {0.0f, 0.0f};
    ExpectValuesEqual(v.x, 0.0f);
    ExpectValuesEqual(v.y, 0.0f);
}

void KEUnitTest::KETVectorConstruct1()
{
    KEVector<0> v = {};
    ExpectValuesEqual(v.DIM, 0);
}

void KEUnitTest::KETVectorConstruct2()
{
    ExpectExpressionThrow<std::invalid_argument>([]()
    {
        KEVector<2> v = {0.0f, 0.0f, 0.0f};
    });
}

void KEUnitTest::KETVectorConstruct3()
{
    KEVector<2> v = {0.0f, 0.0f};
    ExpectValuesEqual(v.x, 0.0f);
    ExpectValuesEqual(v.y, 0.0f);
}

void KEUnitTest::KETVectorToString0()
{
    KEVector<2> v = {0.0f, 0.0f};
    ExpectStringsEqual((KEString)v, CGSTR("KEVector<2>(0.000000, 0.000000)"));
}
void KEUnitTest::KETVectorToString1()
{
    KEVector<5> v = {1.0f, 0.5f, 0.33f, 0.25f, 0.2f};
    ExpectStringsEqual((KEString)v, CGSTR("KEVector<5>(1.000000, 0.500000, 0.330000, 0.250000, 0.200000)"));
}
void KEUnitTest::KETVectorToString2()
{
    KEVector<1> v = {3.0f};
    ExpectStringsEqual((KEString)v, CGSTR("KEVector<1>(3.000000)"));
}
void KEUnitTest::KETVectorToString3()
{
    KEVector<0> v = {};
    ExpectStringsEqual((KEString)v, CGSTR("KEVector<0>()"));
}

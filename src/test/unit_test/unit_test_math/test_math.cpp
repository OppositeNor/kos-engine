#include "kos_engine/math/vector.hpp"
#include "../unit_test.h"
#include "kos_engine/math/matrix.hpp"

void KEUnitTest::KETVectorConstruct0()
{
    KEVector<2> v = {0.0f, 0.0f};
    KE_EXPECT_VALUES_EQUAL(v.x, 0.0f);
    KE_EXPECT_VALUES_EQUAL(v.y, 0.0f);
    KE_EXPECT_VALUES_EQUAL(v.DIM, 2);
}

void KEUnitTest::KETVectorConstruct1()
{
    KEVector<0> v = {};
    KE_EXPECT_VALUES_EQUAL(v.DIM, 0);
}

void KEUnitTest::KETVectorConstruct2()
{
    KE_EXPECT_EXPRESSION_THROW_TYPE(([](){KEVector<2> v = {0.0f, 0.0f, 0.0f};}), std::invalid_argument);
}

void KEUnitTest::KETVectorConstruct3()
{
    KEVector<4> v = {0.0f, 1.0f, 0.02f, 3.0f};
    KE_EXPECT_VALUES_EQUAL(v, KEVector<4>({0.0f, 1.0f, 0.02f, 3.0f}));
}

void KEUnitTest::KETVectorToString0()
{
    KEVector<2> v = {0.0f, 0.0f};
    KE_EXPECT_STRINGS_EQUAL((KEString)v, CGSTR("KEVector<2>(0.000000, 0.000000)"));
}
void KEUnitTest::KETVectorToString1()
{
    KEVector<5> v = {1.0f, 0.5f, 0.33f, 0.25f, 0.2f};
    KE_EXPECT_STRINGS_EQUAL((KEString)v, CGSTR("KEVector<5>(1.000000, 0.500000, 0.330000, 0.250000, 0.200000)"));
}
void KEUnitTest::KETVectorToString2()
{
    KEVector<1> v = {3.0f};
    KE_EXPECT_STRINGS_EQUAL((KEString)v, CGSTR("KEVector<1>(3.000000)"));
}
void KEUnitTest::KETVectorToString3()
{
    KEVector<0> v = {};
    KE_EXPECT_STRINGS_EQUAL((KEString)v, CGSTR("KEVector<0>()"));
}

void KEUnitTest::KETVectorCross0()
{
    KEVector<3> v1 = {0.0f, 0.0f, 0.0f};
    KEVector<3> v2 = {0.0f, 0.0f, 0.0f};
    KE_EXPECT_VALUES_EQUAL(KECross(v1, v2), KEVector<3>({0.0f, 0.0f, 0.0f}));
}

void KEUnitTest::KETVectorCross1()
{
    KEVector<3> v1 = {1.0f, 0.0f, 0.0f};
    KEVector<3> v2 = {0.0f, 0.0f, 1.0f};
    KE_EXPECT_VALUES_EQUAL(KECross(v1, v2), KEVector<3>({0.0f, 1.0f, 0.0f}));
}

void KEUnitTest::KETVectorCross2()
{
    KEVector<3> v1 = {1.0f, 0.0f, 0.0f};
    KEVector<3> v2 = {0.0f, 1.0f, 0.0f};
    KE_EXPECT_VALUES_EQUAL(KECross(v1, v2), KEVector<3>({0.0f, 0.0f, -1.0f}));
}

void KEUnitTest::KETVectorCross3()
{
    KEVector<2> v1 = {1.0f, 0.0f};
    KEVector<2> v2 = {0.0f, 1.0f};
    KE_EXPECT_VALUES_EQUAL(KECross(v1, v2), -1.0f);
}

void KEUnitTest::KETVectorCross4()
{
    KEVector<2> v1 = {1.0f, 0.0f};
    KEVector<2> v2 = {0.0f, 0.0f};
    KE_EXPECT_VALUES_EQUAL(KECross(v1, v2), 0.0f);
}

void KEUnitTest::KETMatrixConstruct0()
{
    KEMatrix<3> mat = {{1.0f, 0.0f, 0.0f}, 
                       {0.0f, 1.0f, 0.0f}, 
                       {0.0f, 0.0f, 1.0f}};
    KE_EXPECT_VALUES_EQUAL(KEMatrix<3>(
        {{1.0f, 0.0f, 0.0f}, 
         {0.0f, 1.0f, 0.0f}, 
         {0.0f, 0.0f, 1.0f}}), mat);
}

void KEUnitTest::KETMatrixConstruct1()
{
    KEMatrix<0> mat = {};
    KE_EXPECT_VALUES_EQUAL(mat.DIM, 0);
}

void KEUnitTest::KETMatrixConstruct2()
{
    KEMatrix<2> mat = {1.0f, 2.0f,
                       3.0f, 4.0f};
    KE_EXPECT_VALUES_EQUAL(mat[0][0], 1.0f);
    KE_EXPECT_VALUES_EQUAL(mat[0][1], 2.0f);
    KE_EXPECT_VALUES_EQUAL(mat[1][0], 3.0f);
    KE_EXPECT_VALUES_EQUAL(mat[1][1], 4.0f);
    KE_EXPECT_VALUES_EQUAL(mat.DIM, 2);
}

void KEUnitTest::KETMatrixConstruct3()
{
    KE_EXPECT_EXPRESSION_THROW_TYPE(([](){
        KEMatrix<2> mat = {{1.0f, 2.0f},
                    {3.0f, 4.0f},
                    {1.0f, 3.0f}};
    }), std::invalid_argument);
}

void KEUnitTest::KETMatrixToString0()
{
    KEMatrix<3> mat = {{1.0f, 0.0f, 0.0f}, 
                       {0.0f, 1.0f, 0.0f}, 
                       {0.0f, 0.0f, 1.0f}};
    KE_EXPECT_STRINGS_EQUAL((KEString)mat, 
        CGSTR("KEMatrix<3>({1.000000, 0.000000, 0.000000}{0.000000, 1.000000, 0.000000}{0.000000, 0.000000, 1.000000})"));
}
void KEUnitTest::KETMatrixToString1()
{
    KEMatrix<0> mat = {};
    KE_EXPECT_STRINGS_EQUAL((KEString)mat, CGSTR("KEMatrix<0>()"));

}
void KEUnitTest::KETMatrixToString2()
{
    KEMatrix<2> mat = {{1.0f, 2.0f}, {3.0f, 4.0f}};
    KE_EXPECT_STRINGS_EQUAL((KEString)mat, CGSTR("KEMatrix<2>({1.000000, 2.000000}{3.000000, 4.000000})"));
}
void KEUnitTest::KETMatrixToString3()
{
    KEMatrix<1> mat = {1.0f};
    KE_EXPECT_STRINGS_EQUAL((KEString)mat, CGSTR("KEMatrix<1>({1.000000})"));
}
void KEUnitTest::KETMatrixAdd0()
{
    KEMatrix<2> mat1 = {{1.0f, 2.0f}, {3.0f, 4.0f}};
    KEMatrix<2> mat2 = {{5.0f, 6.0f}, {7.0f, 8.0f}};
    KE_EXPECT_VALUES_EQUAL(mat1 + mat2, KEMatrix<2>({{6.0f, 8.0f}, {10.0f, 12.0f}}));
}
void KEUnitTest::KETMatrixAdd1()
{
    KEMatrix<1> mat1 = {1.0f};
    KEMatrix<1> mat2 = {2.0f};
    KE_EXPECT_VALUES_EQUAL(mat1 + mat2, KEMatrix<1>({3.0f}));
}
void KEUnitTest::KETMatrixAdd2()
{
    KEMatrix<0> mat1 = {};
    KEMatrix<0> mat2 = {};
    KE_EXPECT_VALUES_EQUAL(mat1 + mat2, KEMatrix<0>());
}
void KEUnitTest::KETMatrixAdd3()
{
    KEMatrix<3> mat1 = {{1.0f, 2.0f, 3.0f}, 
                        {4.0f, 5.0f, 6.0f}, 
                        {7.0f, 8.0f, 9.0f}};
    KEMatrix<3> mat2 = {{10.0f, 13.0f, 16.0f}, 
                        {11.0f, 14.0f, 17.0f}, 
                        {12.0f, 15.0f, 18.0f}};
    KEMatrix<3> mat3 = {{1.0f, 0.0f, 0.0f}, 
                        {0.0f, 1.0f, 0.0f}, 
                        {0.0f, 0.0f, 1.0f}};
    KE_EXPECT_VALUES_EQUAL(mat1 + mat2 + mat3, 
        KEMatrix<3>({12.0f, 15.0f, 19.0f,
                    15.0f, 20.0f, 23.0f,
                    19.0f, 23.0f, 28.0f}));
}

void KEUnitTest::KETMatrixSub0()
{
    KEMatrix<2> mat1 = {{1.0f, 2.0f}, {3.0f, 4.0f}};
    KEMatrix<2> mat2 = {{5.0f, 6.0f}, {7.0f, 8.0f}};
    KE_EXPECT_VALUES_EQUAL(mat1 - mat2, KEMatrix<2>({{-4.0f, -4.0f}, {-4.0f, -4.0f}}));
}
void KEUnitTest::KETMatrixSub1()
{
    KEMatrix<0> mat1 = {};
    KEMatrix<0> mat2 = {};
    KE_EXPECT_VALUES_EQUAL(mat1 - mat2, KEMatrix<0>());
}
void KEUnitTest::KETMatrixSub2()
{
    KEMatrix<3> mat1 = {{10.0f, 13.0f, 16.0f}, 
                        {11.0f, 14.0f, 17.0f}, 
                        {12.0f, 15.0f, 18.0f}};
    KEMatrix<3> mat2 = {{1.0f, 2.0f, 3.0f}, 
                        {4.0f, 5.0f, 6.0f}, 
                        {7.0f, 8.0f, 9.0f}};
    KEMatrix<3> mat3 = {{1.0f, 0.0f, 0.0f}, 
                        {0.0f, 1.0f, 0.0f}, 
                        {0.0f, 0.0f, 1.0f}};
    KE_EXPECT_VALUES_EQUAL(mat1 - mat2 - mat3, 
        KEMatrix<3>({8.0f, 11.0f, 13.0f,
                    7.0f, 8.0f, 11.0f,
                    5.0f, 7.0f, 8.0f}));
}
void KEUnitTest::KETMatrixSub3()
{
    KEMatrix<1> mat1 = {1.0f};
    KEMatrix<1> mat2 = {2.0f};
    KE_EXPECT_VALUES_EQUAL(mat1 - mat2, KEMatrix<1>({-1.0f}));
    KE_EXPECT_VALUES_EQUAL(mat1 -= mat2, KEMatrix<1>({-1.0f}));
    KE_EXPECT_VALUES_EQUAL(mat1, KEMatrix<1>({-1.0f}));
}

void KEUnitTest::KETMatrixMul0()
{
    KEMatrix<2> mat1 = {{1.0f, 2.0f}, {3.0f, 4.0f}};
    KEMatrix<2> mat2 = {{5.0f, 6.0f}, {7.0f, 8.0f}};
    KE_EXPECT_VALUES_EQUAL(mat1 * mat2, KEMatrix<2>({{19.0f, 22.0f}, {43.0f, 50.0f}}));
    KE_EXPECT_VALUES_EQUAL(mat1 *= mat2, KEMatrix<2>({{19.0f, 22.0f}, {43.0f, 50.0f}}));
    KE_EXPECT_VALUES_EQUAL(mat1, KEMatrix<2>({{19.0f, 22.0f}, {43.0f, 50.0f}}));
}

void KEUnitTest::KETMatrixMul1()
{
    KEMatrix<2> mat1 = {{1.0f, 2.0f}, {3.0f, 4.0f}};
    KEMatrix<2> mati = {{1.0f, 0.0f}, {0.0f, 1.0f}};
    KE_EXPECT_VALUES_EQUAL(mat1 * mati, mat1);
}
void KEUnitTest::KETMatrixMul2()
{
    KEMatrix<2> mat1 = {{1.0f, 2.0f}, {3.0f, 4.0f}};
    KEMatrix<2> mat0 = {{0.0f, 0.0f}, {0.0f, 0.0f}};
    KE_EXPECT_VALUES_EQUAL(mat1 * mat0, mat0);
}
void KEUnitTest::KETMatrixMul3()
{
    KEMatrix<0> mat1 = {};
    KEMatrix<0> mat2 = {};
    KE_EXPECT_VALUES_EQUAL(mat1 * mat2, KEMatrix<0>());
}

void KEUnitTest::KETMatrixMul4()
{
    KEMatrix<2> mat1 = {{1.0f, 2.0f}, {3.0f, 4.0f}};
    KEVector<2> vec1 = {1.0f, 2.0f};
    KE_EXPECT_VALUES_EQUAL(mat1 * vec1, KEVector<2>({5.0f, 11.0f}));
}
void KEUnitTest::KETMatrixMul5()
{
    KEMatrix<3> mat1 = {{1.0f, 2.0f, 3.0f}, {3.0f, 4.0f, 2.0f}, {0.0f, 0.0f, 1.0f}};
    KEVector<2> vec1 = {1.0f, 2.0f};
    KE_EXPECT_VALUES_EQUAL(mat1 * vec1, KEVector<2>({8.0f, 13.0}));
}
void KEUnitTest::KETMatrixMul6()
{
    KEMatrix<3> mat1 = {{1.0f, 2.0f, 3.0f}, {3.0f, 4.0f, 2.0f}, {0.0f, 0.0f, 1.0f}};
    KE_EXPECT_VALUES_EQUAL(mat1 * 5, KEMatrix<3>({{5.0f, 10.0f, 15.0f}, {15.0f, 20.0f, 10.0f}, {0.0f, 0.0f, 5.0f}}));
    KE_EXPECT_VALUES_EQUAL(mat1 *= 5, KEMatrix<3>({{5.0f, 10.0f, 15.0f}, {15.0f, 20.0f, 10.0f}, {0.0f, 0.0f, 5.0f}}));
    KE_EXPECT_VALUES_EQUAL(mat1, KEMatrix<3>({{5.0f, 10.0f, 15.0f}, {15.0f, 20.0f, 10.0f}, {0.0f, 0.0f, 5.0f}}));
}
void KEUnitTest::KETMatrixMul7()
{
    KEMatrix<0> mat1 = {};
    KE_EXPECT_VALUES_EQUAL(mat1 * 5, KEMatrix<0>());
}
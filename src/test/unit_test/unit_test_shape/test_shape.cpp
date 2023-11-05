#include "../unit_test.h"
#include "kos_engine/component/shape/shape_circle.h"
void KEUnitTest::KETShapeCircleConstruct0()
{
    KEShapeCircle circle(1.0f);
    KE_EXPECT_VALUES_EQUAL(circle.GetRadius(), 1.0f);
}
void KEUnitTest::KETShapeCircleConstruct1()
{
    KEShapeCircle circle;
    KE_EXPECT_VALUES_EQUAL(circle.GetRadius(), 1.0f);
}
void KEUnitTest::KETShapeCircleConstruct2()
{
    KEShapeCircle circle(0.0f);
    KE_EXPECT_VALUES_EQUAL(circle.GetRadius(), 0.0f);
}
void KEUnitTest::KETShapeCircleConstruct3()
{
    KEShapeCircle circle(-3.0f);
    KE_EXPECT_VALUES_EQUAL(circle.GetRadius(), 3.0f);
}
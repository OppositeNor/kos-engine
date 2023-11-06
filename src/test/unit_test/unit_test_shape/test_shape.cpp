#include "../unit_test.h"
#include "kos_engine/component/shape/shape_circle.h"
#include "kos_engine/component/shape/shape_rect.h"
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

void KEUnitTest::KETShapeRectConstruct0()
{
    KEShapeRect rect(1.0f, 1.0f);
    KE_EXPECT_VALUES_EQUAL(rect.GetWidth(), 1.0f);
    KE_EXPECT_VALUES_EQUAL(rect.GetHeight(), 1.0f);
    KE_EXPECT_VALUES_EQUAL(rect.GetTopY(), 0.5f);
    KE_EXPECT_VALUES_EQUAL(rect.GetBottomY(), -0.5f);
    KE_EXPECT_VALUES_EQUAL(rect.GetLeftX(), -0.5f);
    KE_EXPECT_VALUES_EQUAL(rect.GetRightX(), 0.5f);
}
void KEUnitTest::KETShapeRectConstruct1()
{
    KEShapeRect rect;
    KE_EXPECT_VALUES_EQUAL(rect.GetWidth(), 1.0f);
    KE_EXPECT_VALUES_EQUAL(rect.GetHeight(), 1.0f);
    KE_EXPECT_VALUES_EQUAL(rect.GetTopY(), 0.5f);
    KE_EXPECT_VALUES_EQUAL(rect.GetBottomY(), -0.5f);
    KE_EXPECT_VALUES_EQUAL(rect.GetLeftX(), -0.5f);
    KE_EXPECT_VALUES_EQUAL(rect.GetRightX(), 0.5f);
}
void KEUnitTest::KETShapeRectConstruct2()
{
    KEShapeRect rect(3.0f, 4.0f);
    KE_EXPECT_VALUES_EQUAL(rect.GetWidth(), 3.0f);
    KE_EXPECT_VALUES_EQUAL(rect.GetHeight(), 4.0f);
    KE_EXPECT_VALUES_EQUAL(rect.GetTopY(), 2.0f);
    KE_EXPECT_VALUES_EQUAL(rect.GetBottomY(), -2.0f);
    KE_EXPECT_VALUES_EQUAL(rect.GetLeftX(), -1.5f);
    KE_EXPECT_VALUES_EQUAL(rect.GetRightX(), 1.5f);
}
void KEUnitTest::KETShapeRectConstruct3()
{
    KEShapeRect rect(-3.0f, -4.0f);
    KE_EXPECT_VALUES_EQUAL(rect.GetWidth(), 3.0f);
    KE_EXPECT_VALUES_EQUAL(rect.GetHeight(), 4.0f);
    KE_EXPECT_VALUES_EQUAL(rect.GetTopY(), 2.0f);
    KE_EXPECT_VALUES_EQUAL(rect.GetBottomY(), -2.0f);
    KE_EXPECT_VALUES_EQUAL(rect.GetLeftX(), -1.5f);
    KE_EXPECT_VALUES_EQUAL(rect.GetRightX(), 1.5f);
}
#include "kos_engine/component/shape/shape_circle.h"

float KEShapeCircle::GetCircumference() const
{
    return radius * 2 * KE_PI;
}

float KEShapeCircle::GetArea() const
{
    return radius * radius * KE_PI;
}

float KEShapeCircle::GetTopY() const
{
    return GetTransform().position.y + radius;
}

float KEShapeCircle::GetBottomY() const
{
    return GetTransform().position.y - radius;
}

float KEShapeCircle::GetLeftX() const
{
    return GetTransform().position.x - radius;
}

float KEShapeCircle::GetRightX() const
{
    return GetTransform().position.x + radius;
}
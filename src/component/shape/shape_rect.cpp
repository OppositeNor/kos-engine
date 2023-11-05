#include "kos_engine/component/shape/shape_rect.h"

float KEShapeRect::GetTopY() const
{
    return GetTransform().position.x + height / 2;
}

float KEShapeRect::GetBottomY() const
{
    return GetTransform().position.x - height / 2;
}

float KEShapeRect::GetLeftX() const
{
    return GetTransform().position.y - width / 2;
}

float KEShapeRect::GetRightX() const
{
    return GetTransform().position.y + width / 2;
}
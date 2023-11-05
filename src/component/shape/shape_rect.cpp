#include "kos_engine/component/shape/shape_rect.h"
#include "kos_engine/game.h"

#include "cos_graphics/graphics.h"

KEShapeRect::KEShapeRect(float width, float height)
        : width(width), height(height), 
        quadrangle_instance(
            CGCreateQuadrangle((CGVector2){GetLeftX(), GetTopY()},
                           (CGVector2){GetRightX(), GetTopY()},
                           (CGVector2){GetRightX(), GetBottomY()},
                           (CGVector2){GetLeftX(), GetBottomY()}, CG_FALSE), CGFree)
{}

void KEShapeRect::SetWidth(float p_width)
{
    width = p_width;
    need_update = true;
}

void KEShapeRect::SetHeight(float p_height)
{
    height = p_height;
    need_update = true;
}

void KEShapeRect::UpdateQuadrangle()
{
    quadrangle_instance.get()->vert_1 = (CGVector2){GetLeftX(), GetTopY()};
    quadrangle_instance.get()->vert_2 = (CGVector2){GetRightX(), GetTopY()};
    quadrangle_instance.get()->vert_3 = (CGVector2){GetRightX(), GetBottomY()};
    quadrangle_instance.get()->vert_4 = (CGVector2){GetLeftX(), GetBottomY()};

    need_update = false;
}

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

void KEShapeRect::Draw(float p_delta)
{
    UpdateQuadrangle();
    CGDrawQuadrangle(quadrangle_instance.get(), GetRenderProperty(), KEGame::GetInstance()->GetGameWindow());
}
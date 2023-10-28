#include "kos_engine/component/texture_container.h"
#include "kos_engine/utils.hpp"

#define CGBoarderFunc(Direction, AXIS, axis, comp)                          \
float KETextureContainer::GetBoarder##Direction##AXIS() noexcept            \
{                                                                           \
    auto& children = GetChildren();                                         \
    CGVector2 result = CGVec2(0.0f, 0.0f);                                  \
    if (texture == nullptr)                                                 \
    {                                                                       \
        if (children.empty())                                               \
            return GetGlobalPosition().axis;                                \
        result.axis = GetGlobalPosition().axis;                             \
    }                                                                       \
    else                                                                    \
    {                                                                       \
        result.axis = Get##Direction##AXIS();                               \
        result = GetGlobalTransformMatrix() * result;                       \
        if (children.empty())                                               \
            return result.axis;                                             \
    }                                                                       \
    for (auto& child : children)                                            \
    {                                                                       \
        float child_direct_axis = child->GetBoarder##Direction##AXIS();     \
        if (child_direct_axis comp result.axis)                             \
            result.axis = child_direct_axis;                                \
    }                                                                       \
    return result.axis;                                                     \
}


KETextureContainer::~KETextureContainer()
{
    if (texture != nullptr)
        CGFree(texture);
}


float KETextureContainer::GetBoarderWidth() noexcept
{
    if (texture == nullptr)
        return 0;
    return GetBoarderRightX() - GetBoarderLeftX();
}

float KETextureContainer::GetBoarderHeight() noexcept
{
    if (texture == nullptr)
        return 0;
    return GetBoarderTopY() - GetBoarderBottomY();
}

CGBoarderFunc(Top, Y, y, >)
CGBoarderFunc(Bottom, Y, y, <)
CGBoarderFunc(Left, X, x, <)
CGBoarderFunc(Right, X, x, >)

KETextureContainer::KETextureContainer(const KETextureContainer& p_other) : KEVisualComponent(p_other)
{
    texture = CGCopyVisualImage(p_other.texture);
}

KETextureContainer::KETextureContainer(KETextureContainer&& p_other) noexcept : KEVisualComponent(std::move(p_other))
{
    texture = p_other.texture;
    p_other.texture = nullptr;
}

float KETextureContainer::GetWidth() const noexcept
{
    return texture->img_width * GetTransform().scale.x;
}

float KETextureContainer::GetHeight() const noexcept
{
    return texture->img_height * GetTransform().scale.y;
}

float KETextureContainer::GetTopY() const noexcept
{
    return (float)texture->img_height / 2.0f;
}

float KETextureContainer::GetBottomY() const noexcept
{
    return -1 * (float)texture->img_height / 2.0f;
}

float KETextureContainer::GetLeftX() const noexcept 
{
    return -1 * (float)texture->img_width / 2.0f;
}

float KETextureContainer::GetRightX() const noexcept
{
    return (float)texture->img_width / 2.0f;
}
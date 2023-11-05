#include "kos_engine/component/component.h"
#include "kos_engine/game.h"
#include "kos_engine/utils.hpp"

#include "cos_graphics/log.h"
#include <cmath>

KEComponent::KETransform::KETransform(const KEVector2& p_position, float p_rotation, const KEVector2& p_scale)
    : position(p_position), rotation(p_rotation), scale(p_scale)
{
    
}

KEMat3::KEMat3 KEComponent::KETransform::GetTransformMatrix() const noexcept
{
    return KEMat3::GetPositionMatrix(position) * KEMat3::GetRotationMatrix(rotation) * KEMat3::GetScaleMatrix(scale);
}

KEMat3::KEMat3 KEComponent::KETransform::GetInvTransformMatrix() const noexcept
{
    return KEMat3::GetScaleMatrix(
        KEVector2(KEUtils::GetReciprocal(scale.x), KEUtils::GetReciprocal(scale.y))) 
        * KEMat3::GetInvRoationMatrix(rotation)
        * KEMat3::GetPositionMatrix(position * -1.0f);
}

void KEComponent::OnEnter()
{
    if (activated)
        return;
    for (auto& child : children)
    {
        child->OnEnter();
    }
    activated = true;
    Ready();
}

void KEComponent::QueueFree()
{
    is_queue_freed = true;
}

void KEComponent::ShouldUpdateMatrix()
{
    should_update_global_matrix = true;
    should_update_inv_global_matrix = true;
    for (auto child : children)
    {
        if (!child->should_update_global_matrix || !child->should_update_inv_global_matrix)
            child->ShouldUpdateMatrix();
    }
}

KEComponent::KETransform& KEComponent::GetTransform() noexcept 
{
    ShouldUpdateMatrix();
    return transform;
}

KEComponent::KEComponent()
{
    KEGame::GetInstance()->AddComponent(this);
}

KEComponent::KEComponent(const KEComponent& other) : KEComponent()
{
    transform = other.transform;
}

KEComponent::KEComponent(KEComponent&& other) noexcept : KEComponent()
{
    transform = other.transform;
    parent = other.parent;
    other.parent = nullptr;
    children = std::move(other.children);
}

KEComponent::~KEComponent()
{
    for (auto& child : children)
    {
        DetachChild(child);
    }
    if (parent != nullptr)
        parent->DetachChild(this);
    KEGame::GetInstance()->RemoveComponent(this);
}

#define CGBoarderFunc(Direction, AXIS, axis, comp)                          \
float KEComponent::GetBoarder##Direction##AXIS() noexcept                   \
{                                                                           \
    if (children.empty())                                                   \
        return GetGlobalPosition().y;                                       \
    float result = GetGlobalPosition().y;                                   \
    for (auto& child : children)                                            \
    {                                                                       \
        float child_direct_axis = child->GetBoarder##Direction##AXIS();     \
        if (child_direct_axis comp result)                                  \
            result = child_direct_axis;                                     \
    }                                                                       \
    return result;                                                          \
}

bool KEComponent::IsVisible() const noexcept
{
    if (!visible || !locally_visible)
        return false;
    if (GetParent() == nullptr)
        return true;
    return GetParent()->IsVisible();
}

bool KEComponent::GetVisible() const noexcept
{
    return visible && locally_visible;
}

CGBoarderFunc(Top, Y, y, >)
CGBoarderFunc(Bottom, Y, y, <)
CGBoarderFunc(Left, X, x, <)
CGBoarderFunc(Right, X, x, >)

void KEComponent::Tick(double p_delta_time)
{
    Update(p_delta_time);
}

KEVector2 KEComponent::GetGlobalPosition() const
{
    if (parent == nullptr)
        return GetTransform().position;
    return parent->GetGlobalTransformMatrix() * GetTransform().position;
}

KEMat3::KEMat3 KEComponent::GetGlobalTransformMatrix() noexcept
{
    if (parent == nullptr)
        return GetTransform().GetTransformMatrix();
    if (should_update_global_matrix)
    {
        global_transform_matrix = parent->GetGlobalTransformMatrix() * GetTransform().GetTransformMatrix();
        should_update_global_matrix = false;
    }
    return global_transform_matrix;
}

KEMat3::KEMat3 KEComponent::GetInvGlobalTransformMatrix() noexcept
{
    if (parent == nullptr)
        return GetTransform().GetInvTransformMatrix();
    if (should_update_inv_global_matrix)
    {
        inv_global_transform_matrix = parent->GetInvGlobalTransformMatrix() * GetTransform().GetInvTransformMatrix();
        should_update_inv_global_matrix = false;
    }
    return inv_global_transform_matrix;
}

KEVector2 KEComponent::ToRelativePosition(const KEVector2& global_position) const
{
    if (parent == nullptr)
        return global_position;
    return parent->GetInvGlobalTransformMatrix() * GetTransform().GetInvTransformMatrix() * global_position;
}

KEVector2 KEComponent::ToGlobalPosition(const KEVector2& relative_position) const
{
    if (parent == nullptr)
        return relative_position;
    return parent->GetGlobalTransformMatrix() * relative_position;
}

void KEComponent::SetGlobalPosition(const KEVector2& global_position)
{
    if (parent == nullptr)
        GetTransform().position = global_position;
    else
        GetTransform().position = parent->GetInvGlobalTransformMatrix() * global_position;
}

void KEComponent::SetDepth(float p_depth)
{
    GetTransform().depth = p_depth;
}

void KEComponent::AddChild(KEComponent* p_child)
{
    if (p_child == nullptr)
    {
        CG_WARNING(CGSTR("Trying to add a null child to a component."));
        return;
    }
    for (auto& child : children)
    {
        if (child == p_child)
        {
            CG_WARNING(CGSTR("Trying to add a child that already exists."));
            return;
        }
    }
    children.push_back(p_child);
    if (activated)
        p_child->OnEnter();
    p_child->parent = this;
}

void KEComponent::SetParent(KEComponent* p_parent)
{
    if (p_parent == nullptr)
    {
        CG_WARNING(CGSTR("Trying to set a null parent to a component."));
        return;
    }
    if (parent != nullptr)
        parent->DetachChild(this);
    p_parent->AddChild(this);
    if (p_parent->activated)
        OnEnter();
}

void KEComponent::DetachChild(KEComponent* p_child)
{
    if (p_child == nullptr)
    {
        CG_WARNING(CGSTR("Trying to detach a null child from a component."));
        return;
    }
    for (auto child = children.begin(); child != children.end(); ++child)
    {
        if (*child == p_child)
        {
            children.erase(child);
            p_child->parent = nullptr;
            return;
        }
    }
    CG_WARNING(CGSTR("Trying to detach a child that doesn't exist."));
}

KEComponent* KEComponent::GetParent() const noexcept
{
    return parent;
}

const std::vector<KEComponent*>& KEComponent::GetChildren() const noexcept
{
    return children;
}


void KEComponent::AlignTop(float p_offset)
{
    auto global_position = GetGlobalPosition();
    global_position.y = KEGame::GetInstance()->GetGameWindow()->height / 2.0f - GetBoarderTopY() + p_offset;
    SetGlobalPosition(global_position);
}

void KEComponent::AlignBottom(float p_offset)
{
    auto global_position = GetGlobalPosition();
    global_position.y = KEGame::GetInstance()->GetGameWindow()->height / -2.0f - GetBoarderBottomY() + p_offset;
    SetGlobalPosition(global_position);
}

void KEComponent::AlignLeft(float p_offset)
{
    auto global_position = GetGlobalPosition();
    global_position.x = KEGame::GetInstance()->GetGameWindow()->width / -2.0f - GetBoarderLeftX() + p_offset;
    SetGlobalPosition(global_position);
}

void KEComponent::AlignRight(float p_offset)
{
    auto global_position = GetGlobalPosition();
    global_position.x = KEGame::GetInstance()->GetGameWindow()->width / 2.0f - GetBoarderRightX() + p_offset;
    SetGlobalPosition(global_position);
}

void KEComponent::AlignBottomToTop(KEIRectBoarder* p_target, float p_offset)
{
    auto global_position = GetGlobalPosition();
    global_position.y = p_target->GetBoarderTopY() + GetBoarderHeight() / 2.0f + p_offset;
    SetGlobalPosition(global_position);
}

void KEComponent::AlignTopToTop(KEIRectBoarder* p_target, float p_offset)
{
    auto global_position = GetGlobalPosition();
    global_position.y = p_target->GetBoarderTopY() - GetBoarderHeight() / 2.0f + p_offset;
    SetGlobalPosition(global_position);
}

void KEComponent::AlignTopToBottom(KEIRectBoarder* p_target, float p_offset)
{
    auto global_position = GetGlobalPosition();
    global_position.y = p_target->GetBoarderBottomY() - GetBoarderHeight() / 2.0f + p_offset;
    SetGlobalPosition(global_position);
}

void KEComponent::AlignBottomToBottom(KEIRectBoarder* p_target, float p_offset)
{
    auto global_position = GetGlobalPosition();
    global_position.y = p_target->GetBoarderBottomY() + GetBoarderHeight() / 2.0f + p_offset;
    SetGlobalPosition(global_position);
}

void KEComponent::AlignLeftToRight(KEIRectBoarder* p_target, float p_offset)
{
    auto global_position = GetGlobalPosition();
    global_position.x = p_target->GetBoarderRightX() + GetBoarderWidth() / 2.0f + p_offset;
    SetGlobalPosition(global_position);
}

void KEComponent::AlignRightToRight(KEIRectBoarder* p_target, float p_offset)
{
    auto global_position = GetGlobalPosition();
    global_position.x = p_target->GetBoarderRightX() - GetBoarderWidth() / 2.0f + p_offset;
    SetGlobalPosition(global_position);
}

void KEComponent::AlignRightToLeft(KEIRectBoarder* p_target, float p_offset)
{
    auto global_position = GetGlobalPosition();
    global_position.x = p_target->GetBoarderLeftX() - GetBoarderWidth() / 2.0f + p_offset;
    SetGlobalPosition(global_position);
}

void KEComponent::AlignLeftToLeft(KEIRectBoarder* p_target, float p_offset)
{
    auto global_position = GetGlobalPosition();
    global_position.x = p_target->GetBoarderLeftX() + GetBoarderWidth() / 2.0f + p_offset;
    SetGlobalPosition(global_position);
}
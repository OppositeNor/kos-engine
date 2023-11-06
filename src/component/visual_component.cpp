#include "kos_engine/component/visual_component.h"
#include "kos_engine/component/camera.h"
#include "kos_engine/utils.hpp"
#include "kos_engine/game.h"

KEVisualComponent::KEVisualComponent() : KEComponent()
{
    render_property = CGCreateRenderObjectProperty(CGConstructColor(1.0f, 1.0f, 1.0f,1.0f), 
        GetTransform().position, GetTransform().scale, GetTransform().rotation);
}

CGRenderObjectProperty* KEVisualComponent::GetRenderProperty() noexcept
{
    return render_property;
}

const CGRenderObjectProperty* KEVisualComponent::GetRenderProperty() const noexcept
{
    return render_property;
}

KEVisualComponent::KEVisualComponent(const KEVisualComponent& p_other) : KEComponent(p_other)
{
    render_property = CGCreateRenderObjectProperty(p_other.render_property->color, 
        p_other.GetTransform().position, p_other.GetTransform().scale, p_other.GetTransform().rotation);
    visible = p_other.visible;
}

KEVisualComponent::KEVisualComponent(KEVisualComponent&& p_other) : KEComponent(std::move(p_other))
{
    render_property = p_other.render_property;
    p_other.render_property = nullptr;
    visible = p_other.visible;
}

KEVisualComponent::~KEVisualComponent()
{
    CGFree(render_property);
}

void KEVisualComponent::Tick(double p_delta_time)
{
    KEComponent::Tick(p_delta_time);
    if (!GetLocallyVisible() || !IsVisible() || IsQueueFreed())
        return;

    render_property->z = GetTransform().depth;

    render_property->transform = GetTransform().position;
    if (KEGame::GetInstance()->GetMainCamera() != nullptr)
        render_property->transform -= KEGame::GetInstance()->GetMainCamera()->GetTransform().position;
    render_property->rotation = GetTransform().rotation;
    render_property->scale = GetTransform().scale;
    if (GetParent() != nullptr)
    {
        auto parent_transform_matrix = GetParent()->GetGlobalTransformMatrix();
        for (unsigned int i = 0; i < 4; ++i)
        {
            for (unsigned int j = 0; j < 4; ++j)
            {
                matrix_buffer[i][j] = (i < 3 && j < 3) ? parent_transform_matrix[j][i] : (i == j ? 1.0f : 0.0f);
            }
        }
        render_property->modify_matrix = (float*)matrix_buffer;
    }
    else
        render_property->modify_matrix = NULL;
    
    Draw(p_delta_time);
}

void KEVisualComponent::SetColor(const CGColor& p_color) noexcept
{
    render_property->color = p_color;
}
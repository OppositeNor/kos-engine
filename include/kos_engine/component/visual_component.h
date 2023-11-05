#pragma once
#include "kos_engine/component/component.h"

/**
 * @brief Visual component is the base class for all objects that are visible in the game world.
 * 
 */
class KEVisualComponent : public KEComponent
{
    KE_COMPONENT(KEVisualComponent)

    CGRenderObjectProperty* render_property;

    float matrix_buffer[4][4];
protected:

    /**
     * @brief Draw component on the window.
     * 
     * @param p_delta The time difference between frames
     */
    virtual void Draw(float p_delta) {};

public:

    /**
     * @brief Called every frame by the game.
     * 
     * @param p_delta_time The time difference between frames
     */
    virtual void Tick(double p_delta_time) override;

protected:

    /**
     * @brief Get the render property for objects to render.
     */
    CGRenderObjectProperty* GetRenderProperty() noexcept;
    
    const CGRenderObjectProperty* GetRenderProperty() const noexcept;
public:
    /**
     * @brief Constructor of KEVisualComponent.
     * 
     * @param p_position The initial position of the component.
     */
    KEVisualComponent();

    /**
     * @brief Copy constructor.
     * 
     * @param p_other The other KEVisualComponent object.
     */
    KEVisualComponent(const KEVisualComponent& p_other);

    /**
     * @brief Move constructor.
     * 
     * @param p_other The other KEVisualComponent object.
     */
    KEVisualComponent(KEVisualComponent&& p_other);

    virtual ~KEVisualComponent() override;

    /**
     * @brief Set the color of the component.
     * 
     * @param p_color The color to be set to.
     */
    void SetColor(const CGColor& p_color) noexcept;
};
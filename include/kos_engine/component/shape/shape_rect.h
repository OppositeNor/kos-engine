#pragma once
#include "kos_engine/component/visual_component.h"
#include "kos_engine/interface/irect.h"
#include <memory>

/**
 * @brief A rectangle shape.
 * @details This will be set locally invisible by default.
 */
class KEShapeRect : public KEVisualComponent
{
    KE_COMPONENT(KEShapeRect)

private:
    /**
     * @brief The width of the rectangle.
     */
    float width;
    /**
     * @brief The height of the rectangle.
     */
    float height;

    /**
     * @brief The quadrangle for CosGraphics to render.
     */
    std::unique_ptr<CGQuadrangle, decltype(CGFree)*> quadrangle_instance;

    /**
     * @brief Whether the quadrangle's width or height been changed.
     */
    bool need_update = false;

    /**
     * @brief Update the quadrangle/
     */
    void UpdateQuadrangle();
public:

    /**
     * @brief Constor for KEShapeRect.
     * 
     * @param width The width of the rectangle shape.
     * @param height The height of the rectangle shape.
     */
    KEShapeRect(float width = 1.0f, float height = 1.0f);
    
    /**
     * @brief Set the width of the shape.
     * 
     * @param p_width The width to be set to.
     */
    void SetWidth(float p_width);

    /**
     * @brief Set the height of the shape.
     * 
     * @param p_height The height to be set to.
     */
    void SetHeight(float p_height);

    /**
     * @brief Get the width of the shape.
     * 
     * @return float The width of the shape.
     */
    virtual float GetWidth() const override { return width; }
    /**
     * @brief Get the height of the shape.
     * 
     * @return float The height of the shape.
     */
    virtual float GetHeight() const override { return height; }

    /**
     * @brief Get the y coordinate value of the top of the shape.
     * 
     * @return float The y coordinate value of the top of the shape.
     */
    virtual float GetTopY() const override;
    /**
     * @brief Get the y coordinate value of the bottom of the shape.
     * 
     * @return float The y coordinate value of the bottom of the shape.
     */
    virtual float GetBottomY() const override;

    /**
     * @brief Get the x coordinate value of the left of the shape.
     * 
     * @return float The x coordinate value of the left of the shape.
     */
    virtual float GetLeftX() const override;

    /**
     * @brief Get the x coordinate value of the right of the shape.
     * 
     * @return float The x coordinate value of the right of the shape.
     */
    virtual float GetRightX() const override;

    /**
     * @brief Draw component on the window.
     * 
     * @param p_delta The time difference between frames
     */
    virtual void Draw(float p_delta) final override;
};
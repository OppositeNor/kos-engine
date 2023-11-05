#pragma once
#include "kos_engine/component/component.h"
#include "kos_engine/interface/irect.h"

class KEShapeRect : public KEComponent
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

public:

    KEShapeRect(float width, float height)
        : width(width), height(height)
    {}

    /**
     * @brief Get the width of the shape.
     * 
     * @return float The width of the shape.
     */
    virtual float GetWidth() const override {return width;}
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

};
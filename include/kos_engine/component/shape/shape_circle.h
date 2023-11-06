#pragma once
#include "kos_engine/component/visual_component.h"
#include "kos_engine/interface/icircle.h"

class KEShapeCircle : public KEVisualComponent, public KEICircle
{
    KE_COMPONENT(KEShapeCircle)

private:
    float radius;
public:
    /**
     * @brief Constructor for KEShapeCircle.
     * 
     * @param radius 
     */
    explicit KEShapeCircle(float radius = 1.0f)
        : radius(abs(radius))
    {}

    virtual ~KEShapeCircle() override {};


    /**
     * @brief Get the radius of the circle.
     * 
     * @return float The radius of the circle.
     */
    float& GetRadius() { return radius; }

    /**
     * @brief Get the radius of the circle.
     * 
     * @return float The radius of the circle.
     */
    virtual float GetRadius() const override { return radius; }

    /**
     * @brief Get the diameter of the circle.
     * 
     * @return float The diameter of the circle.
     */
    virtual float GetDiameter() const override { return radius * 2; }

    /**
     * @brief Get the circumference of the circle.
     * 
     * @return float The circumference of the circle.
     */
    virtual float GetCircumference() const override;

    /**
     * @brief Get the area of the circle.
     * 
     * @return float The area of the circle.
     */
    virtual float GetArea() const override;

        /**
     * @brief Get the width of the shape.
     * 
     * @return float The width of the shape.
     */
    virtual float GetWidth() const override { return GetDiameter(); }
    /**
     * @brief Get the height of the shape.
     * 
     * @return float The height of the shape.
     */
    virtual float GetHeight() const override { return GetDiameter(); }

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
#pragma once

class KEICircle
{
public:
    /**
     * @brief Get the radius of the circle.
     * 
     * @return float The radius of the circle.
     */
    virtual float GetRadius() const = 0;

    /**
     * @brief Get the diameter of the circle.
     * 
     * @return float The diameter of the circle.
     */
    virtual float GetDiameter() const = 0;

    /**
     * @brief Get the circumference of the circle.
     * 
     * @return float The circumference of the circle.
     */
    virtual float GetCircumference() const = 0;

    /**
     * @brief Get the area of the circle.
     * 
     * @return float The area of the circle.
     */
    virtual float GetArea() const = 0;
};
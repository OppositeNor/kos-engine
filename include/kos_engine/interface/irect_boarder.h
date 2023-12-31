#pragma once
#include "kos_engine/interface/irect.h"
/**
 * @brief Interface for objects that can be enclosed by a boarder.
 * @note A boarder is a rectangle that enclosed the whole component. The whole
 * component also includes the children of the component.
 */
class KEIRectBoarder : public KEIRect
{
public:
    /**
     * @brief Get the width of the boarder.
     * 
     * @return float The width of the boarder.
     */
    virtual float GetBoarderWidth() = 0;
    /**
     * @brief Get the height of the boarder.
     * 
     * @return float The height of the boarder.
     */
    virtual float GetBoarderHeight() = 0;

    /**
     * @brief Get the y coordinate value of the top of the boarder.
     * 
     * @return float The y coordinate value of the top of the boarder.
     */
    virtual float GetBoarderTopY() = 0;
    /**
     * @brief Get the y coordinate value of the bottom of the boarder.
     * 
     * @return float The y coordinate value of the bottom of the boarder.
     */
    virtual float GetBoarderBottomY() = 0;

    /**
     * @brief Get the x coordinate value of the left of the boarder.
     * 
     * @return float The x coordinate value of the left of the boarder.
     */
    virtual float GetBoarderLeftX() = 0;

    /**
     * @brief Get the x coordinate value of the right of the boarder.
     * 
     * @return float The x coordinate value of the right of the boarder.
     */
    virtual float GetBoarderRightX() = 0;
};
#pragma once

#include "kos_engine/component/visual_component.h"

/**
 * @brief The texture container component. It can contain a texture.
 * 
 * @brief This is the base class of all components that contains a texture.
 * By inheriting this class, the boarder demensions of the component can be
 * automatically calculated based on the texture.
 */
class KETextureContainer : public KEVisualComponent
{
    KE_COMPONENT(KETextureContainer)
protected:
    CGVisualImage* texture = nullptr;
public:

    /**
     * @brief Destroy the KETextureContainer object
     */
    virtual ~KETextureContainer() override;


    /**
     * @brief Get the width of the visual component.
     * 
     * @return float The width of the visual component.
     */
    virtual float GetBoarderWidth() noexcept override;
    /**
     * @brief Get the height of the visual component
     * 
     * @return float The height of the visual component
     */
    virtual float GetBoarderHeight() noexcept override;

    /**
     * @brief Get the y coordinate value of the top of the boarder.
     * 
     * @return float The y coordinate value of the top of the boarder.
     */
    virtual float GetBoarderTopY() noexcept override;
    /**
     * @brief Get the y coordinate value of the bottom of the boarder.
     * 
     * @return float The y coordinate value of the bottom of the boarder.
     */
    virtual float GetBoarderBottomY() noexcept override;

    /**
     * @brief Get the x coordinate value of the left of the boarder.
     * 
     * @return float The x coordinate value of the left of the boarder.
     */
    virtual float GetBoarderLeftX() noexcept override;

    /**
     * @brief Get the x coordinate value of the right of the boarder.
     * 
     * @return float The x coordinate value of the right of the boarder.
     */
    virtual float GetBoarderRightX() noexcept override;

    /**
     * @brief Get the width of the shape.
     * 
     * @return float The width of the shape.
     */
    virtual float GetWidth() const noexcept override;
    /**
     * @brief Get the height of the shape.
     * 
     * @return float The height of the shape.
     */
    virtual float GetHeight() const noexcept override;

    /**
     * @brief Get the y coordinate value of the top of the shape.
     * 
     * @return float The y coordinate value of the top of the shape.
     */
    virtual float GetTopY() const noexcept override;
    /**
     * @brief Get the y coordinate value of the bottom of the shape.
     * 
     * @return float The y coordinate value of the bottom of the shape.
     */
    virtual float GetBottomY() const noexcept override;

    /**
     * @brief Get the x coordinate value of the left of the shape.
     * 
     * @return float The x coordinate value of the left of the shape.
     */
    virtual float GetLeftX() const noexcept override;

    /**
     * @brief Get the x coordinate value of the right of the shape.
     * 
     * @return float The x coordinate value of the right of the shape.
     */
    virtual float GetRightX() const noexcept override;
    
    /**
     * @brief Construct a new KETextureContainer object
     */
    KETextureContainer() : KEVisualComponent() {}
    /**
     * @brief Copy constructor
     */
    KETextureContainer(const KETextureContainer& p_other);

    /**
     * @brief Move constructor
     */
    KETextureContainer(KETextureContainer&& p_other) noexcept;
};
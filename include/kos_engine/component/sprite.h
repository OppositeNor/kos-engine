#pragma once
#include "kos_engine/component/texture_container.h"
#include "cos_graphics/graphics.h"
#include <memory>

/**
 * @brief The sprite component. It can be used to render a component with a texture.
 * 
 * @details The Sprite component can render a texture on the screen.
 * 
 */
class KESprite : public KETextureContainer
{
    KE_COMPONENT(KESprite)
protected:
    virtual void Draw(float p_delta) final override;
public:
    /**
     * @brief Construct a new KESprite object
     * 
     * @param p_texture_rk The resource key of the texture for the sprite
     * @param p_position The position that the sprite is going to be on.
     */
    explicit KESprite(const KEString& p_texture_rk = KEString(CGSTR("")));

    /**
     * @brief Copy constructor
     * 
     * @param p_other The other KESprite object.
     */
    KESprite(const KESprite& p_other);

    /**
     * @brief Move constructor
     * 
     * @param p_other The other KESprite object
     */
    KESprite(KESprite&& p_other) noexcept;
    
    /**
     * @brief Construct a new KESprite object
     * 
     * @param p_texture The texture for the sprite. The texture is going to be copied.
     * @param p_position The position that the sprite is going to be on.
     */
    KESprite(CGVisualImage*& p_texture);

    /**
     * @brief Construct a new KESprite object
     * 
     * @param p_texture The texture for the sprite. The texture is going to be moved.
     * @param p_position The position that the sprite is going to be on.
     */
    KESprite(CGVisualImage*&& p_texture);

    virtual ~KESprite() override;

    /**
     * @brief Set the texture of the sprite. The texture is going to be copied.
     * 
     * @param p_texture The texture that the sprite is going to be set to.
     */
    void SetTexture(CGVisualImage*& p_texture);
    /**
     * @brief Set the texture of the sprite. The texture is going to be moved.
     * 
     * @param p_texture The texture that the sprite is going to be set to.
     */
    void SetTexture(CGVisualImage*&& p_texture) noexcept;

    /**
     * @brief Set the texture of the sprite
     * 
     * @param p_texture_rk The resource key of the texture file that the sprite is going to be set to.
     */
    void SetTexture(const KEString& p_texture_rk);
};
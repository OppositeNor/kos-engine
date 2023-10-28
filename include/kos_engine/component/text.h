#pragma once
#include "kos_engine/component/texture_container.h"

/**
 * @brief A text that can be rendered on the screen.
 */
class KEText : public KETextureContainer
{
    KE_COMPONENT(KEText)
private:
    KEString text;
    KEString font_rk;
    CGTextProperty text_property;

    void UpdateTextImage();
protected:
    virtual void Draw(float p_delta) final override;

public:
    /**
     * @brief Constructor of KEText.
     * 
     * @param p_text The text that the component will draw. If p_is_text_rk is 
     * set to true, then p_text is the resource key of the text.
     * @param p_text_property The property of the text.
     * @param p_is_text_rk Is p_text a resource key of the text.
     */
    KEText(const KEString& p_text, const CGTextProperty& p_text_property, bool p_is_text_rk = false);

    /**
     * @brief Constructor of KEText.
     * 
     * @param p_text The text that the component will draw. If p_is_text_rk is 
     * set to true, then p_text is the resource key of the text.
     * @param p_font_rk The resource key of the font.
     * @param p_text_property The property of the text.
     * @param p_is_text_rk Is p_text a resource key of the text.
     */
    KEText(const KEString& p_text, const KEString& p_font_rk, const CGTextProperty& p_text_property, bool p_is_text_rk = false);
    
    /**
     * @brief Copy constructor.
     * 
     * @param other The other KEText object.
     */
    KEText(const KEText& other);

    /**
     * @brief Move constructor.
     * 
     * @param other The other KEText object.
     */
    KEText(KEText&& other) noexcept;

    /**
     * @brief Destroy the KEText object.
     */
    virtual ~KEText() override;

    /**
     * @brief Set the text that the component will draw.
     * 
     * @param p_text_rk The resource key of the text to be set to.
     */
    void SetText(const KEString& p_text_rk);

    /**
     * @brief Get the text that the component will draw.
     * 
     * @return const KEString 
     */
    const KEString& GetText() const noexcept;

    /**
     * @brief Set the font of the text.
     * 
     * @param p_font_rk The resource key of the font to be set to.
     */
    void SetFont(const KEString& p_font_rk);

    /**
     * @brief Get the property of the text.
     * 
     * @return const CGTextProperty& The property of the text.
     */
    const CGTextProperty& GetTextProperty() const noexcept;
    
    /**
     * @brief Set the property of the text.
     * 
     * @param p_property The property that the text will be set to.
     */
    void SetTextProperty(const CGTextProperty& p_property);
};
#include "kos_engine/component/text.h"
#include "kos_engine/game.h"

void KEText::UpdateTextImage()
{
    if (texture != nullptr)
    {
        CGFree(texture);
        texture = nullptr;
    }
    if (text[0] == (CGChar)('\0'))
        return;
    if (font_rk[0] == (CGChar)('\0'))
        texture = CGCreateTextVisualImageRaw(text.c_str(), NULL, CGTextProperty(), KEGame::GetInstance()->GetGameWindow(), CG_FALSE);
    else
        texture = CGCreateTextVisualImage(text.c_str(), font_rk.c_str(), CGTextProperty(), KEGame::GetInstance()->GetGameWindow(), CG_FALSE);
}

KEText::KEText(const KEString& p_text, const CGTextProperty& p_text_property, bool p_is_text_rk) 
    : text(p_text), font_rk(CGSTR("")), text_property(p_text_property), KETextureContainer()
{
    CGChar* string_data = p_is_text_rk ? (CGChar*)CGLoadResource(p_text.c_str(), NULL, NULL) : (CGChar*)p_text.c_str();
    font_rk = CGSTR("");
    if (p_is_text_rk)
    {
        text = KEString(string_data);
        free(string_data);
    }
    else
        text = p_text;
    
    texture = CGCreateTextVisualImageRaw(p_text.c_str(), NULL, p_text_property, KEGame::GetInstance()->GetGameWindow(), CG_FALSE);
}

KEText::KEText(const KEString& p_text, const KEString& p_font_rk, const CGTextProperty& p_text_property, bool p_is_text_rk)
    : text(p_text), font_rk(p_font_rk), text_property(p_text_property), KETextureContainer()
{
    CGChar* string_data = p_is_text_rk ? (CGChar*)CGLoadResource(p_text.c_str(), NULL, NULL) : (CGChar*)p_text.c_str();
    font_rk = p_font_rk;
    if (p_is_text_rk)
    {
        text = KEString(string_data);
        free(string_data);
    }
    else
        text = p_text;
    texture = CGCreateTextVisualImage(p_text.c_str(), p_font_rk.c_str(), p_text_property, KEGame::GetInstance()->GetGameWindow(), CG_FALSE);
}

KEText::KEText(const KEText& other) : KETextureContainer(other)
{
    text = other.text;
    font_rk = other.font_rk;
    text_property = other.text_property;
    UpdateTextImage();
}

KEText::KEText(KEText&& other) noexcept : KETextureContainer(std::move(other))
{
    text = std::move(other.text);
    font_rk = std::move(other.font_rk);
    text_property = std::move(other.text_property);
    UpdateTextImage();
}

KEText::~KEText()
{
    
}

void KEText::Draw(float p_delta)
{
    if (texture == nullptr)
        return;
    CGDrawVisualImage(texture, GetRenderProperty(), KEGame::GetInstance()->GetGameWindow());
}

void KEText::SetText(const KEString& p_text_rk)
{
    auto string_data = (CGChar*)CGLoadResource(p_text_rk.c_str(), NULL, NULL);
    text = KEString(string_data);
    CGFree(string_data);
    UpdateTextImage();
}

const KEString& KEText::GetText() const noexcept
{
    return text;
}

void KEText::SetFont(const KEString& p_font_rk)
{
    font_rk = p_font_rk;
    UpdateTextImage();
}

const CGTextProperty& KEText::GetTextProperty() const noexcept
{
    return text_property;
}

void KEText::SetTextProperty(const CGTextProperty& p_property)
{
    text_property = p_property;
    UpdateTextImage();
}

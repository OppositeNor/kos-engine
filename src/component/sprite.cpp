#include "kos_engine/component/sprite.h"
#include "kos_engine/game.h"

#include "cos_graphics/log.h"

KESprite::KESprite(const KEString& p_texture_rk) : KETextureContainer()
{
    texture = nullptr;
    if (p_texture_rk == KEString(CGSTR("")))
        return;
    texture = CGCreateVisualImage(p_texture_rk.c_str(), KEGame::GetInstance()->GetGameWindow(), CG_FALSE);
}

KESprite::KESprite(CGVisualImage*& p_texture) : KETextureContainer()
{
    texture = CGCopyVisualImage(p_texture);
}

KESprite::~KESprite()
{
}

void KESprite::Draw(float p_delta)
{
    if (texture == nullptr)
        return;
    CGDrawVisualImage(texture, GetRenderProperty(), KEGame::GetInstance()->GetGameWindow());
}

KESprite::KESprite(CGVisualImage*&& p_texture) : KETextureContainer()
{
    texture = p_texture;
    p_texture = nullptr;
}

KESprite::KESprite(const KESprite& p_other) : KETextureContainer(p_other)
{

}

KESprite::KESprite(KESprite&& p_other) noexcept : KETextureContainer(std::move(p_other))
{

}

void KESprite::SetTexture(CGVisualImage*& p_texture)
{
    texture = CGCopyVisualImage(p_texture);
}

void KESprite::SetTexture(CGVisualImage*&& p_texture) noexcept
{
    texture = p_texture;
    p_texture = nullptr;
}
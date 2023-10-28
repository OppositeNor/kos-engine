#include "kos_engine/component/animation_sprite.h"
#include "kos_engine/game.h"
#include "kos_engine/utils.hpp"

#include "cos_graphics/log.h"


KEAnimationSprite::KEAnimationSprite(float p_fps)
    : frame_duration(KEUtils::GetReciprocal(p_fps)), KEVisualComponent()
{
    animation_finish_callback = [](KEAnimationSprite*){};
}

KEAnimationSprite::KEAnimationSprite(KEAnimationMap& p_animation_map, 
        KEString p_default_animation, float p_fps)
    : KEAnimationSprite(p_fps)
{
    animation_map = KEAnimationMap(p_animation_map);
    current_animation = p_default_animation;
}

KEAnimationSprite::KEAnimationSprite(KEAnimationMap&& p_animation_map, 
        KEString p_default_animation, float p_fps)
    : KEAnimationSprite(p_fps)
{
    animation_map = std::move(p_animation_map);
    current_animation = p_default_animation;
}

KEAnimationSprite::~KEAnimationSprite()
{
    // Free all the textures
    for (auto&& animation : animation_map)
    {
        for (auto&& frame : animation.second)
        {
            CGFree(frame);
        }
    }
}

void KEAnimationSprite::AddAnimation(const KEString& p_animation_name, const std::vector<CGVisualImage*>& p_animation)
{
    animation_map.insert(std::make_pair(p_animation_name, p_animation));
}

void KEAnimationSprite::AddAnimation(const KEAnimationPair& p_animation_pair)
{
    animation_map.insert(p_animation_pair);
}

void KEAnimationSprite::Play()
{
    is_playing = true;
}


void KEAnimationSprite::PlayFromStart()
{
    is_playing = true;
    clock = 0.0f;
}

void KEAnimationSprite::PlayFromStart(KEString p_animation_name)
{
    is_playing = true;
    current_animation = p_animation_name;
    clock = 0.0f;
}

void KEAnimationSprite::SetAnimationFinishCallback(const std::function<void(KEAnimationSprite*)>& p_animation_finish_callback)
{
    animation_finish_callback = p_animation_finish_callback;
}

void KEAnimationSprite::SetAnimationFinishCallback(const std::function<void(KEAnimationSprite*)>&& p_animation_finish_callback)
{
    animation_finish_callback = std::move(p_animation_finish_callback);
}

void KEAnimationSprite::Draw(float p_delta)
{
    if (current_animation == CGSTR("") || animation_map.size() == 0)
        return;
    if (animation_map.find(current_animation) == animation_map.end())
    {
        #ifdef CG_USE_WCHAR
        CG_WARNING(CGSTR("Animation %ls not found."), current_animation.c_str());
        #else
        CG_WARNING(CGSTR("Animation %s not found."), current_animation.c_str());
        #endif
        return;
    }
    auto& animation_played = animation_map[current_animation];
    if (animation_played.size() == 0)
        return;
    if (is_playing)
        clock += p_delta;
    int current_frame = (int)(clock / frame_duration);
    if (current_frame >= animation_played.size())
    {
        animation_finish_callback(this);
        current_frame = 0;
        clock = 0.0f;
    }
    auto frame_displayed = *(animation_played.begin() + current_frame);

    CGDrawVisualImage(frame_displayed, GetRenderProperty(), KEGame::GetInstance()->GetGameWindow());
}
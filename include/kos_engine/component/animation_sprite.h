#pragma once
#include "kos_engine/component/visual_component.h"
#include "cos_graphics/resource.h"
#include <vector>
#include <map>
#include <string>
#include <functional>

using KEAnimationMap = std::map<KEString, std::vector<CGVisualImage*>>;
using KEAnimationPair = std::pair<KEString, std::vector<CGVisualImage*>>;

/**
 * @brief A component that displays an animation.
 */
class KEAnimationSprite : public KEVisualComponent
{
    KE_COMPONENT(KEAnimationSprite)
protected:

    void Draw(float p_delta) override;

    /**
     * @brief How many seconds each frame is going to be displayed.
     */
    float frame_duration;

    /**
     * @brief The current animation that is playing;
     */
    KEString current_animation;

    /**
     * @brief An internal clock of the animation.
     */
    float clock;

    /**
     * @brief The map the animations' textures.
     * @tparam KEString The name of the animation.
     * @tparam std::std::vector<CGVisualImage*> The list of textures of the animation.
     */
    KEAnimationMap animation_map;

    /**
     * @brief Is the animation playing.
     */
    bool is_playing = false;

    /**
     * @brief The function that will be called after the animation is finished.
     * @param KEAnimationSprite* The animation that is finished.
     */
    std::function<void(KEAnimationSprite*)> animation_finish_callback;

public:

    virtual ~KEAnimationSprite();

    /**
     * @brief Construct a new KEAnimationSprite::KEAnimationSprite object
     * 
     * @param p_fps The frame rate of the animation.
     * @param p_position The position of the animation is going to be displayed.
     */
    explicit KEAnimationSprite(float p_fps = 5.0f);

    /**
     * @brief Construct a new KEAnimationSprite object
     * 
     * @param p_animation_map The map the animations' textures.
     * @param p_fps The frame rate of the animation.
     * @param p_start_frame The frame that the animation is going to start.
     * @param p_position The position of the animation is going to be displayed.
     */
    KEAnimationSprite(KEAnimationMap& p_animation_map, KEString p_default_animation, float p_fps = 5.0f);
    
    /**
     * @brief Construct a new KEAnimationSprite object
     * 
     * @param p_animation_map The map the animations' textures.
     * @param p_fps The frame rate of the animation.
     * @param p_start_frame The frame that the animation is going to start.
     * @param p_position The position of the animation is going to be displayed.
     */
    KEAnimationSprite(KEAnimationMap&& p_animation_map, KEString p_default_animation, float p_fps = 5.0f);

    

    /**
     * @brief Add an animation to the animation map.
     * 
     * @param p_animation_name The name of the animation.
     * @param p_animation The list of textures of the animation.
     */
    void AddAnimation(const KEString& p_animation_name, const std::vector<CGVisualImage*>& p_animation);

    /**
     * @brief Add an animation to the animation map.
     * 
     * @param p_animation_pair The pair of the animation name and the list of textures of the animation.
     */
    void AddAnimation(const KEAnimationPair& p_animation_pair);
    
    /**
     * @brief Play the current animation.
     */
    void Play();
    /**
     * @brief Play the current animation from start.
     */
    void PlayFromStart();
    /**
     * @brief Play the animation from start.
     * 
     * @param p_animation_name The animation to be played.
     */
    void PlayFromStart(KEString p_animation_name);

    /**
     * @brief Set the animation finish callback function.
     * 
     * @param animation_finish_callback The function that will be called after the animation is finished.
     */
    void SetAnimationFinishCallback(const std::function<void(KEAnimationSprite*)>& p_animation_finish_callback);

    /**
     * @brief Set the animation finish callback function.
     * 
     * @param animation_finish_callback The function that will be called after the animation is finished.
     */
    void SetAnimationFinishCallback(const std::function<void(KEAnimationSprite*)>&& p_animation_finish_callback);
};
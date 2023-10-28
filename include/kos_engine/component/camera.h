#pragma once
#include "kos_engine/component/component.h"

/**
 * @brief The camera of the game.
 * @details The camera can be used to put the view of the game 
 * on a specific position.
 */
class KECamera : public KEComponent
{
    KE_COMPONENT(KECamera)
public:
    KECamera();

    /**
     * @brief Use this camera as the main camera of the game.
     */
    void Use();
};
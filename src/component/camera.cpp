#include "kos_engine/component/camera.h"
#include "kos_engine/game.h"

#include "cos_graphics/log.h"

KECamera::KECamera() : KEComponent()
{
    
}

void KECamera::Use()
{
    KEGame::GetInstance()->SetMainCamera(this);
}
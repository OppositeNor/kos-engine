#include "kos_engine/game_factory.h"
#include "kos_engine/game.h"
#include "kos_engine/component/component.h"

KEGameFactory::KEGameFactory()
{
}

KEGameFactory::~KEGameFactory()
{
}

KEGame* KEGameFactory::CreateGame() const
{
    return new KEGame();
}

KEComponent* KEGameFactory::CreateRootComponent() const
{
    return new KEComponent();
}
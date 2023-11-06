#include "unit_test/unit_test.h"

#include "kos_engine/game.h"
#include "kos_engine/game_factory.h"
#include "kos_engine/component/sprite.h"
#include "kos_engine/component/text.h"
#include "kos_engine/utils.hpp"
#include "kos_engine/component/shape/shape_rect.h"
int main()
{
    KEGame::InitGame(new KEGameFactory(), 1280, 720, CGSTR("Test"), CG_FALSE, CG_FALSE);
    
    KEUnitTest::Start();


    auto sprite = new KESprite(CGCreateVisualImage(CGSTR("test1"), KEGame::GetInstance()->GetGameWindow(), CG_FALSE));
    sprite->GetLabel() = CGSTR("sprite");
    auto sprite2 = new KESprite(CGCreateVisualImage(CGSTR("test1"), KEGame::GetInstance()->GetGameWindow(), CG_FALSE));
    sprite2->GetLabel() = CGSTR("sprite2");
    sprite->AddChild(sprite2);
    sprite->GetTransform().scale = KEVector2(2.0f, 2.0f);
    sprite2->GetTransform().position = KEVector2(100.0f, -100.0f);
    sprite->AlignLeft();
    auto sprite3 = new KESprite(CGCreateVisualImage(CGSTR("test1"), KEGame::GetInstance()->GetGameWindow(), CG_FALSE));
    sprite3->GetLabel() = CGSTR("sprite3");
    sprite3->GetTransform().position = KEVector2(0.0f, -100.0f);
    sprite3->AlignLeftToRight(sprite2);
    //sprite->SetVisible(false);
    sprite3->QueueFree();
    
    auto shape_rect = new KEShapeRect(100.0f, 200.0f);
    shape_rect->SetColor(CGConstructColor(1.0f, 0.0f, 0.0f, 0.7f));

    KEGame::GetInstance()->StartGame();
    delete sprite;
    delete sprite2;
    delete shape_rect;
    KEGame::GetInstance()->ExitGame();
    return 0;
}
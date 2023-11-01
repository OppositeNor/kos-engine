#include "kos_engine/game.h"
#include "kos_engine/game_factory.h"
#include "kos_engine/component/sprite.h"
#include "kos_engine/component/text.h"
#include "kos_engine/utils.hpp"
#include "unit_test/unit_test.h"
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
    //auto text = new CGText(CGSTR("test_text"), CGConstructTextProperty(60, 60, 20, 5));
    KEGame::GetInstance()->StartGame();
    delete sprite;
    //delete sprite2;
    KEGame::GetInstance()->ExitGame();
    return 0;
}
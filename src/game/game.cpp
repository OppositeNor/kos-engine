#include "kos_engine/game.h"
#include "kos_engine/component/component.h"
#include "kos_engine/component/camera.h"
#include "kos_engine/game_factory.h"

#include "cos_graphics/log.h"

KEGame* KEGame::game_instance = nullptr;

KEGame::KEGame() : window_properties(WindowProperties(640, 480, CGSTR(""), CG_FALSE, CG_FALSE, CG_FALSE, CG_FALSE, CG_FALSE))
{
    
}

KEGame::~KEGame()
{
    game_initialized = false;
}

KEGame* KEGame::GetInstance()
{
    if (game_instance == nullptr)
        throw "The game instance is NULL. Please initialize the game before getting game instance.";
    return game_instance;
}

void KEGame::InitGame(unsigned int p_width, unsigned int p_height, const KEString& p_title, 
    CG_BOOL p_fullscreen, CG_BOOL p_resizable, CG_BOOL p_boarderless, CG_BOOL p_transparent, CG_BOOL p_topmost)
{
    InitGame(new KEGameFactory(), p_width, p_height, p_title, p_fullscreen, p_resizable, p_boarderless, p_transparent, p_topmost);
}

void KEGame::InitGame(unsigned int p_width, unsigned int p_height, const KEString& p_title, 
    CG_BOOL p_fullscreen, CG_BOOL p_resizable)
{
    InitGame(p_width, p_height, p_title, p_fullscreen, p_resizable, CG_FALSE, CG_FALSE, CG_FALSE);
}

void KEGame::InitGame(unsigned int p_width, unsigned int p_height, const KEString& p_title)
{
    InitGame(p_width, p_height, p_title, CG_FALSE, CG_TRUE, CG_FALSE, CG_FALSE, CG_FALSE);
}

void KEGame::InitGame(KEGameFactory*&& p_factory, unsigned int p_width, unsigned int p_height, const KEString& p_title, 
    CG_BOOL p_fullscreen, CG_BOOL p_resizable, CG_BOOL p_boarderless, CG_BOOL p_transparent, CG_BOOL p_topmost)
{
    CG_PRINT(CGSTR("Initializing game..."));
    if (game_factory != nullptr)
    {
        delete game_factory;
        game_factory = nullptr;
    }
    game_factory = p_factory;
    if (game_instance != nullptr)
    {
        delete game_instance;
        game_instance = nullptr;
    }
    game_instance = game_factory->CreateGame();
    game_instance->window_properties = WindowProperties(p_width, p_height, p_title, p_fullscreen, 
        p_resizable, p_boarderless, p_transparent, p_topmost);
    CG_PRINT(CGSTR("Creating window..."));
    
    CGWindowSubProperty window_sub_property = CGConstructDefaultWindowSubProperty();
    window_sub_property.use_full_screen = p_fullscreen;
    window_sub_property.resizable = p_resizable;
    window_sub_property.boarderless = p_boarderless;
    window_sub_property.transparent = p_transparent;
    window_sub_property.topmost = p_topmost;

    game_instance->game_window = CGCreateWindow(
        p_width, 
        p_height, 
        p_title.c_str(),
        window_sub_property);
    CGSetKeyCallback(KEGame::KeyInputCallback);
    if (game_instance->game_window == nullptr)
        throw "Failed to create window";
    CG_PRINT(CGSTR("Window created."));
    CG_PRINT(CGSTR("Game initialized."));
    game_instance->game_initialized = true;
    game_instance->main_camera = new KECamera();
}

void KEGame::InitGame(KEGameFactory*&& p_factory, unsigned int p_width, unsigned int p_height, const KEString& p_title, 
    CG_BOOL p_fullscreen, CG_BOOL p_resizable)
{
    InitGame(std::move(p_factory), p_width, p_height, p_title, p_fullscreen, p_resizable, CG_FALSE, CG_FALSE, CG_FALSE);
}

void KEGame::InitGame(KEGameFactory*&& p_factory, unsigned int p_width, unsigned int p_height, const KEString& p_title)
{
    InitGame(std::move(p_factory), p_width, p_height, p_title, CG_FALSE, CG_TRUE, CG_FALSE, CG_FALSE, CG_FALSE);
}

void KEGame::StartGame()
{
    if (game_instance == nullptr)
        throw "The game instance is NULL. Please initialize the game before starting the game.";
    if (!game_instance->game_initialized)
        throw "The game is not initialized. Please initialize the game before starting the game.";
    game_instance->Ready();
    game_instance->root_component = game_factory->CreateRootComponent();
    game_instance->root_component->OnEnter();
    game_instance->GameLoop();
}

void KEGame::ExitGame()
{
    if (game_instance == nullptr)
        throw "The game instance is NULL. Please initialize the game before exiting the game.";
    if (!game_instance->game_initialized)
        throw "The game is not initialized. Please initialize the game before exiting the game.";
    delete game_instance->root_component;
    delete game_instance;
    game_instance = nullptr;
    CGTerminateGraphics();
    CG_PRINT(CGSTR("Game exited."));
    delete game_factory;
}

void KEGame::AddComponent(KEComponent* p_component)
{
    component_list.insert(component_list.end(), p_component);
}

void KEGame::RemoveComponent(KEComponent* p_component)
{
    for (auto iter = component_list.begin(); iter < component_list.end(); ++iter)
    {
        if (*iter != p_component)
            continue;
        else
        {
            component_list.erase(iter);
            break;
        }
    }
}

void KEGame::SetWindowClearColor(const CGColor& p_color)
{
    if (game_instance == nullptr)
        throw "The game instance is NULL. Please initialize the game before setting the window clear color.";
    if (!game_instance->game_initialized)
        throw "The game is not initialized. Please initialize the game before setting the window clear color.";
    CGSetClearScreenColor(p_color);
}

const KECamera* KEGame::GetMainCamera() const noexcept
{
    return main_camera;
}

KECamera* KEGame::GetMainCamera() noexcept
{
    return main_camera;
}

void KEGame::SetMainCamera(KECamera* p_camera) noexcept
{
    main_camera = p_camera;
}

const CGWindow* KEGame::GetGameWindow() const noexcept
{
    return game_window;
}

CGWindow* KEGame::GetGameWindow() noexcept
{
    return game_window;
}

void KEGame::Tick(float p_delta)
{
    Update(p_delta);
    for (auto& i : component_list)
    {
        i->Tick(p_delta);
        if (i->IsQueueFreed())
            component_free_list.insert(component_free_list.end(), i);
    }
}

void KEGame::ProcessComponentKeyInput(int p_key, int p_action)
{
    for (auto& i : component_list)
    {
        i->KeyInput(p_key, p_action);
    }
}

void KEGame::GameLoop()
{
    double tick_end_time = CGGetCurrentTime();
    while (!CGShouldWindowClose(game_window))
    {
        input_handler.UpdateInput();
        static double tick_start_time = 0;
        static double delta = 0.01;
        tick_start_time = CGGetCurrentTime();
        
        CGTickRenderStart(game_window);
        Tick(delta);
        CGWindowDraw(game_window);
        for (auto i = component_free_list.begin(); i < component_free_list.end(); ++i)
        {
            delete *i;
            component_free_list.erase(i);
        }
        CGTickRenderEnd();

        tick_end_time = CGGetCurrentTime();
        delta = tick_end_time - tick_start_time;
    }
}

void KEGame::KeyInputCallback(CGWindow* p_window, int p_key, int p_action)
{
    KEGame::GetInstance()->input_handler.KeyFunc(p_key, p_action);
    KEGame::GetInstance()->ProcessComponentKeyInput(p_key, p_action);
    
}
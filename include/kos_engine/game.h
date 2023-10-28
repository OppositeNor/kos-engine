#pragma once
#include "cos_graphics/graphics.h"
#include "kos_engine/input_handler.h"
#include <vector>
#include <string>
#include <functional>

class KEComponent;
class KECamera;
class KEGameFactory;

/**
 * @brief The game class.
 */
class KEGame
{
    friend KEGameFactory;
    /**
     * @brief The instance of the game.
     */
    static KEGame* game_instance;

    /**
     * @brief The root component of the game.
     */
    KEComponent* root_component = nullptr;

    /**
     * @brief The window for the game to run on.
     */
    CGWindow* game_window = nullptr;
    
    /**
     * @brief The properties of the window.
     */
    struct WindowProperties
    {
        unsigned int width;
        unsigned int height;
        KEString title;
        CG_BOOL resizable;
        CG_BOOL fullscreen;
        CG_BOOL borderless;
        CG_BOOL transparent;
        CG_BOOL topmost;

        WindowProperties(unsigned int p_width, unsigned int p_height, KEString p_title, 
                CG_BOOL p_fullscreen = CG_FALSE, CG_BOOL p_resizable = CG_TRUE) noexcept
            : WindowProperties(p_width, p_height, p_title, p_fullscreen, p_resizable, CG_FALSE, CG_FALSE, CG_FALSE)
        {}

        WindowProperties(unsigned int p_width, unsigned int p_height, KEString p_title, 
                CG_BOOL p_fullscreen, CG_BOOL p_resizable, CG_BOOL p_boarderless, CG_BOOL p_transparent, CG_BOOL p_topmost) noexcept
            : width(p_width), height(p_height), title(p_title), resizable(p_resizable), fullscreen(p_fullscreen),
            borderless(p_boarderless), transparent(p_transparent), topmost(p_topmost)
        {}
    } window_properties;

    /**
     * @brief List of components that's in the game.
     */
    std::vector<KEComponent*> component_list;

    /**
     * @brief The component that are prepared, but have not called the Ready() function.
     */
    std::vector<KEComponent*> component_free_list;

    bool game_initialized = false;

    /**
     * @brief The main camera for the game.
     */
    KECamera* main_camera = nullptr;

    /**
     * @brief The factory that created the game.
     */
    inline static KEGameFactory* game_factory = nullptr;

    /**
     * @brief Input handler.
     */
    KEInputHandler input_handler;

protected:
    /**
     * @brief Called once when the game is created.
     */
    virtual void Ready() {}

    /**
     * @brief Called every frame.
     * 
     * @param p_delta The difference in time between frames.
     */
    virtual void Update(float p_delta) {}
    
    /**
     * @brief Called when a key input is received.
     * 
     * @param p_key The key that recieves the action.
     * @param p_action The action of the key. This should be one of CG_PRESS, CG_RELEASE, CG_REPEAT.
     */
    virtual void KeyInput(int p_key, int p_action) {}
    
protected:

    /**
     * @brief Constructor
     */
    KEGame();

public:

    /**
     * @brief Destroy the KEGame object
     */
    virtual ~KEGame();

    /**
     * @brief Get the root component of the game.
     * 
     * @return KEComponent* The root component of the game.
     */
    inline KEComponent* GetRootComponent() noexcept { return root_component; };

    /**
     * @brief Get the instance of the game. If the game is not started, this will return nullptr.
     * 
     * @return KEGame* The instance of the game.
     */
    static KEGame* GetInstance();

    static void InitGame(
        unsigned int p_width, 
        unsigned int p_height, 
        const KEString& p_title,
        CG_BOOL p_fullscreen,
        CG_BOOL p_resizable,
        CG_BOOL boarderless, 
        CG_BOOL transparent, 
        CG_BOOL topmost);
    
    static void InitGame(
        unsigned int p_width, 
        unsigned int p_height, 
        const KEString& p_title, 
        CG_BOOL p_fullscreen, 
        CG_BOOL p_resizable);

    static void InitGame(
        unsigned int p_width, 
        unsigned int p_height, 
        const KEString& p_title);
    
    static void InitGame(
        KEGameFactory*&& p_factory, 
        unsigned int p_width, 
        unsigned int p_height, 
        const KEString& p_title, 
        CG_BOOL p_fullscreen, 
        CG_BOOL p_resizable, 
        CG_BOOL p_boarderless, 
        CG_BOOL p_transparent, 
        CG_BOOL p_topmost);
    
    static void InitGame(
        KEGameFactory*&& p_factory, 
        unsigned int p_width, 
        unsigned int p_height, 
        const KEString& p_title, 
        CG_BOOL p_fullscreen, 
        CG_BOOL p_resizable);

    static void InitGame(
        KEGameFactory*&& p_factory, 
        unsigned int p_width, 
        unsigned int p_height, 
        const KEString& p_title);

    /**
     * @brief Start the game.
     */
    static void StartGame();

    /**
     * @brief Exit the game.
     */
    static void ExitGame();

    /**
     * @brief Get the instance of the game window.
     * 
     * @return CGWindow* The instance of the game window.
     */
    const CGWindow* GetGameWindow() const noexcept;
    
    /**
     * @brief Get the instance of the game window.
     * 
     * @return CGWindow* The instance of the game window.
     */
    CGWindow* GetGameWindow() noexcept;

    /**
     * @brief Add component to the component list, and return the component's identifier.
     * 
     * @param p_component The component to be added.
     * @return unsigned int The component's identifier.
     */
    void AddComponent(class KEComponent* p_component);
    
    /**
     * @brief Remove component from the component list.
     * 
     * @param p_component The component to be removed.
     */
    void RemoveComponent(KEComponent* p_component);

    /**
     * @brief Set the clear color of the window
     * 
     * @param p_color The color to be set to
     */
    void SetWindowClearColor(const CGColor& p_color);

    /**
     * @brief Get the Main Camera object
     * 
     * @return KECamera* The main camera object.
     */
    const KECamera* GetMainCamera() const noexcept;
    
    /**
     * @brief Get the Main Camera object
     * 
     * @return KECamera* The main camera object.
     */
    KECamera* GetMainCamera() noexcept;

    /**
     * @brief Use the camera as the main camera.
     * 
     * @param p_camera The camera that the main camera will be set to.
     */
    void SetMainCamera(KECamera* p_camera) noexcept;

    /**
     * @brief Get the input handler
     * 
     * @return KEInputHandler& The input handler
     */
    KEInputHandler& GetInputHandler() noexcept {return input_handler;};
    
private:

    /**
     * @brief Game loop.
     */
    void GameLoop();

    /**
     * @brief Update, called every frame.
     */
    void Tick(float p_delta);

    /**
     * @brief Process the input function in the components
     * 
     * @param p_key The key that recieves the action.
     * @param p_action The action of the key. This should be one of CG_PRESS, CG_RELEASE, CG_REPEAT.
     */
    void ProcessComponentKeyInput(int p_key, int p_action);

    /**
     * @brief The callback function for keyboard input.
     * 
     * @param p_window The window that the input is from.
     * @param p_key The key that is pressed.
     * @param p_action The action of the key. This should be one of CG_PRESS, CG_RELEASE, CG_REPEAT.
     */
    static void KeyInputCallback(CGWindow* p_window, int p_key, int p_action);

};
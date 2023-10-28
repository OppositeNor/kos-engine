#pragma once
/**
 * @brief Contructor of the game object.
 */
class KEGame;
class KEGameFactory
{
    friend KEGame;
protected:
    /**
     * @brief Create a instance of the game.
     * 
     * @return KEGame* 
     */
    virtual KEGame* CreateGame() const;

    /**
     * @brief Create a root component of the game.
     * 
     * @return KEComponent* 
     */
    virtual class KEComponent* CreateRootComponent() const;

public:
    KEGameFactory();
    virtual ~KEGameFactory();

};
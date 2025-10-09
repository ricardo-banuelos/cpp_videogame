#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "GameState.h"
#include "Player.h"

class Game {
public:
    Game();
    ~Game();
    
    void run();
    
private:
    void handleEvents();
    void update(float deltaTime);
    void render();
    
    void changeState(GameState newState);
    void handleMenuInput();
    void handlePlayingInput();
    void handlePausedInput();
    void handleGameOverInput();
    
    sf::RenderWindow mWindow;
    GameState mCurrentState;
    std::shared_ptr<Player> mPlayer;
    sf::Clock mClock;
    
    static const int WINDOW_WIDTH = 1920;
    static const int WINDOW_HEIGHT = 1080;
};

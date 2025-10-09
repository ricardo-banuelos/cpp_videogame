#include "Game.h"
#include "UI.h"
#include <iostream>

Game::Game() 
    : mWindow(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Platformer Game"),
      mCurrentState(GameState::Menu),
      mPlayer(nullptr) {
    mWindow.setFramerateLimit(60);
}

Game::~Game() {}

void Game::run() {
    while (mWindow.isOpen()) {
        handleEvents();
        
        float deltaTime = mClock.restart().asSeconds();
        update(deltaTime);
        
        render();
    }
}

void Game::handleEvents() {
    while (const std::optional event = mWindow.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            mWindow.close();
        }
        else if (const auto* keyEvent = event->getIf<sf::Event::KeyPressed>()) {
            switch (mCurrentState) {
                case GameState::Menu:
                    handleMenuInput();
                    break;
                case GameState::Playing:
                    handlePlayingInput();
                    break;
                case GameState::Paused:
                    handlePausedInput();
                    break;
                case GameState::GameOver:
                    handleGameOverInput();
                    break;
            }
        }
    }
}

void Game::update(float deltaTime) {
    switch (mCurrentState) {
        case GameState::Menu:
            // No updates needed for menu
            break;
            
        case GameState::Playing:
            if (mPlayer) {
                mPlayer->update(deltaTime);
                
                // Check lose condition (fall below screen)
                if (mPlayer->getPosition().y > WINDOW_HEIGHT) {
                    changeState(GameState::GameOver);
                }
            }
            break;
            
        case GameState::Paused:
            // No updates when paused
            break;
            
        case GameState::GameOver:
            // No updates for game over
            break;
    }
}

void Game::render() {
    switch (mCurrentState) {
        case GameState::Menu:
            UI::renderMenu(mWindow);
            break;
            
        case GameState::Playing:
            mWindow.clear(sf::Color::Black);
            if (mPlayer) {
                mPlayer->render(mWindow);
            }
            break;
            
        case GameState::Paused:
            // First render the game state, then overlay
            mWindow.clear(sf::Color::Black);
            if (mPlayer) {
                mPlayer->render(mWindow);
            }
            UI::renderPauseOverlay(mWindow);
            break;
            
        case GameState::GameOver:
            UI::renderGameOver(mWindow);
            break;
    }
    
    mWindow.display();
}

void Game::changeState(GameState newState) {
    mCurrentState = newState;
    
    // Initialize state-specific resources
    switch (newState) {
        case GameState::Playing:
            if (!mPlayer) {
                mPlayer = std::make_shared<Player>(960 - 50, 540 - 50, 100, 100);
            }
            break;
        case GameState::Menu:
        case GameState::Paused:
        case GameState::GameOver:
            // No special initialization needed
            break;
    }
}

void Game::handleMenuInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
        changeState(GameState::Playing);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
        mWindow.close();
    }
}

void Game::handlePlayingInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
        changeState(GameState::Paused);
    }
}

void Game::handlePausedInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
        changeState(GameState::Playing);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
        changeState(GameState::Menu);
    }
}

void Game::handleGameOverInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)) {
        // Reset player and restart
        if (mPlayer) {
            mPlayer->reset();
        }
        changeState(GameState::Playing);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
        changeState(GameState::Menu);
    }
}

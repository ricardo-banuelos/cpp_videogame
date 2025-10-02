#include <SFML/Graphics.hpp>
#include <iostream>

#include "Player.h"

int main()
{
    const int WINDOW_WIDTH = 1920;
    const int WINDOW_HEIGHT = 1080;

    auto window = sf::RenderWindow(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), 
        "CMake SFML Project"
    );
    window.setFramerateLimit(60);

    auto player = std::make_shared<Player>(960 - 50, 540 - 50, 100, 100);
    sf::Clock clock;
    float groundY = 540.0f; 
    float velocityY = 0.0f;
    float gravity = 900.0f; // pixels/sec^2
    bool isOnGround = true;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            else if(const auto* keyEvent = event->getIf<sf::Event::KeyPressed>()) 
            {
                if(keyEvent->code == sf::Keyboard::Key::Escape) {
                    window.close();
                }
            }
        }

        float deltaTime = clock.restart().asSeconds();
        // float speed = 300.0f;

        // sf::Vector2f movement(0.0f, 0.0f);
        // if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        //     movement.x -= speed * deltaTime;
        // }
        // if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        //     movement.x += speed * deltaTime;
        // }
        // if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && isOnGround) {
        //     velocityY = -500.0f; // Jump impulse
        //     isOnGround = false;
        // }

        // // Apply gravity if not on ground
        // if(!isOnGround) {
        //     velocityY += gravity * deltaTime;
        //     movement.y += velocityY * deltaTime;
        // }

        // // player->move(movement);

        // // if(player->getPosition().y >= groundY) {
        // //     player->setPosition(sf::Vector2f(player->getPosition().x, groundY));
        // //     velocityY = 0.0f;
        // //     isOnGround = true;
        // // }
        player->update(deltaTime);
        window.clear(sf::Color::Black);
        player->render(window);
        window.display();
    }
}
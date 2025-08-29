#include <SFML/Graphics.hpp>

int main()
{
    auto window = sf::RenderWindow(
        sf::VideoMode({1920u, 1080u}), 
        "CMake SFML Project",
        sf::State::Fullscreen
    );
    window.setFramerateLimit(144);

    auto object = sf::RectangleShape({100, 100});
    object.setPosition(sf::Vector2f{960 - 50, 540 - 50});   
    object.setFillColor(sf::Color::White);

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
                if(keyEvent->code == sf::Keyboard::Key::Space && isOnGround) {
                    velocityY = -500.0f; // Jump impulse
                    isOnGround = false;
                }
            }
        }

        float deltaTime = clock.restart().asSeconds();
        float speed = 300.0f;

        sf::Vector2f movement(0.0f, 0.0f);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            movement.x -= speed * deltaTime;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            movement.x += speed * deltaTime;
        }

        // Apply gravity if not on ground
        if(!isOnGround) {
            velocityY += gravity * deltaTime;
            movement.y += velocityY * deltaTime;
        }

        object.move(movement);

        if(object.getPosition().y >= groundY) {
            object.setPosition(sf::Vector2f(object.getPosition().x, groundY));
            velocityY = 0.0f;
            isOnGround = true;
        }

        window.clear(sf::Color::Black);
        window.draw(object);
        window.display();
    }
}
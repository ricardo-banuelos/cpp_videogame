#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

class GameObject {
public:
    GameObject();
    virtual ~GameObject();                 
    virtual void update(float deltaTime) = 0;
    virtual void render(sf::RenderWindow& window) = 0;

    sf::Vector2f getPosition() const;
    sf::Vector2f getSize() const;

protected:
    void setPosition(const sf::Vector2f& position);
    void setSize(const sf::Vector2f& size);
    void setTexture(std::shared_ptr<sf::Texture> texture);
    void move(const sf::Vector2f& offset);
    
    sf::Vector2f mPosition;
    sf::Vector2f mSize;
    sf::RectangleShape mShape;
    std::shared_ptr<sf::Texture> mTexture; 
};
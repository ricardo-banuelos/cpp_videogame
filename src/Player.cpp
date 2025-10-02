#include "Player.h"
#include "GameObject.h"

Player::Player(float x, float y, float width, float height, std::shared_ptr<sf::Texture> texture)
    : GameObject(),
      mSpeed(300.0f),
      mGroundY(y + height),
      mVelocityY(0.0f),
      mIsOnGround(true){
    setPosition({x, y});
    setSize({width, height});
    
    if(texture) {
        setTexture(texture);
    }

    mShape.setFillColor(sf::Color::Green);
}

Player::~Player() {}

void Player::update(float deltaTime) {
    sf::Vector2f movement(0.0f, 0.0f);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        movement.x -= mSpeed * deltaTime;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        movement.x += mSpeed * deltaTime;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && mIsOnGround) {
        mVelocityY = -500.0f; // Jump impulse
        mIsOnGround = false;
    }
    if(!mIsOnGround) {
        mVelocityY += 900.0f * deltaTime; // Gravity constant
        movement.y += mVelocityY * deltaTime;
    }

    this->move(movement);

    if(this->getPosition().y >= mGroundY) {
        this->setPosition(sf::Vector2f(this->getPosition().x, mGroundY));
        mVelocityY = 0.0f;
        mIsOnGround = true;
    }
}

void Player::render(sf::RenderWindow& window) {
    window.draw(mShape);
}
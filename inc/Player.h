#pragma once

#include "GameObject.h"
#include <memory>

class Player : public GameObject {
public:
    Player(float x, float y, float width, float height, std::shared_ptr<sf::Texture> texture = nullptr);
    ~Player();
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;
    void reset();
private:    
    float mSpeed;
    float mGroundY;
    float mVelocityY;
    bool mIsOnGround;
};
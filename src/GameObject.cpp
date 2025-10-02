#include "GameObject.h"

GameObject::GameObject(){}
GameObject::~GameObject() {}

sf::Vector2f GameObject::getPosition() const {
    return mPosition;
}

sf::Vector2f GameObject::getSize() const {
    return mSize;
}

void GameObject::setPosition(const sf::Vector2f& position) {
    mPosition = position;
    mShape.setPosition(position);
}

void GameObject::setSize(const sf::Vector2f& size) {
    mSize = size;
    mShape.setSize(size);
}

void GameObject::setTexture(std::shared_ptr<sf::Texture> texture) {
    mTexture = texture;
    mShape.setTexture(mTexture.get());
}

void GameObject::move(const sf::Vector2f& offset) {
    mPosition += offset;
    mShape.move(offset);
}

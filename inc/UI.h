#pragma once

#include <SFML/Graphics.hpp>

class UI {
public:
    static void renderMenu(sf::RenderWindow& window);
    static void renderPauseOverlay(sf::RenderWindow& window);
    static void renderGameOver(sf::RenderWindow& window);
    
private:
    static sf::Text createText(const std::string& text, float x, float y, sf::Color color = sf::Color::White);
};

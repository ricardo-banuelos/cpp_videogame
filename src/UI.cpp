#include "UI.h"
#include <iostream>

sf::Text UI::createText(const std::string& text, float x, float y, sf::Color color) {
    static sf::Font font; // Static font to reuse across calls
    static bool fontLoaded = false;
    
    if (!fontLoaded) {
        // Try to load a system font, fallback to default if not available
        if (!font.openFromFile("/usr/share/fonts/truetype/ubuntu/Ubuntu-R.ttf")) {
            // If system font fails, we'll use SFML's default font
            // For now, we'll create a simple workaround
        }
        fontLoaded = true;
    }
    
    sf::Text sfText(font, text, 48);
    sfText.setFillColor(color);
    sfText.setPosition(sf::Vector2f(x, y));
    return sfText;
}

void UI::renderMenu(sf::RenderWindow& window) {
    window.clear(sf::Color(50, 50, 100)); // Dark blue background
    
    auto title = createText("PLATFORMER GAME", 400, 300, sf::Color::White);
    auto instruction = createText("Press SPACE to Start", 500, 500, sf::Color::Yellow);
    auto exitInstruction = createText("Press ESC to Exit", 550, 600, sf::Color::Cyan);
    
    window.draw(title);
    window.draw(instruction);
    window.draw(exitInstruction);
}

void UI::renderPauseOverlay(sf::RenderWindow& window) {
    // Draw semi-transparent overlay
    sf::RectangleShape overlay(sf::Vector2f(1920, 1080));
    overlay.setFillColor(sf::Color(0, 0, 0, 128));
    window.draw(overlay);
    
    auto pausedText = createText("PAUSED", 700, 400, sf::Color::White);
    auto resumeInstruction = createText("Press ESC to Resume", 500, 500, sf::Color::Yellow);
    auto menuInstruction = createText("Press Q to Return to Menu", 450, 600, sf::Color::Cyan);
    
    window.draw(pausedText);
    window.draw(resumeInstruction);
    window.draw(menuInstruction);
}

void UI::renderGameOver(sf::RenderWindow& window) {
    window.clear(sf::Color(100, 50, 50)); // Dark red background
    
    auto gameOverText = createText("GAME OVER", 600, 300, sf::Color::Red);
    auto restartInstruction = createText("Press R to Restart", 500, 500, sf::Color::Yellow);
    auto menuInstruction = createText("Press ESC to Return to Menu", 450, 600, sf::Color::Cyan);
    
    window.draw(gameOverText);
    window.draw(restartInstruction);
    window.draw(menuInstruction);
}

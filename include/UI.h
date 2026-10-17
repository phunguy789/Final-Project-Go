#pragma once
#include "Game.h"
#include <SFML/Graphics.hpp>
class UI 
{   
    public:
    UI();
    void drawMenu(sf::RenderWindow &w, sf::Font &font);
    void drawBoard(sf::RenderWindow &w, sf::Font &font, Game &game);
    void drawDifficultyMenu(sf::RenderWindow &w, sf::Font &font);
};
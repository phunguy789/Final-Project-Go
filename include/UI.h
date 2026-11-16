#pragma once
#include "Game.h"
#include <SFML/Graphics.hpp>
class UI 
{   
    public:
    UI();

    void drawSetting(sf::RenderWindow &w, sf::Font &font, Game &game);
    void drawBoardTheme(sf::RenderWindow &w, sf::Font &font, Game &game);
    void drawStoneTheme(sf::RenderWindow &w, sf::Font &font, Game &game);
    void drawSoundSettings(sf::RenderWindow &w, sf::Font &font, Game &game);
    void drawMusicSettings(sf::RenderWindow &w, sf::Font &font, Game &game);

    void drawBoard(sf::RenderWindow &w, sf::Font &font, Game &game);

    void drawMenu(sf::RenderWindow &w, sf::Font &font);

    void drawDifficultyMenu(sf::RenderWindow &w, sf::Font &font);
};
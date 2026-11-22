#pragma once
#include "Game.h"
#include <SFML/Graphics.hpp>
class UI 
{   
    public:
    sf::Texture fireTexture;
    sf::Texture waterTexture;
    
    UI();

    void drawNotification(sf::RenderWindow &w, sf::Font &font, bool check, bool type);

    void drawSetting(sf::RenderWindow &w, sf::Font &font, Game &game);
    void drawBackbutton(sf::RenderWindow &w, sf::Font &font);
    void drawBoardTheme(sf::RenderWindow &w, sf::Font &font, Game &game);
    void drawStoneTheme(sf::RenderWindow &w, sf::Font &font, Game &game);
    void drawSoundSettings(sf::RenderWindow &w, sf::Font &font, Game &game);
    void drawMusicSettings(sf::RenderWindow &w, sf::Font &font, Game &game);

    void drawBoard(sf::RenderWindow &w, sf::Font &font, Game &game);

    void drawMenu(sf::RenderWindow &w, sf::Font &font);

    void drawDifficultyMenu(sf::RenderWindow &w, sf::Font &font);
};
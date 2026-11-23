#include "UI.h"
#include "Game.h"
#include <cstring>
#include <SFML/Graphics.hpp>
#include <iostream>
#define fi first 
#define se second 
using pii = pair<int, int>;
using namespace std;
UI::UI()
{
    if (fireTexture.loadFromFile("assets/stones/fire_stone.png"));
    if (waterTexture.loadFromFile("assets/stones/water_stone.png"));
}
void UI::drawBackbutton(sf::RenderWindow &w, sf::Font &font)
{
    sf::RectangleShape backButton({100.f, 45.f});
    backButton.setPosition({30.f, 25.f});
    backButton.setFillColor(sf::Color(245, 222, 179));
    backButton.setOutlineThickness(2.f);
    backButton.setOutlineColor(sf::Color(75, 45, 20));

    sf::Text backText(font, "BACK", 20);
    backText.setPosition({55.f, 33.f});
    backText.setFillColor(sf::Color::Black);

    w.draw(backButton);
    w.draw(backText);
}
void UI::drawSetting(sf::RenderWindow &w, sf::Font &font, Game &game)
{
    sf::RectangleShape background(sf::Vector2f(800.f, 800.f));
    background.setPosition(sf::Vector2f(0.f, 0.f));
    background.setFillColor(sf::Color(243, 235, 221));
    w.draw(background);

    drawBackbutton(w, font);

    drawBoardTheme(w, font, game);
    drawStoneTheme(w, font, game);
    drawSoundSettings(w, font, game);
    drawMusicSettings(w, font, game);
}
void UI::drawBoardTheme(sf::RenderWindow &w, sf::Font &font, Game &game)
{
    sf::Text title(font, "BOARD COLOR", 25);
    title.setPosition({300.f, 80.f});
    title.setFillColor(sf::Color(40, 30, 20));
    w.draw(title);

    string names[3] = {"CLASSIC", "DARK", "LIGHT"};

    sf::Color colors[3] =
    {
        sf::Color(220, 179, 92),
        sf::Color(110, 75, 45),
        sf::Color(240, 220, 170)
    };

    for (int i = 0; i < 3; i++)
    {
        sf::RectangleShape button({130.f, 65.f});
        button.setPosition({125.f + i * 200.f, 130.f});
        button.setFillColor(colors[i]);
        button.setOutlineThickness(4.f);

        if (game.boardTheme == i) button.setOutlineColor(sf::Color::Red);
        else button.setOutlineColor(sf::Color(75, 45, 20));

        sf::Text text(font, names[i], 20);
        float textWidth = text.getLocalBounds().size.x;
        text.setPosition({125.f + i * 200.f + (130.f - textWidth) / 2.f, 150.f});
        text.setFillColor(i == 1 ? sf::Color::White : sf::Color(40, 30, 20));

        w.draw(button);
        w.draw(text);
    }
}
void UI::drawStoneTheme(sf::RenderWindow &w, sf::Font &font, Game &game)
{
    sf::Text title(font, "STONE THEME", 25);
    title.setPosition({300.f, 210.f});
    title.setFillColor(sf::Color(40, 30, 20));
    w.draw(title);

    string names[2] = {"CLASSIC", "CARTOON"};

    sf::Color colors[3] =
    {
        sf::Color(220, 179, 92),
        sf::Color(220, 179, 92),
    };

    for (int i = 0; i < 2; i++)
    {
        sf::RectangleShape button({140.f, 90.f});
        button.setPosition({220.f + i * 200.f, 260.f});
        button.setFillColor(colors[i]);
        button.setOutlineThickness(4.f);

        if (game.stoneTheme == i) button.setOutlineColor(sf::Color::Red);
        else button.setOutlineColor(sf::Color(75, 45, 20));

        w.draw(button);

        if (i == 0)
        {
            sf::CircleShape blackStone(30.f);
            blackStone.setOrigin({30.f, 30.f});
            blackStone.setPosition({270.f, 305.f});
            blackStone.setFillColor(sf::Color(25, 25, 25));
            blackStone.setOutlineThickness(1.f);
            blackStone.setOutlineColor(sf::Color(70, 70, 70));

            sf::CircleShape whiteStone(30.f);
            whiteStone.setOrigin({30.f, 30.f});
            whiteStone.setPosition({310.f, 305.f});
            whiteStone.setFillColor(sf::Color(250, 250, 250));
            whiteStone.setOutlineThickness(1.f);
            whiteStone.setOutlineColor(sf::Color(150, 150, 150));

            w.draw(blackStone);
            w.draw(whiteStone);
        }
        else if (i == 1)
        {
            sf::Sprite fire(fireTexture);

            sf::Vector2f fireSize = fire.getLocalBounds().size;
            fire.setOrigin(fireSize / 2.f);
            fire.setScale({
                65.f / fireSize.x,
                65.f / fireSize.y
            });
            fire.setPosition({470.f, 305.f});

            sf::Sprite water(waterTexture);

            sf::Vector2f waterSize = water.getLocalBounds().size;
            water.setOrigin(waterSize / 2.f);
            water.setScale({
                65.f / waterSize.x,
                65.f / waterSize.y
            });
            water.setPosition({510.f, 305.f});

            w.draw(fire);
            w.draw(water);
        }

        sf::Text text(font, names[i], 20);
        float textWidth = text.getLocalBounds().size.x;
        text.setPosition({220.f + i * 200.f + (140.f - textWidth) / 2.f, 360.f});
        text.setFillColor(sf::Color(40, 30, 20));

        w.draw(text);
    }
}
void UI::drawSoundSettings(sf::RenderWindow &w, sf::Font &font, Game &game)
{
    sf::Text title(font, "SOUND EFFECTS", 25);
    title.setPosition({10.f, 410.f});
    title.setFillColor(sf::Color(40, 30, 20));
    w.draw(title);

    sf::RectangleShape toggle({100.f, 45.f});
    toggle.setPosition({290.f, 405.f});
    toggle.setOutlineThickness(2.f);
    toggle.setOutlineColor(sf::Color(75, 45, 20));

    if (game.soundEnabled) toggle.setFillColor(sf::Color(80, 160, 90));
    else toggle.setFillColor(sf::Color(130, 130, 130));

    w.draw(toggle);

    sf::Text toggleText(font, game.soundEnabled ? "ON" : "OFF", 20);
    float toggleWidth = toggleText.getLocalBounds().size.x;
    toggleText.setPosition({290.f + (100.f - toggleWidth) / 2.f, 415.f});
    toggleText.setFillColor(sf::Color::White);
    w.draw(toggleText);

    for (int i = 0; i < 10; i++)
    {
        sf::RectangleShape block({25.f, 35.f});
        block.setPosition({455.f + i * 27.f, 405.f});

        if (i < game.soundVolume / 10.f) block.setFillColor(sf::Color(80, 160, 90));
        else block.setFillColor(sf::Color(190, 190, 190));

        block.setOutlineThickness(1.f);
        block.setOutlineColor(sf::Color(75, 45, 20));

        w.draw(block);
    }
}
void UI::drawMusicSettings(sf::RenderWindow &w, sf::Font &font, Game &game)
{
    sf::Text title(font, "BACKGROUND MUSIC", 25);
    title.setPosition({10.f, 490.f});
    title.setFillColor(sf::Color(40, 30, 20));
    w.draw(title);

    sf::RectangleShape toggle({100.f, 45.f});
    toggle.setPosition({290.f, 485.f});
    toggle.setOutlineThickness(2.f);
    toggle.setOutlineColor(sf::Color(75, 45, 20));

    if (game.musicEnabled) toggle.setFillColor(sf::Color(80, 160, 90));
    else toggle.setFillColor(sf::Color(130, 130, 130));

    w.draw(toggle);

    sf::Text toggleText(font, game.musicEnabled ? "ON" : "OFF", 20);
    float toggleWidth = toggleText.getLocalBounds().size.x;
    toggleText.setPosition({290.f + (100.f - toggleWidth) / 2.f, 495.f});
    toggleText.setFillColor(sf::Color::White);
    w.draw(toggleText);

    for (int i = 0; i < 10; i++)
    {
        sf::RectangleShape block({25.f, 35.f});
        block.setPosition({455.f + i * 27.f, 485.f});

        if (i < game.musicVolume / 10.f) block.setFillColor(sf::Color(80, 160, 90));
        else block.setFillColor(sf::Color(190, 190, 190));

        block.setOutlineThickness(1.f);
        block.setOutlineColor(sf::Color(75, 45, 20));

        w.draw(block);
    }
}
void UI::drawBoard(sf::RenderWindow &w, sf::Font &font, Game &game)
{
    float cell = 30.f;
    float x0 = 50.f;
    float y0 = 50.f;

    sf::RectangleShape bg(sf::Vector2f(590.f, 590.f));
    bg.setPosition(sf::Vector2f(20.f, 20.f));
    if (game.boardTheme == 0) bg.setFillColor(sf::Color(220, 179, 92));
    else if (game.boardTheme == 1) bg.setFillColor(sf::Color(110, 75, 45));
    else if (game.boardTheme == 1) bg.setFillColor(sf::Color(240, 220, 170));
    w.draw(bg);

    for (int i = 0; i < N; i++)
    {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(x0, y0 + i * cell), sf::Color::Black),
            sf::Vertex(sf::Vector2f(x0 + (N - 1) * cell, y0 + i * cell), sf::Color::Black)
        };
        w.draw(line, 2, sf::PrimitiveType::Lines);

        sf::Vertex line2[] = {
            sf::Vertex(sf::Vector2f(x0 + i * cell, y0), sf::Color::Black),
            sf::Vertex(sf::Vector2f(x0 + i * cell, y0 + (N - 1) * cell), sf::Color::Black)
        };
        w.draw(line2, 2, sf::PrimitiveType::Lines);
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (game.board.a[i][j] == 0)
                continue;

            float x = x0 + j * cell;
            float y = y0 + i * cell;
            if (game.stoneTheme == 0)
            {            
                sf::CircleShape stone(cell * 0.42f);
                stone.setOrigin(sf::Vector2f(cell * 0.42f, cell * 0.42f));
                stone.setPosition({x, y});

                if (game.board.a[i][j] == 1) stone.setFillColor(sf::Color::Black);
                else stone.setFillColor(sf::Color::White);

                stone.setOutlineThickness(1.f);
                stone.setOutlineColor(sf::Color(60, 60, 60));
                w.draw(stone);
            }
            else if (game.stoneTheme == 1)
            {
                sf::Sprite stone(game.board.a[i][j] == 1 ? fireTexture : waterTexture);
                sf::Vector2f size = stone.getLocalBounds().size;

                stone.setOrigin(size / 2.f);
                float scale = (cell * 0.95f) / std::max(size.x, size.y);
                stone.setScale({scale, scale});
                stone.setPosition({x, y});

                w.draw(stone);
            }
        }
    }

    if (game.highlight.fi != -1 && game.highlight.se != -1)
    {
        int i = game.highlight.fi;
        int j = game.highlight.se;
        sf::CircleShape mark(4.f);
        mark.setOrigin(sf::Vector2f(4.f, 4.f));
        mark.setPosition(sf::Vector2f(x0 + j * cell, y0 + i * cell));
        mark.setFillColor(sf::Color::Red);
        w.draw(mark);
    }

    //BACK TO MENU
    sf::RectangleShape backButton({100.f, 45.f});
    backButton.setPosition({30.f, 730.f});
    backButton.setFillColor(sf::Color(245, 222, 179));
    backButton.setOutlineThickness(2.f);
    backButton.setOutlineColor(sf::Color(75, 45, 20));

    sf::Text backText(font, "MENU", 20);
    backText.setPosition({55.f, 740.f});
    backText.setFillColor(sf::Color::Black);

    w.draw(backButton);
    w.draw(backText);

    //RESTART GAME
    sf::RectangleShape restartButton({100.f, 45.f});
    restartButton.setPosition({140.f, 730.f});
    restartButton.setFillColor(sf::Color(245, 222, 179));
    restartButton.setOutlineThickness(2.f);
    restartButton.setOutlineColor(sf::Color(75, 45, 20));

    sf::Text restartText(font, "RESTART", 20);
    restartText.setPosition({145.f, 740.f});
    restartText.setFillColor(sf::Color::Black);

    w.draw(restartButton);
    w.draw(restartText);

    //UNDO
    sf::RectangleShape undoButton({100.f, 45.f});
    undoButton.setPosition({655.f, 30.f});
    undoButton.setFillColor(sf::Color(245, 222, 179));
    undoButton.setOutlineThickness(2.f);
    undoButton.setOutlineColor(sf::Color(75, 45, 20));

    sf::Text undoText(font, "UNDO", 20);
    undoText.setPosition({675.f, 40.f});
    undoText.setFillColor(sf::Color::Black);

    w.draw(undoButton);
    w.draw(undoText);

    //REDO
    sf::RectangleShape redoButton({100.f, 45.f});
    redoButton.setPosition({655.f, 90.f});
    redoButton.setFillColor(sf::Color(245, 222, 179));
    redoButton.setOutlineThickness(2.f);
    redoButton.setOutlineColor(sf::Color(75, 45, 20));

    sf::Text redoText(font, "REDO", 20);
    redoText.setPosition({675.f, 100.f});
    redoText.setFillColor(sf::Color::Black);

    w.draw(redoButton);
    w.draw(redoText);

    //SAVEGAME
    sf::RectangleShape savegameButton({100.f, 45.f});
    savegameButton.setPosition({655.f, 150.f});
    savegameButton.setFillColor(sf::Color(245, 222, 179));
    savegameButton.setOutlineThickness(2.f);
    savegameButton.setOutlineColor(sf::Color(75, 45, 20));

    sf::Text savegameText(font, "SAVE", 20);
    savegameText.setPosition({680.f, 160.f});
    savegameText.setFillColor(sf::Color::Black);

    w.draw(savegameButton);
    w.draw(savegameText);

    //LOADGAME
    sf::RectangleShape loadgameButton({100.f, 45.f});
    loadgameButton.setPosition({655.f, 210.f});
    loadgameButton.setFillColor(sf::Color(245, 222, 179));
    loadgameButton.setOutlineThickness(2.f);
    loadgameButton.setOutlineColor(sf::Color(75, 45, 20));

    sf::Text loadgameText(font, "LOAD", 20);
    loadgameText.setPosition({680.f, 220.f});
    loadgameText.setFillColor(sf::Color::Black);

    w.draw(loadgameButton);
    w.draw(loadgameText);

    //TURN
    sf::RectangleShape turnButton({100.f, 120.f});
    turnButton.setPosition({655.f, 270.f});
    turnButton.setFillColor(sf::Color(245, 222, 179));
    turnButton.setOutlineThickness(2.f);
    turnButton.setOutlineColor(sf::Color(75, 45, 20));

    sf::Text turnText(font, "TURN", 20);
    turnText.setPosition({678.f, 280.f});
    turnText.setFillColor(sf::Color::Black);

    w.draw(turnButton);
    w.draw(turnText);

    if (game.stoneTheme == 0)
    {
        if (3 - game.turn == 1)
        {
            sf::CircleShape blackStone(30.f);
            blackStone.setOrigin({30.f, 30.f});
            blackStone.setPosition({705.f, 343.f});
            blackStone.setFillColor(sf::Color(25, 25, 25));
            blackStone.setOutlineThickness(1.f);
            blackStone.setOutlineColor(sf::Color(70, 70, 70));
            w.draw(blackStone);
        }
        else 
        {
            sf::CircleShape whiteStone(30.f);
            whiteStone.setOrigin({30.f, 30.f});
            whiteStone.setPosition({705.f, 343.f});
            whiteStone.setFillColor(sf::Color(250, 250, 250));
            whiteStone.setOutlineThickness(1.f);
            whiteStone.setOutlineColor(sf::Color(150, 150, 150));
            w.draw(whiteStone);
        }
    }
    else
    {
        if (3 - game.turn == 1)
        {
            sf::Sprite fire(fireTexture);
            sf::Vector2f fireSize = fire.getLocalBounds().size;
            fire.setOrigin(fireSize / 2.f);
            fire.setScale({
                65.f / fireSize.x,
                65.f / fireSize.y
            });
            fire.setPosition({705.f, 343.f});
            w.draw(fire);
        }
        else 
        {
            sf::Sprite water(waterTexture);
            sf::Vector2f waterSize = water.getLocalBounds().size;
            water.setOrigin(waterSize / 2.f);
            water.setScale({
                65.f / waterSize.x,
                65.f / waterSize.y
            });
            water.setPosition({705.f, 343.f});
            w.draw(water);
        }
    }    

    //PASS
    sf::RectangleShape passturnButton({100.f, 45.f});
    passturnButton.setPosition({655.f, 405.f});
    passturnButton.setFillColor(sf::Color(245, 222, 179));
    passturnButton.setOutlineThickness(2.f);
    passturnButton.setOutlineColor(sf::Color(75, 45, 20));

    sf::Text passturnText(font, "PASS TURN", 17);
    passturnText.setPosition({658.f, 415.f});
    passturnText.setFillColor(sf::Color::Black);

    w.draw(passturnButton);
    w.draw(passturnText);
}
void UI::drawNotification(sf::RenderWindow &w, sf::Font &font, bool check, bool type)
{
    string str;
    if (type == 0)
    {
        str = "SAVED";
        if (!check) str = "SAVE";
    }
    else 
    {
        str = "LOADED";
        if (!check) str = "LOAD";
    }
    if (check) str += " SUCCESSFULLY";
    else str += " FAILED";
    sf::Text NofiText(font, str, 30);
    NofiText.setPosition({200.f, 650.f});
    NofiText.setFillColor(sf::Color::White);
    w.draw(NofiText);
}
void UI::drawMenu(sf::RenderWindow &w, sf::Font &font)
{
    sf::RectangleShape background(sf::Vector2f(800.f, 800.f));
    background.setPosition(sf::Vector2f(0.f, 0.f));
    background.setFillColor(sf::Color(243, 235, 221));
   
    sf::Text title(font, "GO GAME", 52);
    title.setPosition(sf::Vector2f(275.f, 100.f));
    title.setFillColor(sf::Color(45, 30, 15));

    sf::RectangleShape button1(sf::Vector2f(320.f, 75.f));
    button1.setPosition(sf::Vector2f(240.f, 300.f));
    button1.setFillColor(sf::Color(245, 222, 179));
    button1.setOutlineThickness(3.f);
    button1.setOutlineColor(sf::Color(75, 45, 20));

    sf::Text text1(font, "PLAYER VS PLAYER", 25);
    text1.setPosition(sf::Vector2f(280.f, 320.f));
    text1.setFillColor(sf::Color(40, 30, 20));

    sf::RectangleShape button2(sf::Vector2f(320.f, 75.f));
    button2.setPosition(sf::Vector2f(240.f, 410.f));
    button2.setFillColor(sf::Color(245, 222, 179));
    button2.setOutlineThickness(3.f);
    button2.setOutlineColor(sf::Color(75, 45, 20));

    sf::Text text2(font, "PLAYER VS BOT", 25);
    text2.setPosition(sf::Vector2f(302.f, 430.f));
    text2.setFillColor(sf::Color(40, 30, 20));

    sf::RectangleShape button3(sf::Vector2f(320.f, 75.f));
    button3.setPosition(sf::Vector2f(240.f, 520.f));
    button3.setFillColor(sf::Color(245, 222, 179));
    button3.setOutlineThickness(3.f);
    button3.setOutlineColor(sf::Color(75, 45, 20));

    sf::Text text3(font, "SETTING", 25);
    text3.setPosition(sf::Vector2f(340.f, 540.f));
    text3.setFillColor(sf::Color(40, 30, 20));

    sf::RectangleShape button4(sf::Vector2f(320.f, 75.f));
    button4.setPosition(sf::Vector2f(240.f, 630.f));
    button4.setFillColor(sf::Color(245, 179, 179));
    button4.setOutlineThickness(3.f);
    button4.setOutlineColor(sf::Color(75, 45, 20));

    sf::Text text4(font, "EXIT GAME", 25);
    text4.setPosition(sf::Vector2f(330.f, 650.f));
    text4.setFillColor(sf::Color(40, 30, 20));

    w.draw(background);
    w.draw(title);
    w.draw(button1); w.draw(text1);
    w.draw(button2); w.draw(text2);
    w.draw(button3); w.draw(text3);
    w.draw(button4); w.draw(text4);
}
void UI::drawDifficultyMenu(sf::RenderWindow &w, sf::Font &font)
{
    sf::RectangleShape background(sf::Vector2f(800.f, 800.f));
    background.setPosition(sf::Vector2f(0.f, 0.f));
    background.setFillColor(sf::Color(243, 235, 221));

    sf::RectangleShape button1(sf::Vector2f(320.f, 75.f));
    button1.setPosition(sf::Vector2f(240.f, 290.f));
    button1.setFillColor(sf::Color(245, 222, 179));
    button1.setOutlineThickness(3.f);
    button1.setOutlineColor(sf::Color(75, 45, 20));

    sf::Text text1(font, "EASY", 25);
    text1.setPosition(sf::Vector2f(365.f, 312.f));
    text1.setFillColor(sf::Color(40, 30, 20));

    sf::RectangleShape button2(sf::Vector2f(320.f, 75.f));
    button2.setPosition(sf::Vector2f(240.f, 395.f));
    button2.setFillColor(sf::Color(245, 222, 179));
    button2.setOutlineThickness(3.f);
    button2.setOutlineColor(sf::Color(75, 45, 20));

    sf::Text text2(font, "MEDIUM", 25);
    text2.setPosition(sf::Vector2f(345.f, 417.f));
    text2.setFillColor(sf::Color(40, 30, 20));

    sf::RectangleShape button3(sf::Vector2f(320.f, 75.f));
    button3.setPosition(sf::Vector2f(240.f, 500.f));
    button3.setFillColor(sf::Color(245, 222, 179));
    button3.setOutlineThickness(3.f);
    button3.setOutlineColor(sf::Color(75, 45, 20));

    sf::Text text3(font, "HARD", 25);
    text3.setPosition(sf::Vector2f(365.f, 522.f));
    text3.setFillColor(sf::Color(40, 30, 20));

    w.draw(background);
    w.draw(button1); w.draw(text1);
    w.draw(button2); w.draw(text2);
    w.draw(button3); w.draw(text3);
    drawBackbutton(w, font);
}
void UI::drawGameover(sf::RenderWindow &w, sf::Font &font, Game &game)
{
    sf::RectangleShape background(sf::Vector2f(800.f, 800.f));
    background.setPosition(sf::Vector2f(0.f, 0.f));
    background.setFillColor(sf::Color(243, 235, 221));
    w.draw(background);
}
#include "UI.h"
#include "Game.h"
#include <cstring>
#include <SFML/Graphics.hpp>
#define fi first 
#define se second 
using pii = pair<int, int>;
using namespace std;
UI::UI()
{
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
    // drawStoneTheme(w, font, game);
    // drawSoundSettings(w, font, game);
    // drawMusicSettings(w, font, game);
}
void UI::drawBoardTheme(sf::RenderWindow &w, sf::Font &font, Game &game)
{
    sf::Text title(font, "BOARD COLOR", 25);
    title.setPosition({250.f, 180.f});
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
        button.setPosition({105.f + i * 200.f, 250.f});
        button.setFillColor(colors[i]);
        button.setOutlineThickness(4.f);

        if (game.boardTheme == i) button.setOutlineColor(sf::Color::Red);
        else button.setOutlineColor(sf::Color(75, 45, 20));

        sf::Text text(font, names[i], 20);
        text.setPosition({125.f + i * 200.f, 270.f});
        text.setFillColor(i == 1 ? sf::Color::White : sf::Color(40, 30, 20));

        w.draw(button);
        w.draw(text);
    }
}
void UI::drawStoneTheme(sf::RenderWindow &w, sf::Font &font, Game &game)
{

}
void UI::drawSoundSettings(sf::RenderWindow &w, sf::Font &font, Game &game)
{

}
void UI::drawMusicSettings(sf::RenderWindow &w, sf::Font &font, Game &game)
{

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

            sf::CircleShape stone(cell * 0.42f);
            stone.setOrigin(sf::Vector2f(cell * 0.42f, cell * 0.42f));
            stone.setPosition(sf::Vector2f(x0 + j * cell, y0 + i * cell));

            if (game.board.a[i][j] == 1) stone.setFillColor(sf::Color::Black);
            else stone.setFillColor(sf::Color::White);

            stone.setOutlineThickness(1.f);
            stone.setOutlineColor(sf::Color(60, 60, 60));
            w.draw(stone);
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
    text2.setPosition(sf::Vector2f(295.f, 430.f));
    text2.setFillColor(sf::Color(40, 30, 20));

    sf::RectangleShape button3(sf::Vector2f(320.f, 75.f));
    button3.setPosition(sf::Vector2f(240.f, 520.f));
    button3.setFillColor(sf::Color(245, 222, 179));
    button3.setOutlineThickness(3.f);
    button3.setOutlineColor(sf::Color(75, 45, 20));

    sf::Text text3(font, "SETTING", 25);
    text3.setPosition(sf::Vector2f(340.f, 540.f));
    text3.setFillColor(sf::Color(40, 30, 20));

    w.draw(background);
    w.draw(title);
    w.draw(button1); w.draw(text1);
    w.draw(button2); w.draw(text2);
    w.draw(button3); w.draw(text3);
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
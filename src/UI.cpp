#include "UI.h"
#include "Game.h"
#include <cstring>
#include <SFML/Graphics.hpp>
using namespace std;

UI::UI()
{
}
void UI::drawMenu(sf::RenderWindow &w, sf::Font &font)
{

}
void UI::drawBoard(sf::RenderWindow &w, sf::Font &font, Game &game)
{
    float cell = 30.f;
    float x0 = 50.f;
    float y0 = 50.f;

    sf::RectangleShape bg(sf::Vector2f(590.f, 590.f));
    bg.setPosition(sf::Vector2f(20.f, 20.f));
    bg.setFillColor(sf::Color(220, 179, 92));
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

            if (game.board.a[i][j] == 1)
                stone.setFillColor(sf::Color::Black);
            else
                stone.setFillColor(sf::Color::White);

            stone.setOutlineThickness(1.f);
            stone.setOutlineColor(sf::Color(60, 60, 60));
            w.draw(stone);
        }
    }
}
void UI::drawDifficultyMenu(sf::RenderWindow &w, sf::Font &font)
{
    sf::RectangleShape background(sf::Vector2f(800.f, 800.f));
    background.setPosition(sf::Vector2f(0.f, 0.f));
    background.setFillColor(sf::Color(220, 179, 92));
   
    sf::Text title(font, "GO GAME", 52);
    title.setPosition(sf::Vector2f(250.f, 100.f));
    title.setFillColor(sf::Color(45, 30, 15));

    w.draw(background);
    w.draw(title);
}
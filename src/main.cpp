#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Game.h"
#include "UI.h"
#include "AI.h"
#include <algorithm>
#include <iostream>
#include <chrono>
#include <thread>
using namespace std;
int screen = 0;
// 0 : menu
// 1 : setting
// 2 : difficulty menu
// 3 : board
Game game;
UI ui;
AI ai;
void BoardOperation(sf::RenderWindow &w, sf::Font &font, const sf::Event* event)
{
    w.clear(sf::Color(40, 40, 40));
    ui.drawBoard(w, font, game);
    w.display();
    if (const auto* m = event->getIf<sf::Event::MouseButtonPressed>())
    {
        if (m->button == sf::Mouse::Button::Left)
        {
            sf::Vector2f pos = w.mapPixelToCoords(m->position);

            float x0 = 50.f;
            float y0 = 50.f;
            float cell = 30.f;

            int j = static_cast<int>((pos.x - x0 + cell / 2) / cell);
            int i = static_cast<int>((pos.y - y0 + cell / 2) / cell);

            if (i >= 0 && i < N && j >= 0 && j < N && game.board.a[i][j] == 0)
            {
                if (game.mode == 2)
                {
                    if (!game.completeMove(game.board, i, j, 1, 0))
                    return;

                    game.highlight = {i, j};
                    w.clear(sf::Color(40, 40, 40));
                    ui.drawBoard(w, font, game);
                    w.display();
                    game.undoStack.push({game.board, game.passCount});

                    this_thread::sleep_for(chrono::milliseconds(50));
                    game.highlight = ai.makemove(game.board, 2, game.difficult, game);
                    //                                    turn, dif
                    game.undoStack.push({game.board, game.passCount});
                }
                else 
                {
                    if (!game.completeMove(game.board, i, j, 3 - game.turn, 0))
                    return;
                    game.turn = 3 - game.turn;
                    game.highlight = {i, j};
                    w.clear(sf::Color(40, 40, 40));
                    ui.drawBoard(w, font, game);
                    w.display();
                    game.undoStack.push({game.board, game.passCount});
                }
            }
            else if (sf::FloatRect({30.f, 730.f}, {100.f, 45.f}).contains(pos))
            {
                game.reset();
                screen = 0;
                return;
            }
        }
    }
}
void MenuOperation(sf::RenderWindow &w, sf::Font &font, const sf::Event* event)
{
    w.clear(sf::Color(40, 40, 40));
    ui.drawMenu(w, font);
    w.display();
    if (const auto* m = event->getIf<sf::Event::MouseButtonPressed>())
    {
        if (m->button == sf::Mouse::Button::Left)
        {
            sf::Vector2f pos = w.mapPixelToCoords(m->position);

            if (sf::FloatRect({240.f, 300.f}, {320.f, 75.f}).contains(pos))
            {
                screen = 3;
                game.mode = 1;
            }
            else if (sf::FloatRect({240.f, 410.f}, {320.f, 75.f}).contains(pos))
            {
                screen = 2;
                game.mode = 2;
            }
            else if (sf::FloatRect({240.f, 520.f}, {320.f, 75.f}).contains(pos))
            {
                screen = 1;
            }
        }
    }
}
void DifficultymenuOperation(sf::RenderWindow &w, sf::Font &font, const sf::Event* event)
{
    w.clear(sf::Color(40, 40, 40));
    ui.drawDifficultyMenu(w, font);
    w.display();
    if (const auto* m = event->getIf<sf::Event::MouseButtonPressed>())
    {
        if (m->button == sf::Mouse::Button::Left)
        {
            sf::Vector2f pos = w.mapPixelToCoords(m->position);

            if (sf::FloatRect({240.f, 290.f}, {320.f, 75.f}).contains(pos))
            {
                screen = 3;
                game.difficult = 1;
            }
            else if (sf::FloatRect({240.f, 395.f}, {320.f, 75.f}).contains(pos))
            {
                screen = 3;
                game.difficult = 2;
            }
            else if (sf::FloatRect({240.f, 500.f}, {320.f, 75.f}).contains(pos))
            {
                screen = 3;
                game.difficult = 3;
            }
            else if (sf::FloatRect({30.f, 25.f}, {100.f, 45.f}).contains(pos))
            {
                screen = 0;
            }
        }
    }
}
void SettingOperation(sf::RenderWindow &w, sf::Font &font, const sf::Event* event)
{
    w.clear(sf::Color(40, 40, 40));
    ui.drawSetting(w, font, game);
    w.display();
    if (const auto* m = event->getIf<sf::Event::MouseButtonPressed>())
    {
        if (m->button == sf::Mouse::Button::Left)
        {
            sf::Vector2f pos = w.mapPixelToCoords(m->position);

            if (sf::FloatRect({125.f + 0 * 200.f, 130.f}, {130.f, 65.f}).contains(pos))
            {
                game.boardTheme = 0;
            }
            else if (sf::FloatRect({125.f + 1 * 200.f, 130.f}, {130.f, 65.f}).contains(pos))
            {
                game.boardTheme = 1;
            }
            else if (sf::FloatRect({125.f + 2 * 200.f, 130.f}, {130.f, 65.f}).contains(pos))
            {
                game.boardTheme = 2;
            }
            else if (sf::FloatRect({220.f + 0 * 200.f, 260.f}, {140.f, 90.f}).contains(pos))
            {
                game.stoneTheme = 0;
            }
            else if (sf::FloatRect({220.f + 1 * 200.f, 260.f}, {140.f, 90.f}).contains(pos))
            {
                game.stoneTheme = 1;
            }
            else if (sf::FloatRect({30.f, 25.f}, {100.f, 45.f}).contains(pos))
            {
                screen = 0;
            }
        }
    }
}
int main()
{
    srand(time(0));
    sf::Font font;
    if (!font.openFromFile("C:/Windows/Fonts/arial.ttf")) return 1;
    sf::RenderWindow w(sf::VideoMode({800u, 800u}), "Go Game");
    sf::View view(sf::FloatRect({0.f, 0.f}, {800.f, 800.f}));
    auto resizeView = [&]()
    {
        auto sz = w.getSize();
        float r = (float)sz.x / sz.y;
        float vx = 0, vy = 0, vw = 1, vh = 1;
        if (r > 1) { vw = 1 / r; vx = (1 - vw) / 2; }
        else { vh = r; vy = (1 - vh) / 2; }
        view.setViewport(sf::FloatRect({vx, vy}, {vw, vh}));
        w.setView(view);
    };
    resizeView();
    while (w.isOpen())
    {
        while (const std::optional event = w.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            w.close();

            if (event->is<sf::Event::Resized>())
            resizeView();

            if (screen == 0)
                MenuOperation(w, font, &(*event));
            else
            if (screen == 1)
                SettingOperation(w, font, &(*event));
            else
            if (screen == 2)
                DifficultymenuOperation(w, font, &(*event));
            else
            if (screen == 3)
                BoardOperation(w, font, &(*event));
        }
    }
}
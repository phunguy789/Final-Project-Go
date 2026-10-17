#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Game.h"
#include "UI.h"
#include "AI.h"
#include <algorithm>
using namespace std;
int screen = 0;
Game game;
UI ui;
int main()
{
    srand(time(0));
    game.reset();
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
        while (const auto e = w.pollEvent())
        {
            if (e->is<sf::Event::Closed>()) w.close();
            if (e->is<sf::Event::Resized>()) resizeView();
            if (const auto *m = e->getIf<sf::Event::MouseButtonPressed>())
            {
                if (m->button == sf::Mouse::Button::Left)
                {
                    sf::Vector2f p = w.mapPixelToCoords(m->position);
                    float x = p.x, y = p.y;
                    if (screen == 0)
                    {
                        if (x >= 250 && x <= 550 && y >= 280 && y <= 340)
                        {
                            game.mode = 1;
                            game.reset();
                            screen = 1;
                        }
                        else if (x >= 250 && x <= 550 && y >= 370 && y <= 430)
                        {
                            game.mode = 2;
                            screen = 2;
                        }
                        else if (x >= 250 && x <= 550 && y >= 460 && y <= 520)
                            w.close();
                    }
                    else if (screen == 1)
                    {
                        if (x >= 240 && x <= 390 && y >= 730 && y <= 775)
                            game.reset();
                        else if (x >= 410 && x <= 560 && y >= 730 && y <= 775)
                        {
                            game.reset();
                            screen = 0;
                        }
                        else if (!game.gameover)
                        {
                            float c = 40.f, bx = 100.f, by = 100.f;
                            if (x >= bx && x < bx + c * 15 && y >= by && y < by + c * 15)
                            {
                                int i = (y - by) / c;
                                int j = (x - bx) / c;
                                game.playmove(i, j);
                            }
                        }
                    }
                    else if (screen == 2)
                    {
                        if (x >= 250 && x <= 550 && y >= 250 && y <= 310)
                        {
                            game.difficult = 1;
                            game.reset();
                            screen = 1;
                        }
                        else if (x >= 250 && x <= 550 && y >= 340 && y <= 400)
                        {
                            game.difficult = 2;
                            game.reset();
                            screen = 1;
                        }
                        else if (x >= 250 && x <= 550 && y >= 430 && y <= 490)
                        {
                            game.difficult = 3;
                            game.reset();
                            screen = 1;
                        }
                        else if (x >= 250 && x <= 550 && y >= 530 && y <= 580)
                            screen = 0;
                    }
                }
            }
            if (const auto *k = e->getIf<sf::Event::KeyPressed>())
            {
                if (k->code == sf::Keyboard::Key::Escape)
                {
                    if (screen == 1 || screen == 2) screen = 0;
                    else w.close();
                }
                if (k->code == sf::Keyboard::Key::R && screen == 1)
                    game.reset();
            }
        }
        if (screen == 0) ui.drawMenu(w, font);
        else if (screen == 2) ui.drawDifficultyMenu(w, font);
        else ui.drawBoard(w, font, game);
    }
}
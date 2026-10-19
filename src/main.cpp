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
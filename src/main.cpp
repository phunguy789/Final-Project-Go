#include <SFML/Graphics.hpp>
int main()
{
    sf::RenderWindow window(sf::VideoMode({800,600}),"Caro Game");
    while(window.isOpen())
    {
        while(const auto e=window.pollEvent())
            if(e->is<sf::Event::Closed>()) window.close();
        window.clear(sf::Color::Yellow);
        window.display();
    }
    return 0;
}
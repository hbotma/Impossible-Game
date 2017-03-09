#include "Menu.hpp"
#include "Game.hpp"
#include "Creator.hpp"

///////////////////////////
///////////////////////////

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(WINDOWX, WINDOWY), "The Impossible Game", sf::Style::Close, settings);
    window.setKeyRepeatEnabled(false);

    std::ifstream fin;
    fin.open("Map.txt");
    Game game(fin);

    while (window.isOpen())
    {
        sf::Event event;
        game.processEvents(window, event);
        game.processLogic();
        game.processGraphics(window);
    }

    fin.close();

    return 0;
}

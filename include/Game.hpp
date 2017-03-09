#ifndef GAME_HPP
#define GAME_HPP

#include "Mode.hpp"

class Game
{
public:
    Game(std::ifstream & map);
    ~Game();
    void processEvents(sf::RenderWindow & window, sf::Event & event);
    void processLogic();
    void processGraphics(sf::RenderWindow & window);

private:
    sf::View view;
    sf::RectangleShape player, background, overlay;
    sf::Clock clock;
    sf::Time elapsed;
    sf::Vector2f speed;
    Nonplayer** object;
    bool paused, jumping, gameOver;
    int numObj;
    float winDist;
};

#endif // GAME_HPP

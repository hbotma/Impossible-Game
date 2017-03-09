#ifndef MODE_HPP
#define MODE_HPP

#include "Root.hpp"

class Mode
{
public:
    virtual void processEvents(sf::RenderWindow & window, sf::Event & event) = 0;
    virtual void processLogic() = 0;
    virtual void processGraphics(sf::RenderWindow & window) = 0;
};

#endif // MODE_HPP

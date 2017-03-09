#include "Root.hpp"

/////////////////////
/////////////////////

float floatMod(float num, float modulo)
{
    int x = num/modulo;
    return num - modulo*x;
}

bool rotatedContains(sf::RectangleShape rect, sf::Vector2f point)
{
    float oy = rect.getPosition().y, ox = rect.getPosition().x,
          beta = floatMod(rect.getRotation(), 90) * M_PI/180 + atan2(oy - point.y, point.x - ox),
          r = sqrt((point.x - ox)*(point.x - ox) + (point.y - oy)*(point.y - oy));

    rect.setRotation(0);

    return (rect.getGlobalBounds().contains(ox + r*cos(beta), oy - r*sin(beta)));
}

/////////////////////
/////////////////////

Platform::Platform()
{
    rect.setFillColor(sf::Color::Black);
}

Platform::Platform(sf::Vector2f pos, sf::Vector2f size) : Platform()
{
    this->setPosition(pos);
    rect.setSize(size);
}

sf::FloatRect Platform::getContainer()
{
    return sf::FloatRect(this->getPosition(), rect.getSize());
}

bool Platform::containsPoint(sf::Vector2f point)
{
    return sf::FloatRect(this->getPosition(), rect.getSize()).contains(point);
}

void Platform::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
    states.transform *= this->getTransform();
    target.draw(rect, states);
}

char Platform::getType()
{
    return 'p';
}

/////////////////////
/////////////////////

Spike::Spike()
{
    tri.setPrimitiveType(sf::Triangles);
    tri.resize(3);
    tri[0].position.y = SDIM;
    tri[1].position.x = SDIM/2;
    tri[2].position.x = tri[2].position.y = SDIM;
    tri[0].color = tri[1].color = tri[2].color = sf::Color::Black;
}

Spike::Spike(sf::Vector2f pos) : Spike()
{
    this->setPosition(pos);
}

sf::FloatRect Spike::getContainer()
{
    return sf::FloatRect(this->getPosition(), sf::Vector2f(SDIM, SDIM));
}

bool Spike::containsPoint(sf::Vector2f point)
{
    if (point.y <= this->getPosition().y + SDIM)
        return point.y >= this->getPosition().y + 2*fabs(point.x - (this->getPosition().x + SDIM/2));
    return false;
}

void Spike::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
    states.transform *= this->getTransform();
    target.draw(tri, states);
}

char Spike::getType()
{
    return 's';
}

/////////////////////
/////////////////////

bool checkCollision(sf::RectangleShape & player, Nonplayer* npc)
{
    sf::FloatRect intersection;
    if (player.getGlobalBounds().intersects(npc->getContainer(), intersection));
    {
        for (int x = 0; x < intersection.width; x++)
            for (int y = 0; y < intersection.height; y++)
                if (npc->containsPoint(sf::Vector2f(intersection.left + x, intersection.top + y)) &&
                    rotatedContains(player, sf::Vector2f(intersection.left + x, intersection.top + y)))
                    return true;
    }
    return false;
}

int checkAllCollisions(sf::RectangleShape & player, Nonplayer* object[], int numObj)
{
    for (int i = 0; i < numObj; i++)
        if (checkCollision(player, object[i]))
            return i;
    return -1;
}








#ifndef ROOT_HPP
#define ROOT_HPP

#include "SFML/Graphics.hpp"
#include <iostream>
#include <fstream>
#include <cmath>

/////////////////////
/////////////////////

const float WINDOWX = 600, WINDOWY = 600,
            PDIM = 50, SDIM = 50,
            SPEED = 200, JUMP = 1000, GRAVITY = 2500, ANGVEL = 90;

/////////////////////
/////////////////////

float floatMod(float num, float modulo);
bool rotatedContains(sf::RectangleShape rect, sf::Vector2f point);

/////////////////////
/////////////////////

class Nonplayer : public sf::Drawable, public sf::Transformable
{
public:
    virtual sf::FloatRect getContainer() = 0;
    virtual bool containsPoint(sf::Vector2f point) = 0;
    virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const = 0;
    virtual char getType() = 0;
};

class Platform : public Nonplayer
{
public:
    Platform();
    Platform(sf::Vector2f pos, sf::Vector2f size);
    sf::FloatRect getContainer();
    bool containsPoint(sf::Vector2f point);
    void draw(sf::RenderTarget & target, sf::RenderStates states) const;
    char getType();

private:
    sf::RectangleShape rect;
};

class Spike : public Nonplayer
{
public:
    Spike();
    Spike(sf::Vector2f pos);
    sf::FloatRect getContainer();
    bool containsPoint(sf::Vector2f point);
    void draw(sf::RenderTarget & target, sf::RenderStates states) const;
    char getType();

private:
    sf::VertexArray tri;
};

/////////////////////
/////////////////////

bool checkCollision(sf::RectangleShape & player, Nonplayer* npc);
int checkAllCollisions(sf::RectangleShape & player, Nonplayer* object[], int numObj);

#endif // ROOT_HPP

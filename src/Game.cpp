#include "Game.hpp"

Game::Game(std::ifstream & map)
{
    view.setSize(WINDOWX, WINDOWY);

    player.setSize(sf::Vector2f(PDIM, PDIM));
    player.setOrigin(PDIM/2, PDIM/2);
    player.setPosition(0, 0);
    player.setFillColor(sf::Color::Black);

    background.setSize(sf::Vector2f(WINDOWX, WINDOWY));
    background.setFillColor(sf::Color::White);

    overlay.setSize(sf::Vector2f(WINDOWX, WINDOWY));
    overlay.setFillColor(sf::Color(255, 0, 0, 75));

    map >> winDist >> numObj;
    object = new Nonplayer*[numObj];
    char bufferC;
    float buffer[4] = {0,0,0,0};
    for (int i = 0; i < numObj; i++)
    {
        map >> bufferC >> buffer[0] >> buffer[1];
        if (bufferC == 'p')
        {
            map >> buffer[2] >> buffer[3];
            object[i] = new Platform(sf::Vector2f(buffer[0], buffer[1]), sf::Vector2f(buffer[2], buffer[3]));
        }
        else
            object[i] = new Spike(sf::Vector2f(buffer[0], buffer[1]));
    }

    jumping = false;
    paused = false;
    gameOver = false;

    speed.x = SPEED;
    speed.y = 0;

    clock.restart();
}

Game::~Game()
{
    for (int i = 0; i < numObj; i++)
    {
        delete object[i];
        object[i] = NULL;
    }
    delete object;
    object = NULL;
}

void Game::processEvents(sf::RenderWindow & window, sf::Event & event)
{
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
        else
        {
            if (gameOver)
            {
                if (event.type == sf::Event::KeyPressed)
                {
                    gameOver = false;
                    overlay.setFillColor(sf::Color(255, 0, 0, 75));
                    jumping = false;
                    elapsed = sf::Time::Zero;
                    clock.restart();
                    player.setPosition(0, 0);
                    player.setRotation(0);
                    speed.y = 0;
                }
            }
            else if (!paused)
            {
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space && !jumping)
                {
                    jumping = true;
                    speed.y -= JUMP;
                }
                else if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) ||
                         event.type == sf::Event::LostFocus)
                {
                    paused = true;
                    elapsed += clock.restart();
                }
            }
            else if (sf::Event::KeyPressed)
            {
                paused = false;
                clock.restart();
            }
        }
    }
}

void Game::processLogic()
{
    if (!gameOver && !paused)
    {
        elapsed += clock.restart();

        player.move(speed * elapsed.asSeconds());
        if (jumping)
        {
            speed.y += GRAVITY * elapsed.asSeconds();
            player.rotate(ANGVEL * elapsed.asSeconds());
        }
        else if (fabs(floatMod(player.getRotation(), 90) - 90) > 0.1)
            player.rotate(ANGVEL * 5 * elapsed.asSeconds() * (1 - 2*(floatMod(player.getRotation(), 90) < 45)));

        int coll = checkAllCollisions(player, object, numObj);
        if (coll == -1)
            jumping = true;
        else
        {
            jumping = false;
            speed.y = 0;
            if (object[coll]->getType() == 'p' &&
                object[coll]->getPosition().y - player.getPosition().y >= PDIM/4)
                player.setPosition(player.getPosition().x, object[coll]->getPosition().y - PDIM/2);
            else
                gameOver = true;
        }

        if (player.getPosition().x >= winDist)
        {
            gameOver = true;
            overlay.setFillColor(sf::Color(0, 255, 0, 75));
        }
        else if (player.getPosition().y > WINDOWY)
            gameOver = true;

        elapsed = sf::Time::Zero;
    }
}


void Game::processGraphics(sf::RenderWindow & window)
{
    window.clear();

    window.setView(window.getDefaultView());
    window.draw(background);

    view.setCenter(player.getPosition().x, WINDOWY/2);
    window.setView(view);
    window.draw(player);
    for (int i = 0; i < numObj; i++)
        window.draw(*(object[i]));

    if (gameOver)
    {
        window.setView(window.getDefaultView());
        window.draw(overlay);
    }

    window.display();
}






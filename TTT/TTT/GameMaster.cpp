#include "GameMaster.h"

GameMaster::GameMaster(std::shared_ptr<sf::RenderWindow> iWindow) :
	_window(std::move(iWindow))
{
}

void GameMaster::Run()
{
    _window->setFramerateLimit(60);

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (_window->isOpen())
    {
        sf::Event event;
        while (_window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                _window->close();
        }

        _window->clear();
        _window->draw(shape);
        _window->display();
    }
}

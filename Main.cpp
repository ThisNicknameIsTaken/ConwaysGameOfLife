#include <SFML/Graphics.hpp>
#include "Game.h"

int main(){

	int window_size = 1000;
	

	sf::RenderWindow window(sf::VideoMode(window_size, window_size), "Game Of Life");
	window.setFramerateLimit(15);

	sf::Event event;


	Game game(window_size);
	game.setPosition(0.f, 0.f);

	

	while (window.isOpen())
	{
		game.Logic();
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape) window.close();
				if (event.key.code == sf::Keyboard::P) game.changePause();
				if (event.key.code == sf::Keyboard::C) game.changeColorMode();
			}

			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					game.CheckClick(event.mouseButton.x, event.mouseButton.y,false);
				}

				if (event.mouseButton.button == sf::Mouse::Right)
				{
					game.CheckClick(event.mouseButton.x, event.mouseButton.y,true);
				}
			}			
		}
		window.clear();
		window.draw(game);
		window.display();
	}
	return 0;
}
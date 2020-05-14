#include "SFML/Graphics.hpp"

#include "GameManager.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 800), "Space Invaders", sf::Style::Close);

	GameManager gameManager(window);

	while (window.isOpen())
	{
		gameManager.handleEvents();

		gameManager.update();

		gameManager.render();
	}

	return 0;
}
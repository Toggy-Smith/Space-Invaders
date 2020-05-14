#pragma once

#include "SFML/Graphics.hpp"

class GameOverManager
{
	private:
		sf::RenderWindow& m_window;

		sf::RectangleShape m_background;

		sf::Font m_font;

		sf::Text m_gameOverText;
		sf::Text m_pressSpaceText;

	public:
		GameOverManager(sf::RenderWindow& window);

		void update();
		void render();
		void reset() { m_gameOver = false; }

		bool m_gameOver = false;
		bool m_reset = false;
};
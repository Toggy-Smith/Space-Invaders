#pragma once

#include "SFML/Graphics.hpp"

#include "GameOverManager.hpp"

#include <string>

class LivesManager
{
	private:
		sf::RenderWindow& m_window;

		GameOverManager& m_gameOverManager;

		sf::Font m_font;
		sf::Text m_text;

	public:
		LivesManager(sf::RenderWindow& window, GameOverManager& gameOverManager);

		void update();
		void render();

		int m_lives = 3;

		void reset() { m_lives = 3; }
};
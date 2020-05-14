#pragma once

#include "SFML/Graphics.hpp"

#include <string>

class ScoreManager
{
	private:
		sf::RenderWindow& m_window;

		sf::Font m_font;
		sf::Text m_text;

	public:
		ScoreManager(sf::RenderWindow& window);

		void update();
		void render();

		int m_score = 0;
		int m_numberDestroyed = 0;

		void reset() { m_score = 0; m_numberDestroyed = 0; }
};
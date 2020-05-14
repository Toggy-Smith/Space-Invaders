#include "ScoreManager.hpp"

ScoreManager::ScoreManager(sf::RenderWindow& window)
	: m_window(window)
{
	m_font.loadFromFile("assets/NotoSans-Bold.ttf");

	m_text.setFont(m_font);
	m_text.setCharacterSize(30);
	m_text.setPosition(sf::Vector2f(18, 18));
}

void ScoreManager::update()
{
	m_text.setString("Score: " + std::to_string(m_score));
}

void ScoreManager::render()
{
	m_window.draw(m_text);
}
#include "LivesManager.hpp"

LivesManager::LivesManager(sf::RenderWindow& window, GameOverManager& gameOverManager)
	: m_window(window), m_gameOverManager(gameOverManager)
{
	m_font.loadFromFile("assets/NotoSans-Bold.ttf");

	m_text.setFont(m_font);
	m_text.setCharacterSize(30);
	m_text.setString("Lives: " + std::to_string(m_lives));
	m_text.setPosition(sf::Vector2f(18, window.getSize().y - m_text.getGlobalBounds().height - 24));
}

void LivesManager::update()
{
	m_text.setString("Lives: " + std::to_string(m_lives));

	if (m_lives == 0)
		m_gameOverManager.m_gameOver = true;
}

void LivesManager::render()
{
	m_window.draw(m_text);
}
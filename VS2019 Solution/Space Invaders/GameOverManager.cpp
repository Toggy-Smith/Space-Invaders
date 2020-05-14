#include "GameOverManager.hpp"

GameOverManager::GameOverManager(sf::RenderWindow& window)
	: m_window(window)
{
	m_background.setFillColor(sf::Color::Blue);
	m_background.setSize(sf::Vector2f((float)window.getSize().x / 2, (float)window.getSize().y / 2));
	m_background.setPosition(sf::Vector2f((float)window.getSize().x / 2 - m_background.getSize().x / 2, (float)window.getSize().y / 2 - m_background.getSize().y / 2));

	m_font.loadFromFile("assets/NotoSans-Bold.ttf");

	m_gameOverText.setFont(m_font);
	m_gameOverText.setString("Game over!");
	m_gameOverText.setCharacterSize(30);
	m_gameOverText.setPosition(sf::Vector2f(m_background.getPosition().x + m_background.getSize().x / 2 - m_gameOverText.getGlobalBounds().left - m_gameOverText.getGlobalBounds().width / 2, m_background.getPosition().y + m_background.getSize().y / 3 - m_gameOverText.getGlobalBounds().top - m_gameOverText.getGlobalBounds().height / 2));

	m_pressSpaceText.setFont(m_font);
	m_pressSpaceText.setString("Press space to restart");
	m_pressSpaceText.setCharacterSize(30);
	m_pressSpaceText.setPosition(sf::Vector2f(m_background.getPosition().x + m_background.getSize().x / 2 - m_pressSpaceText.getGlobalBounds().left - m_pressSpaceText.getGlobalBounds().width / 2, m_background.getPosition().y + m_background.getSize().y / 3 * 2 - m_pressSpaceText.getGlobalBounds().top - m_pressSpaceText.getGlobalBounds().height / 2));
}

void GameOverManager::update()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && m_gameOver)
	{
		m_gameOver = false;
		m_reset = true;
	}
}

void GameOverManager::render()
{
	if (m_gameOver)
	{
		m_window.draw(m_background);

		m_window.draw(m_gameOverText);
		m_window.draw(m_pressSpaceText);
	}
}
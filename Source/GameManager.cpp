#include "GameManager.hpp"

GameManager::GameManager(sf::RenderWindow& window)
	: m_window(window),
	m_gameOverManager(window),
	m_scoreManager(window),
	m_livesManager(window, m_gameOverManager),
	m_alienManager(window, m_gameOverManager, m_scoreManager, m_bulletManager, m_textureManager),
	m_bunkerManager(window, m_textureManager, m_bulletManager),
	m_bulletManager(window, m_textureManager),
	m_playerEntity(window, m_event, m_textureManager, m_livesManager, m_bulletManager)
{
	m_greenLine.setSize(sf::Vector2f((float) m_window.getSize().x, 3));
	m_greenLine.setFillColor(sf::Color::Green);
	m_greenLine.setPosition(sf::Vector2f(0, m_window.getSize().y - m_greenLine.getSize().y * 20));
}

void GameManager::handleEvents()
{
	while (m_window.pollEvent(m_event))
	{
		if (m_event.type == sf::Event::Closed)
		{
			m_window.close();
		}

		m_playerEntity.handleEvents();
	}
}

void GameManager::update()
{
	float l_elapsedTime = m_updateClock.getElapsedTime().asSeconds();

	if (m_gameOverManager.m_reset)
	{
		m_scoreManager.reset();
		m_livesManager.reset();
		m_alienManager.reset();
		m_bunkerManager.reset();
		m_bulletManager.reset();
		m_playerEntity.reset();

		m_gameOverManager.m_reset = false;
	}

	if (!m_gameOverManager.m_gameOver)
	{
		m_alienManager.update(l_elapsedTime);
		m_bunkerManager.update();
		m_bulletManager.update(l_elapsedTime);
		m_playerEntity.update(l_elapsedTime);
		m_scoreManager.update();
		m_livesManager.update();
	}

	m_gameOverManager.update();

	m_updateClock.restart();
}

void GameManager::render()
{
	m_window.clear();

	m_window.draw(m_greenLine);
	m_alienManager.render();
	m_bunkerManager.render();
	m_bulletManager.render();
	m_playerEntity.render();
	m_scoreManager.render();
	m_livesManager.render();
	m_gameOverManager.render();

	m_window.display();
}
#include "AlienManager.hpp"

AlienManager::AlienManager(sf::RenderWindow& window, GameOverManager& gameOverManager, ScoreManager& scoreManager, BulletManager& bulletManager, TextureManager& textureManager)
	: m_window(window), m_gameOverManager(gameOverManager), m_scoreManager(scoreManager), m_saucer(window, textureManager, scoreManager, bulletManager)
{
	// Load the texture
	textureManager.createTexture("aliens", "assets/aliens.png");

	// Create 5 rows of 11 aliens
	for (int row = 0; row < 5; row++)
	{
		for (int column = 0; column < 11; column++)
		{
			m_aliens.push_back(AlienEntity(m_window, scoreManager, bulletManager, textureManager.getTexture("aliens"), m_position, column, row));
		}
	}
}

void AlienManager::reset()
{
	m_movementClockWaitTime = 0.5f;
	m_position = sf::Vector2f(30, 6);
	m_movementDirection = Direction::RIGHT;

	m_saucer.reset();

	for (unsigned int i = 0; i < m_aliens.size(); i++)
	{
		m_aliens[i].reset();
	}
}
#include <iostream>
void AlienManager::update(const float elapsedTime)
{
	m_movementClockWaitTime = 0.5f - (m_scoreManager.m_numberDestroyed * 0.001f);

	if (m_position.y > 23)
	{
		m_gameOverManager.m_gameOver = true;
	}

	if (m_shootClock.getElapsedTime().asSeconds() >= 1)
	{
		bool l_allAliensDestroyed = true;

		for (int i = 0; i < 10; i++)
		{
			l_allAliensDestroyed = l_allAliensDestroyed && m_aliens[i].getIsDestroyed();
		}

		if (!l_allAliensDestroyed)
		{
			int l_chosenAlienIndex;

			do
			{
				std::random_device l_rd;
				std::mt19937 l_mt(l_rd());
				std::uniform_int_distribution<int> l_dist(0, 10);

				l_chosenAlienIndex = l_dist(l_mt);

			} while (!m_aliens[l_chosenAlienIndex].shoot());
		}
		else
		{
			for (unsigned int i = 0; i < m_aliens.size(); i++)
			{
				m_position = sf::Vector2f(30, 6);
				m_movementDirection = Direction::RIGHT;
				m_aliens[i].reset();
			}
		}

		m_shootClock.restart();
	}

	m_saucer.update(elapsedTime);

	if (m_movementClock.getElapsedTime().asSeconds() >= m_movementClockWaitTime)
	{
		int l_furthestLeftAliveAlienX = 2000;

		for (unsigned int i = 0; i < m_aliens.size(); i++)
		{
			if (!m_aliens[i].getIsDestroyed())
			{
				if (m_aliens[i].getX() < l_furthestLeftAliveAlienX)
				{
					l_furthestLeftAliveAlienX = m_aliens[i].getX();
				}
			}
		}

		int l_furthestRightAliveAlien = 0;

		for (unsigned int i = 0; i < m_aliens.size(); i++)
		{
			if (!m_aliens[i].getIsDestroyed())
			{
				if (m_aliens[i].getRightX() > m_aliens[l_furthestRightAliveAlien].getRightX())
				{
					l_furthestRightAliveAlien = i;
				}
			}
		}

		bool l_reachedLeftSideLimit = m_position.x <= 30 - (l_furthestLeftAliveAlienX - m_position.x);
		bool l_reachedRightSideLimit = m_position.x >= 310 + (m_aliens[0].getSpace() * (10 - l_furthestRightAliveAlien % 11));

		if (l_reachedLeftSideLimit && m_movementDirection == Direction::LEFT)
		{
			m_movementDirection = Direction::RIGHT;

			m_position.y += 1;
		}
		else if (l_reachedRightSideLimit && m_movementDirection == Direction::RIGHT)
		{
			m_movementDirection = Direction::LEFT;

			m_position.y += 1;
		}
		else
		{
			if (m_movementDirection == Direction::LEFT)
				m_position.x -= m_movementAmount;
			else if (m_movementDirection == Direction::RIGHT)
				m_position.x += m_movementAmount;
		}

		m_movementClock.restart();
	}

	for (unsigned int i = 0; i < m_aliens.size(); i++)
	{
		m_aliens[i].update(elapsedTime);
	}
}

void AlienManager::render()
{
	m_saucer.render();

	for (unsigned int i = 0; i < m_aliens.size(); i++)
	{
		m_aliens[i].render();
	}
}
#include "SaucerEntity.hpp"

SaucerEntity::SaucerEntity(sf::RenderWindow& window, TextureManager& textureManager, ScoreManager& scoreManager, BulletManager& bulletManager)
	: m_window(window), m_scoreManager(scoreManager), m_bulletManager(bulletManager)
{
	textureManager.createTexture("saucer", "assets/saucer.png");

	m_sprite.setTexture(textureManager.getTexture("saucer"));
	m_sprite.setScale(sf::Vector2f(3, 3));
	m_sprite.setPosition(sf::Vector2f((float) m_window.getSize().x, 80));
}

void SaucerEntity::reset()
{
	m_isDestroyed = false;

	m_sprite.setPosition(sf::Vector2f((float) m_window.getSize().x, 80));
}

void SaucerEntity::update(const float elapsedTime)
{
	if (!m_isDestroyed)
	{
		int l_numberOfErasedBullets = 0;

		// Check for collisions with bullets
		for (int i = 0; i < m_bulletManager.getNumberOfBullets(); i++)
		{
			bool l_collision = false;

			sf::FloatRect l_bulletBounds = m_bulletManager.getBulletBounds(i - l_numberOfErasedBullets);

			if (m_sprite.getGlobalBounds().intersects(l_bulletBounds))
			{
				l_collision = true;
			}

			if (l_collision)
			{
				m_bulletManager.removeBullet(i - l_numberOfErasedBullets);

				m_isDestroyed = true;

				m_scoreManager.m_score += 100;

				m_scoreManager.m_numberDestroyed++;

				l_numberOfErasedBullets++;

				break;
			}
		}
	}

	m_sprite.move(sf::Vector2f(-200.0f * elapsedTime, 0));

	if (m_sprite.getPosition().x < -1000.0f)
	{
		m_isDestroyed = false;

		m_sprite.setPosition(sf::Vector2f((float) m_window.getSize().x, m_sprite.getPosition().y));
	}
}

void SaucerEntity::render()
{
	if (!m_isDestroyed)
		m_window.draw(m_sprite);
}
#include "AlienEntity.hpp"

AlienEntity::AlienEntity(sf::RenderWindow& window, ScoreManager& scoreManager, BulletManager& bulletManager, const sf::Texture& texture, sf::Vector2f& relativePosition, const int column, const int row)
	: m_window(window), m_scoreManager(scoreManager), m_bulletManager(bulletManager), m_relativePosition(relativePosition), m_column(column), m_row(row)
{
	m_sprite.setTexture(texture);
	m_sprite.setScale(sf::Vector2f(3, 3));
	m_sprite.setTextureRect(sf::IntRect(0, 0, 12, 8));

	m_sprite.setOrigin(sf::Vector2f(6, 4));
	m_sprite.setPosition(sf::Vector2f(relativePosition.x + (m_sprite.getGlobalBounds().width + m_horizontalSpacing) * column, relativePosition.y + (m_sprite.getGlobalBounds().height + m_verticalSpacing) * row));
}

void AlienEntity::reset()
{
	m_isDestroyed = false;

	m_sprite.setPosition(sf::Vector2f(m_relativePosition.x + (m_sprite.getGlobalBounds().width + m_horizontalSpacing) * m_column, m_relativePosition.y + (m_sprite.getGlobalBounds().height + m_verticalSpacing) * m_row));
}

bool AlienEntity::shoot()
{
	if (m_isDestroyed)
	{
		return false;
	}
	else
	{
		m_bulletManager.createBullet(sf::Vector2i((int)(m_sprite.getPosition().x + m_sprite.getGlobalBounds().width / 4), (int)m_sprite.getPosition().y), BulletManager::BulletType::alien);

		return true;
	}
}

void AlienEntity::update(const float elapsedTime)
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

			bool l_isPlayerBullet = m_bulletManager.getBulletType(i - l_numberOfErasedBullets) == "player";

			if (l_collision && l_isPlayerBullet)
			{
				m_bulletManager.removeBullet(i - l_numberOfErasedBullets);

				m_isDestroyed = true;

				if (m_row == 0)
					m_scoreManager.m_score += 30;
				else if (m_row == 1 || m_row == 2)
					m_scoreManager.m_score += 20;
				else if (m_row == 3 || m_row == 4)
					m_scoreManager.m_score += 10;

				m_scoreManager.m_numberDestroyed++;

				l_numberOfErasedBullets++;

				break;
			}
		}

		// Positioning
		m_sprite.setPosition(sf::Vector2f(m_relativePosition.x + (m_sprite.getGlobalBounds().width + m_horizontalSpacing) * m_column, (m_relativePosition.y * m_sprite.getGlobalBounds().height) + (m_sprite.getGlobalBounds().height + m_verticalSpacing) * m_row));
		
		// Animation
		int l_textureRectX = 0;

		if (m_animationClock.getElapsedTime().asSeconds() >= 0.5)
		{
			if (l_textureRectX == 0)
				l_textureRectX = 12;
			else if (l_textureRectX == 12)
				l_textureRectX = 0;

			if (m_animationClock.getElapsedTime().asSeconds() >= 1)
				m_animationClock.restart();
		}

		int l_textureRectY = 0;

		if (m_row == 0)
			l_textureRectY = 0;
		else if (m_row == 1 || m_row == 2)
			l_textureRectY = 8;
		else if (m_row == 3 || m_row == 4)
			l_textureRectY = 16;

		m_sprite.setTextureRect(sf::IntRect(l_textureRectX, l_textureRectY, 12, 8));
	}
}

void AlienEntity::render()
{
	if (!m_isDestroyed)
		m_window.draw(m_sprite);
}
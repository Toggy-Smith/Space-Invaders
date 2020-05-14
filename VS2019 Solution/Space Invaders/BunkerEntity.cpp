#include "BunkerEntity.hpp"

BunkerEntity::BunkerEntity(sf::RenderWindow& window, TextureManager& textureManager, BulletManager& bulletManager, const int position)
	: m_window(window), m_bulletManager(bulletManager), m_position(position), m_texture(textureManager.getTexture("bunker"))
{
	m_topLeftSprite.setTexture(m_texture);
	m_bottomLeftSprite.setTexture(m_texture);
	m_topMiddleSprite.setTexture(m_texture);
	m_bottomMiddleSprite.setTexture(m_texture);
	m_topRightSprite.setTexture(m_texture);
	m_bottomRightSprite.setTexture(m_texture);

	m_topLeftSprite.setTextureRect(sf::IntRect(0, 16, 7, 8));
	m_bottomLeftSprite.setTextureRect(sf::IntRect(0, 24, 7, 8));
	m_topMiddleSprite.setTextureRect(sf::IntRect(0, 0, 7, 8));
	m_bottomMiddleSprite.setTextureRect(sf::IntRect(0, 8, 7, 8));
	m_topRightSprite.setTextureRect(sf::IntRect(7, 16, -7, 8));
	m_bottomRightSprite.setTextureRect(sf::IntRect(7, 24, -7, 8));

	const int scale = 3;

	m_topLeftSprite.setScale(sf::Vector2f(scale, scale));
	m_bottomLeftSprite.setScale(sf::Vector2f(scale, scale));
	m_topMiddleSprite.setScale(sf::Vector2f(scale, scale));
	m_bottomMiddleSprite.setScale(sf::Vector2f(scale, scale));
	m_topRightSprite.setScale(sf::Vector2f(scale, scale));
	m_bottomRightSprite.setScale(sf::Vector2f(scale, scale));

	m_topLeftSprite.setPosition(sf::Vector2f(window.getSize().x / 5 * m_position - (7 * 3 / 2 * m_topLeftSprite.getScale().x), window.getSize().y - m_topLeftSprite.getGlobalBounds().height * 8));
	m_bottomLeftSprite.setPosition(sf::Vector2f(m_topLeftSprite.getPosition().x, m_topLeftSprite.getPosition().y + m_topLeftSprite.getGlobalBounds().height));
	m_topMiddleSprite.setPosition(sf::Vector2f(m_topLeftSprite.getPosition().x + m_topLeftSprite.getGlobalBounds().width, m_topLeftSprite.getPosition().y));
	m_bottomMiddleSprite.setPosition(sf::Vector2f(m_topMiddleSprite.getPosition().x, m_bottomLeftSprite.getPosition().y));
	m_topRightSprite.setPosition(sf::Vector2f(m_topMiddleSprite.getPosition().x + m_topMiddleSprite.getGlobalBounds().width, m_topMiddleSprite.getPosition().y));
	m_bottomRightSprite.setPosition(sf::Vector2f(m_topRightSprite.getPosition().x, m_bottomMiddleSprite.getPosition().y));
}

void BunkerEntity::update()
{
	int l_numberOfErasedBullets = 0;

	// Check for collisions with bullets
	for (int i = 0; i < m_bulletManager.getNumberOfBullets(); i++)
	{
		bool l_collision = false;
		
		sf::FloatRect l_bulletBounds = m_bulletManager.getBulletBounds(i - l_numberOfErasedBullets);

		if (m_topLeftSprite.getGlobalBounds().intersects(l_bulletBounds) && !m_topLeftDestroyed)
		{
			l_collision = true;

			m_topLeftNumberOfHits++;
		}
		else if (m_bottomLeftSprite.getGlobalBounds().intersects(l_bulletBounds) && !m_bottomLeftDestroyed)
		{
			l_collision = true;

			m_bottomLeftNumberOfHits++;
		}
		else if (m_topMiddleSprite.getGlobalBounds().intersects(l_bulletBounds) && !m_topMiddleDestroyed)
		{
			l_collision = true;

			m_topMiddleNumberOfHits++;
		}
		else if (m_bottomMiddleSprite.getGlobalBounds().intersects(l_bulletBounds) && !m_bottomMiddleDestroyed)
		{
			l_collision = true;

			m_bottomMiddleNumberOfHits++;
		}
		else if (m_topRightSprite.getGlobalBounds().intersects(l_bulletBounds) && !m_topRightDestroyed)
		{
			l_collision = true;

			m_topRightNumberOfHits++;
		}
		else if (m_bottomRightSprite.getGlobalBounds().intersects(l_bulletBounds) && !m_bottomRightDestroyed)
		{
			l_collision = true;

			m_bottomRightNumberOfHits++;
		}

		if (l_collision)
		{
			m_bulletManager.removeBullet(i - l_numberOfErasedBullets);

			l_numberOfErasedBullets++;
		}
	}

	// Check to see if any parts are destroyed, if not, set appropriate texture
	if (m_topLeftNumberOfHits > 3)
		m_topLeftDestroyed = true;
	else
		m_topLeftSprite.setTextureRect(sf::IntRect(7 * m_topLeftNumberOfHits, 16, 7, 8));

	if (m_bottomLeftNumberOfHits > 3)
		m_bottomLeftDestroyed = true;
	else
		m_bottomLeftSprite.setTextureRect(sf::IntRect(7 * m_bottomLeftNumberOfHits, 24, 7, 8));

	if (m_topMiddleNumberOfHits > 3)
		m_topMiddleDestroyed = true;
	else
		m_topMiddleSprite.setTextureRect(sf::IntRect(7 * m_topMiddleNumberOfHits, 0, 7, 8));

	if (m_bottomMiddleNumberOfHits > 3)
		m_bottomMiddleDestroyed = true;
	else
		m_bottomMiddleSprite.setTextureRect(sf::IntRect(7 * m_bottomMiddleNumberOfHits, 8, 7, 8));

	if (m_topRightNumberOfHits > 3)
		m_topRightDestroyed = true;
	else
		m_topRightSprite.setTextureRect(sf::IntRect(7 + (7 * m_topRightNumberOfHits), 16, -7, 8));

	if (m_bottomRightNumberOfHits > 3)
		m_bottomRightDestroyed = true;
	else
		m_bottomRightSprite.setTextureRect(sf::IntRect(7 + (7 * m_bottomRightNumberOfHits), 24, -7, 8));
}

void BunkerEntity::render()
{
	if (!m_topLeftDestroyed) m_window.draw(m_topLeftSprite);
	if (!m_bottomLeftDestroyed) m_window.draw(m_bottomLeftSprite);
	if (!m_topMiddleDestroyed) m_window.draw(m_topMiddleSprite);
	if (!m_bottomMiddleDestroyed) m_window.draw(m_bottomMiddleSprite);
	if (!m_topRightDestroyed) m_window.draw(m_topRightSprite);
	if (!m_bottomRightDestroyed) m_window.draw(m_bottomRightSprite);
}

void BunkerEntity::reset()
{
	m_topLeftDestroyed = false;
	m_bottomLeftDestroyed = false;
	m_topMiddleDestroyed = false;
	m_bottomMiddleDestroyed = false;
	m_topRightDestroyed = false;
	m_bottomRightDestroyed = false;

	m_topLeftNumberOfHits = 0;
	m_bottomLeftNumberOfHits = 0;
	m_topMiddleNumberOfHits = 0;
	m_bottomMiddleNumberOfHits = 0;
	m_topRightNumberOfHits = 0;
	m_bottomRightNumberOfHits = 0;
}
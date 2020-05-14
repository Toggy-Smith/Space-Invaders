#include "BulletManager.hpp"

BulletManager::BulletManager(sf::RenderWindow& window, TextureManager& textureManager) : m_window(window), m_textureManager(textureManager)
{
	textureManager.createTexture("player bullet", "assets/player_bullet.png");
	textureManager.createTexture("alien bullet", "assets/alien_bullet.png");
}

void BulletManager::createBullet(sf::Vector2i position, BulletType bulletType)
{
	if (bulletType == BulletType::player)
	{
		m_bullets.emplace_back(std::make_unique<BulletEntity>(m_window, position, -m_playerBulletSpeed, m_textureManager.getTexture("player bullet")));
	}
	else if (bulletType == BulletType::alien)
	{
		m_bullets.emplace_back(std::make_unique<BulletEntity>(m_window, position, m_alienBulletSpeed, m_textureManager.getTexture("alien bullet")));
	}
}

sf::FloatRect BulletManager::getBulletBounds(int index)
{
	return m_bullets[index]->getBounds();
}

void BulletManager::update(const float elapsedTime)
{
	// Remove bullets that have gone off screen
	int l_numberOfErasedBullets = 0;

	for (unsigned int i = 0; i < m_bullets.size(); i++)
	{
		if (m_bullets[i]->outOfBounds())
		{
			m_bullets.erase(m_bullets.begin() + i - l_numberOfErasedBullets);

			l_numberOfErasedBullets++;
		}
	}

	// Update bullets
	for (unsigned int i = 0; i < m_bullets.size(); i++)
	{
		m_bullets[i]->update(elapsedTime);
	}
}

void BulletManager::render()
{
	for (unsigned int i = 0; i < m_bullets.size(); i++)
	{
		m_bullets[i]->render();
	}
}
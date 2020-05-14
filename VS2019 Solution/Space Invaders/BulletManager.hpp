#pragma once

#include "SFML/Graphics.hpp"

#include "BulletEntity.hpp"
#include "TextureManager.hpp"

#include <vector>
#include <memory>

class BulletManager
{
	private:
		sf::RenderWindow& m_window;

		TextureManager& m_textureManager;
		
		std::vector<std::unique_ptr<BulletEntity>> m_bullets;

		const float m_playerBulletSpeed = 800.0f;
		const float m_alienBulletSpeed = m_playerBulletSpeed * 0.9f;

	public:
		BulletManager(sf::RenderWindow& window, TextureManager& textureManager);

		enum class BulletType { player, alien };

		void reset() { m_bullets.clear(); }

		const std::string getBulletType(int index) const { return m_bullets[index]->getType(); }
		void removeBullet(int index) { m_bullets.erase(m_bullets.begin() + index); }
		void createBullet(sf::Vector2i position, BulletType bulletType);
		int getNumberOfBullets() const { return m_bullets.size(); }
		sf::FloatRect getBulletBounds(int index);
		void update(const float elapsedTime);
		void render();
};
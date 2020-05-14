#pragma once

#include "SFML/Graphics.hpp"

#include "BulletManager.hpp"
#include "TextureManager.hpp"

class BunkerEntity
{
	private:
		sf::RenderWindow& m_window;

		BulletManager& m_bulletManager;

		const int m_position;

		const sf::Texture& m_texture;

		sf::Sprite m_topLeftSprite, m_bottomLeftSprite,
			m_topMiddleSprite, m_bottomMiddleSprite,
			m_topRightSprite, m_bottomRightSprite;

		int m_topLeftNumberOfHits = 0, m_bottomLeftNumberOfHits = 0,
			m_topMiddleNumberOfHits = 0, m_bottomMiddleNumberOfHits = 0,
			m_topRightNumberOfHits = 0, m_bottomRightNumberOfHits = 0;

		bool m_topLeftDestroyed = false, m_bottomLeftDestroyed = false,
			m_topMiddleDestroyed = false, m_bottomMiddleDestroyed = false,
			m_topRightDestroyed = false, m_bottomRightDestroyed = false;
	
	public:
		BunkerEntity(sf::RenderWindow& window, TextureManager& textureManager, BulletManager& bulletManager, const int position);

		void update();
		void render();

		void reset();
};
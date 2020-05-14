#pragma once

#include "SFML/Graphics.hpp"

#include "BunkerEntity.hpp"
#include "BulletManager.hpp"
#include "TextureManager.hpp"

class BunkerManager
{
	private:
		sf::RenderWindow& m_window;

		std::vector<BunkerEntity> m_bunkers;

	public:
		BunkerManager(sf::RenderWindow& window, TextureManager& textureManager, BulletManager& bulletManager);

		void update();
		void render();

		void reset() { for (unsigned int i = 0; i < m_bunkers.size(); i++) m_bunkers[i].reset(); }
};
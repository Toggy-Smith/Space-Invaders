#pragma once

#include "SFML/Graphics.hpp"

#include "BulletManager.hpp"
#include "TextureManager.hpp"
#include "ScoreManager.hpp"

class SaucerEntity
{
	private:
		sf::RenderWindow& m_window;

		ScoreManager& m_scoreManager;

		BulletManager& m_bulletManager;

		sf::Sprite m_sprite;

		bool m_isDestroyed = false;

	public:
		SaucerEntity(sf::RenderWindow& window, TextureManager& textureManager, ScoreManager& scoreManager, BulletManager& bulletManager);

		void reset();

		void update(const float elapsedTime);
		void render();
};
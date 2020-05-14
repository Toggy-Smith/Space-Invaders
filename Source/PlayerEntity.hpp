#pragma once

#include "SFML/Graphics.hpp"

#include "BulletManager.hpp"
#include "TextureManager.hpp"
#include "LivesManager.hpp"

class PlayerEntity
{
	private:
		sf::RenderWindow& m_window;

		sf::Event& m_event;

		sf::Texture m_texture;
		sf::Sprite m_sprite;

		const float m_speed = 750.0f;

		LivesManager& m_livesManager;
		BulletManager& m_bulletManager;

		sf::Clock m_shootLimitClock;

	public:
		PlayerEntity(sf::RenderWindow& window, sf::Event& event, TextureManager& textureManager, LivesManager& livesManager, BulletManager& bulletManager);

		void reset() { m_sprite.setPosition(sf::Vector2f(m_window.getSize().x / 2 - m_sprite.getGlobalBounds().width / 2, m_window.getSize().y - m_sprite.getGlobalBounds().height * 4)); }
		void handleEvents();
		void update(const float elapsedTime);
		void render();
};
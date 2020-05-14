#pragma once

#include "SFML/Graphics.hpp"

#include "TextureManager.hpp"

class BulletEntity
{
	private:
		sf::RenderWindow& m_window;

		const sf::Texture& m_texture;

		sf::Sprite m_sprite;

		const float m_speed;

	public:
		BulletEntity(sf::RenderWindow& window, sf::Vector2i& position, const float speed, const sf::Texture& texture);

		const std::string getType();
		bool outOfBounds();
		const sf::FloatRect getBounds() const { return m_sprite.getGlobalBounds(); }
		void update(const float elapsedTime);
		void render();
};
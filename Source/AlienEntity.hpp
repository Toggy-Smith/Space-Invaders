#pragma once

#include "SFML/Graphics.hpp"

#include "BulletManager.hpp"
#include "TextureManager.hpp"
#include "ScoreManager.hpp"

class AlienEntity
{
	private:
		sf::RenderWindow& m_window;

		ScoreManager& m_scoreManager;

		BulletManager& m_bulletManager;

		sf::Sprite m_sprite;

		sf::Vector2f& m_relativePosition;

		const int m_column;
		const int m_row;

		const int m_horizontalSpacing = 10;
		const int m_verticalSpacing = 20;

		bool m_isDestroyed = false;

		sf::Clock m_animationClock;

	public:
		AlienEntity(sf::RenderWindow& window, ScoreManager& scoreManager, BulletManager& bulletManager, const sf::Texture& texture, sf::Vector2f& relativePosition, const int column, const int row);
		
		void reset();

		int getSpace() const { return (int) m_sprite.getGlobalBounds().width + m_horizontalSpacing; }
		int getRightX() const { return (int) m_sprite.getPosition().x + (int) m_sprite.getGlobalBounds().width; }
		int getX() const { return (int) m_sprite.getPosition().x; }
		bool getIsDestroyed() { return m_isDestroyed; }
		bool shoot();
		void update(const float elapsedTime);
		void render();
};
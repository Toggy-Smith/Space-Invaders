#pragma once

#include "SFML/Graphics.hpp"

#include "AlienEntity.hpp"
#include "BulletManager.hpp"
#include "SaucerEntity.hpp"
#include "TextureManager.hpp"
#include "ScoreManager.hpp"
#include "GameOverManager.hpp"

#include <vector>
#include <random>

class AlienManager
{
	private:
		sf::RenderWindow& m_window;

		std::vector<AlienEntity> m_aliens;

		GameOverManager& m_gameOverManager;

		SaucerEntity m_saucer;

		sf::Vector2f m_position = sf::Vector2f(30, 6);

		enum class Direction { LEFT, RIGHT };

		Direction m_movementDirection = Direction::RIGHT;

		float m_movementAmount = 10.0f;

		sf::Clock m_movementClock;

		float m_movementClockWaitTime = 0.5f;

		sf::Clock m_shootClock;

		ScoreManager& m_scoreManager;

	public:
		AlienManager(sf::RenderWindow& window, GameOverManager& gameOverManager, ScoreManager& scoreManager, BulletManager& bulletManager, TextureManager& textureManager);

		void reset();

		void update(const float elapsedTime);
		void render();
};
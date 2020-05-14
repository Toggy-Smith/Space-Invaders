#pragma once

#include "SFML/Graphics.hpp"

#include "AlienManager.hpp"
#include "BunkerManager.hpp"
#include "BulletManager.hpp"
#include "PlayerEntity.hpp"
#include "TextureManager.hpp"
#include "ScoreManager.hpp"
#include "LivesManager.hpp"
#include "GameOverManager.hpp"

class GameManager
{
	private:
		sf::RenderWindow& m_window;

		sf::Event m_event;

		sf::Clock m_updateClock;

		GameOverManager m_gameOverManager;
		ScoreManager m_scoreManager;
		LivesManager m_livesManager;
		TextureManager m_textureManager;
		AlienManager m_alienManager;
		BunkerManager m_bunkerManager;
		BulletManager m_bulletManager;
		PlayerEntity m_playerEntity;

		sf::RectangleShape m_greenLine;

	public:
		GameManager(sf::RenderWindow& window);

		void handleEvents();
		void update();
		void render();
};
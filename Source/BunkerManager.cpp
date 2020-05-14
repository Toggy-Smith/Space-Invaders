#include "BunkerManager.hpp"

BunkerManager::BunkerManager(sf::RenderWindow& window, TextureManager& textureManager, BulletManager& bulletManager)
	: m_window(window)
{
	textureManager.createTexture("bunker", "assets/bunker.png");

	m_bunkers.push_back(BunkerEntity(window, textureManager, bulletManager, 1));
	m_bunkers.push_back(BunkerEntity(window, textureManager, bulletManager, 2));
	m_bunkers.push_back(BunkerEntity(window, textureManager, bulletManager, 3));
	m_bunkers.push_back(BunkerEntity(window, textureManager, bulletManager, 4));
}

void BunkerManager::update()
{
	for (unsigned int b = 0; b < m_bunkers.size(); b++)
		m_bunkers[b].update();
}

void BunkerManager::render()
{
	for (unsigned int b = 0; b < m_bunkers.size(); b++)
		m_bunkers[b].render();
}
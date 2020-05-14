#include "PlayerEntity.hpp"

PlayerEntity::PlayerEntity(sf::RenderWindow& window, sf::Event& event, TextureManager& textureManager, LivesManager& livesManager, BulletManager& bulletManager)
	: m_window(window), m_event(event), m_livesManager(livesManager), m_bulletManager(bulletManager)
{
	textureManager.createTexture("player", "assets/player.png");
	
	m_texture = textureManager.getTexture("player");

	m_sprite.setTexture(m_texture);
	m_sprite.setScale(sf::Vector2f(3, 3));
	m_sprite.setPosition(sf::Vector2f(m_window.getSize().x / 2 - m_sprite.getGlobalBounds().width / 2, m_window.getSize().y - m_sprite.getGlobalBounds().height * 4));
}

void PlayerEntity::handleEvents()
{
	if (m_event.type == sf::Event::KeyReleased)
	{
		bool l_isShootButtonReleased = (m_event.key.code == sf::Keyboard::Space || m_event.key.code == sf::Keyboard::Up);
		bool l_isAbleToShoot = m_shootLimitClock.getElapsedTime().asSeconds() >= 0.8f;

		if (l_isShootButtonReleased && l_isAbleToShoot)
		{
			m_shootLimitClock.restart();

			m_bulletManager.createBullet((sf::Vector2i) sf::Vector2f(m_sprite.getPosition().x + m_sprite.getGlobalBounds().width / 2, m_sprite.getPosition().y), BulletManager::BulletType::player);
		}
	}
}

void PlayerEntity::update(const float elapsedTime)
{
	// Check to see if any bullets have collided with the player
	int l_numberOfErasedBullets = 0;

	for (int i = 0; i < m_bulletManager.getNumberOfBullets(); i++)
	{
		if (m_bulletManager.getBulletType(i - l_numberOfErasedBullets) == "player")
			continue;

		const sf::FloatRect& l_bulletBounds = m_bulletManager.getBulletBounds(i - l_numberOfErasedBullets);

		if (m_sprite.getGlobalBounds().intersects(l_bulletBounds))
		{
			m_livesManager.m_lives -= 1;

			m_bulletManager.removeBullet(i - l_numberOfErasedBullets);

			break;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_sprite.move(sf::Vector2f(-(m_speed * elapsedTime), 0));

		if (m_sprite.getPosition().x < 0)
			m_sprite.setPosition(sf::Vector2f(0, m_sprite.getPosition().y));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_sprite.move(sf::Vector2f(m_speed * elapsedTime, 0));

		if (m_sprite.getPosition().x + m_sprite.getGlobalBounds().width > m_window.getSize().x)
			m_sprite.setPosition(sf::Vector2f(m_window.getSize().x - m_sprite.getGlobalBounds().width, m_sprite.getPosition().y));
	}
}

void PlayerEntity::render()
{
	m_window.draw(m_sprite);
}
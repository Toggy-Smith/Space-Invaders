#include "BulletEntity.hpp"

BulletEntity::BulletEntity(sf::RenderWindow& window, sf::Vector2i& position, const float speed, const sf::Texture& texture) : m_window(window), m_speed(speed), m_texture(texture)
{
	m_sprite.setPosition((sf::Vector2f) position);
	m_sprite.setTexture(m_texture);
	m_sprite.setScale(sf::Vector2f(3, 3));
}

const std::string BulletEntity::getType()
{
	if (m_speed > 0)
	{
		return "alien";
	}
	else
	{
		return "player";
	}
}

bool BulletEntity::outOfBounds()
{
	bool l_isOffTopSideOfScreen = m_sprite.getPosition().y < 0;
	bool l_isOffBottomSideOfScreen = m_sprite.getPosition().y + m_sprite.getGlobalBounds().height > m_window.getSize().y;

	if (l_isOffTopSideOfScreen || l_isOffBottomSideOfScreen)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void BulletEntity::update(const float elapsedTime)
{
	m_sprite.move(sf::Vector2f(0, m_speed * elapsedTime));
}

void BulletEntity::render()
{
	m_window.draw(m_sprite);
}
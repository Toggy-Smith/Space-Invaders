#include "TextureManager.hpp"

void TextureManager::createTexture(const std::string& name, const std::string& location)
{
	sf::Texture texture;

	texture.loadFromFile(location);

	m_textures.emplace(name, texture);
}

const sf::Texture& TextureManager::getTexture(const std::string& name) const
{
	return m_textures.at(name);
}
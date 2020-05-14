#pragma once

#include "SFML/Graphics.hpp"

#include <map>

class TextureManager
{
	private:
		std::map<std::string, sf::Texture> m_textures;

	public:
		void createTexture(const std::string& name, const std::string& location);
		const sf::Texture& getTexture(const std::string& name) const;
};
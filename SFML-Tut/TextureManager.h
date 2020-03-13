#pragma once
#include "ResourceManager.h"
#include <SFML/Graphics.hpp>

class TextureManager : public ResourceManager<TextureManager, sf::Texture>
{
public:
	TextureManager()
		:
		ResourceManager( "textures.cfg" )
	{}
	~TextureManager() override {}

public:
	sf::Texture* Load( const std::string& path )
	{
		sf::Texture* texture = new sf::Texture();

		if ( !texture->loadFromFile( Utils::GetWorkingDirectory() + path ) )
		{
			delete texture;
			texture = nullptr;
			std::cerr << "No se pudo cargar la textura: " << path << std::endl;
		}

		return texture;
	}
private:

};
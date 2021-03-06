#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "TextureManager.h"
#include "AnimDirectional.h"
#include "Utilities.h"
#include <unordered_map>

using Animations = std::unordered_map<std::string, AnimBase*>;

class SpriteSheet
{
public:
	SpriteSheet( TextureManager* textMgr );
	~SpriteSheet();

public:
	void CropSprite( sf::IntRect& rect );
	bool LoadSheet( const std::string& file );
	void ReleaseSheet();
	void SetSpriteSize( const sf::Vector2i& sprSize );
	sf::Vector2i GetSpriteSize();
	Direction GetDirection();
	void SetSpritePosition( const sf::Vector2f& pos );
	void SetDirection( const Direction& dir );
	AnimBase* GetCurrentAnim();
	bool SetAnimation( const std::string& name, const bool& play = false, const bool& loop = false );
	void Update( const float& dt );
	void Draw( sf::RenderWindow* window );

private:
	std::string texture;
	sf::Sprite sprite;
	sf::Vector2i spriteSize;
	sf::Vector2f spriteScale;
	Direction direction;
	std::string animType;
	Animations animations;
	AnimBase* animationCurrent;
	TextureManager* textureManager;
};
#pragma once
#include <SFML/Graphics.hpp>
#include "Snake.h"

class World
{
public:
	World( sf::Vector2u windowSize );
	~World() = default;

public:
	int GetBlockSize() const;
	void RespawnApple();
	void Update( Snake& player );
	void Render( sf::RenderWindow& window );

private:
	sf::Vector2u windowSize;
	sf::Vector2i item;
	int blockSize;
	sf::CircleShape appleShape;
	sf::RectangleShape bounds[4];
};
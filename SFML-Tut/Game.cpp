#include "Game.h"

Game::Game()
	:
	window( "Chapter 2", { 640, 480 } )
{
	if ( !mushroomTexture.loadFromFile( "img/Mushroom.png" ) )
	{
		throw("Error loading img Mushroom.png");
	}

	mushroom.setTexture( mushroomTexture );
	increment = sf::Vector2f( 4.f, 4.f );
}

void Game::HandleInput()
{
}

void Game::Update()
{
	window.Update();
	MoveMushroom();
}

void Game::Render()
{
	window.BeginDraw();
	window.Draw( mushroom );
	window.EndDraw();
}

Window * Game::GetWindow()
{
	return &window;
}

void Game::MoveMushroom()
{
	sf::Vector2u windowSize = window.GetWindowSize();
	sf::Vector2u textureSize = mushroomTexture.getSize();

	if ( (mushroom.getPosition().x >= windowSize.x - textureSize.x  && increment.x > 0) ||
		(mushroom.getPosition().x < 0 && increment.x < 0) )
	{
		increment.x = -increment.x;
	}
	if ( (mushroom.getPosition().y >= windowSize.y - textureSize.y && increment.y > 0) ||
		(mushroom.getPosition().y < 0 && increment.y < 0) )
	{
		increment.y = -increment.y;
	}
	mushroom.setPosition( mushroom.getPosition() + increment );
}

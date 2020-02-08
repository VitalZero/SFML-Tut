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
	increment = sf::Vector2f( 400.f, 400.f );
}

void Game::HandleInput()
{
}

void Game::Update()
{
	window.Update();

	MoveMushroom();

	if ( elapsed.asSeconds() >= frameTime )
	{
		elapsed -= sf::seconds( frameTime );
	}
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

sf::Time Game::GetElapsed()
{
	return elapsed;
}

void Game::RestartClock()
{
	elapsed = clock.restart();
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
	float dt = elapsed.asSeconds();

	mushroom.setPosition( mushroom.getPosition() + increment * dt );
}

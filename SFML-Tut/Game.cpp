#include "Game.h"

Game::Game()
	:
	window( "Snake!", { 640, 480 } ),
	snake( world.GetBlockSize() ),
	world( sf::Vector2u(640, 480) )
{
	clock.restart();
	srand( time( nullptr ) );
	elapsed = 0.0f;
}

void Game::HandleInput()
{
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) &&
		snake.GetDirection() != Direction::Down )
	{
		snake.SetDirection( Direction::Up );
	}
	else if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Down ) &&
		snake.GetDirection() != Direction::Up )
	{
		snake.SetDirection( Direction::Down );
	}
	else if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) &&
		snake.GetDirection() != Direction::Right )
	{
		snake.SetDirection( Direction::Left );
	}
	else if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) &&
		snake.GetDirection() != Direction::Left )
	{
		snake.SetDirection( Direction::Right );
	}
}

void Game::Update()
{
	window.Update();

	float timeStep = 1.0f / snake.GetSpeed();

	if ( elapsed >= timeStep )
	{
		snake.Tick();
		world.Update( snake );
		elapsed -= timeStep;
		if ( snake.HasLost() )
		{
			snake.Reset();
		}
	}
}

void Game::Render()
{
	window.BeginDraw();

	world.Render( *window.GetRenderWindow() );
	snake.Render( *window.GetRenderWindow() );

	window.EndDraw();
}

Window * Game::GetWindow()
{
	return &window;
}

sf::Time Game::GetElapsed()
{
	return clock.getElapsedTime();
}

void Game::RestartClock()
{
	elapsed += clock.restart().asSeconds();
}
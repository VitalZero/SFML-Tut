#include "Game.h"

Game::Game()
	:
	window( "Snake!", { 640, 480 } ),
	snake( world.GetBlockSize() ),
	world( sf::Vector2u(640, 480) ),
	stateManager(&context)
{
	context.window = &window;
	context.eventManager = window.GetEventManager();
	stateManager.SwitchTo( StateType::Intro );

	textbox.Setup( 5, 14, 350, sf::Vector2f( 255, 0 ) );
	textbox.Add( "Seeded random number generator with " + std::to_string( time( nullptr ) ) );
	clock.restart();
	srand( time( nullptr ) );
	elapsed = sf::Time::Zero;
}

void Game::HandleInput()
{
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) &&
		snake.GetPhysicalDirection() != Direction::Down )
	{
		snake.SetDirection( Direction::Up );
	}
	else if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Down ) &&
		snake.GetPhysicalDirection() != Direction::Up )
	{
		snake.SetDirection( Direction::Down );
	}
	else if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) &&
		snake.GetPhysicalDirection() != Direction::Right )
	{
		snake.SetDirection( Direction::Left );
	}
	else if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) &&
		snake.GetPhysicalDirection() != Direction::Left )
	{
		snake.SetDirection( Direction::Right );
	}
}

void Game::Update()
{
	window.Update();
	
/*
	float timeStep = 1.0f / snake.GetSpeed();
	float tmpElapsed = elapsed.asSeconds();

	if ( tmpElapsed >= timeStep )
	{
		snake.Tick();
		world.Update( snake, textbox );
		tmpElapsed -= timeStep;
		if ( snake.HasLost() )
		{
			snake.Reset();
		}
	}
	*/
	stateManager.Update( elapsed );
}

void Game::Render()
{
	window.BeginDraw();
	

	/*world.Render( *window.GetRenderWindow() );
	snake.Render( *window.GetRenderWindow() );
	textbox.Render( *window.GetRenderWindow() );*/
	stateManager.Draw();
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
	elapsed = clock.restart();
}

void Game::LateUpdate()
{
	stateManager.ProcessRequests();
	RestartClock();
}

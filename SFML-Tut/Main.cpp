#include <SFML/Graphics.hpp>
#include "Game.h"
#include <iostream>

int main()
{
	Game game;
	
	float lastTime = 0.f; // fps

	while ( !game.GetWindow()->IsDone() )
	{
		game.HandleInput();
		game.Update();
		game.Render();
		game.RestartClock();
		float currentTime = game.GetElapsed().asSeconds(); // fps
		float fps = 1.0f / currentTime; // fps
		lastTime = currentTime; // fps

		//std::cout << "FPS: " << fps << "\n"; // fps
	}

	return 0;
}
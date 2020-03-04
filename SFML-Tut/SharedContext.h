#pragma once
#include <SFML/Graphics.hpp>

struct SharedContext
{
	SharedContext()
		:
		window( nullptr ),
		eventManager( nullptr )
	{}
	Window* window;
	EventManager* eventManager;
};
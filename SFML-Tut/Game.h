#pragma once
#include "SFMLWindow.h"
#include "World.h"
#include "Textbox.h"
#include "StateManager.h"

class Game
{
public:
	Game();
	~Game() = default;

public:
	void HandleInput();
	void Update();
	void Render();
	Window* GetWindow();
	sf::Time GetElapsed();
	void RestartClock();
	void LateUpdate();

private:
	Window window;
	sf::Clock clock;
	sf::Time elapsed;
	float frameTime = 1.0f / 60.0f;
	float constantFT = 0.0f;
	World world;
	Snake snake;
	Textbox textbox;
	SharedContext context;
	StateManager stateManager;
};
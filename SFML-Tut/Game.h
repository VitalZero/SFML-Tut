#pragma once
#include "SFMLWindow.h"

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

private:
	Window window;
	void MoveMushroom();
	sf::Texture mushroomTexture;
	sf::Sprite mushroom;
	sf::Vector2f increment;
	sf::Clock clock;
	sf::Time elapsed;
	float frameTime = 1.0f / 60.0f;
	float constantFT = 0.0f;
};
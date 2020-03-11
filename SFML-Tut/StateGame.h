#pragma once
#include <SFML/Graphics.hpp>
#include "BaseState.h"
#include "EventManager.h"
#include "StateManager.h"

class StateGame : public BaseState
{
public:
	StateGame(StateManager* stateManager);
	~StateGame() {}

public:
	void OnCreate() override;
	void OnDestroy() override;
	void Activate() override {};
	void Deactivate() override {};
	void Update( const sf::Time& time ) override;
	void Draw() override;
	void MainMenu( EventDetails* details );
	void Pause( EventDetails* details );

private:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f increment;
};
#pragma once
#include <SFML/Graphics.hpp>
#include "BaseState.h"
#include "EventManager.h"
#include "StateManager.h"

class StatePaused : public BaseState
{
public:
	StatePaused( StateManager* stateManager );
	~StatePaused() {}

public:
	void OnCreate() override;
	void OnDestroy() override;
	void Activate() override {};
	void Deactivate() override {};
	void Update( const sf::Time& time ) override {};
	void Draw() override;
	void Unpause( EventDetails* eventDetails );

private:
	sf::Text text;
	sf::Font font;
	sf::RectangleShape rect;
};
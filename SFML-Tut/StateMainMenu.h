#pragma once
#include <SFML/Graphics.hpp>
#include "BaseState.h"
#include "EventManager.h"
#include "StateManager.h"

class MainMenu : public BaseState 
{
public:
	MainMenu( StateManager* stateManager );
	~MainMenu() {};

public:
	void OnCreate() override;
	void OnDestroy() override;
	void Activate() override;
	void Deactivate() override {};
	void Update( const sf::Time& time ) override {};
	void Draw() override;
	void MouseClick( EventDetails* eventDetails );

private:
	sf::Text text;
	sf::Font font;
	sf::Vector2f buttonSize;
	sf::Vector2f buttonPos;
	unsigned int buttonPadding;
	sf::RectangleShape rects[3];
	sf::Text labels[3];
};
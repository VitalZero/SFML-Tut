#pragma once
#include <SFML/Graphics.hpp>
#include "BaseState.h"
#include "EventManager.h"

class StateIntro : public BaseState
{
public:
	StateIntro(StateManager* stateManager);
	~StateIntro() {}
public:
	void OnCreate() override;
	void OnDestroy() override;
	void Activate() override {};
	void Deactivate() override {};
	void Update( const sf::Time& time ) override;
	void Draw() override;
	void Continue( EventDetails* details );

private:
	sf::Texture introTexture;
	sf::Sprite introSprite;
	sf::Text text;
	sf::Font font;
	float timePassed;
};
#include "StateGame.h"

StateGame::StateGame( StateManager * stateManager )
	:
	BaseState( stateManager )
{
}

void StateGame::OnCreate()
{
	texture.loadFromFile( "img/mushroom.png" );
	sprite.setTexture( texture );
	sprite.setPosition( 0, 0 );
	increment = sf::Vector2f( 400.0f, 400.f );

	EventManager* evtMgr = stateManager->GetContext()->eventManager;
	evtMgr->AddCallback( StateType::Game, "Key_Escape", &StateGame::MainMenu, this );
	evtMgr->AddCallback( StateType::Game, "Key_P", &StateGame::Pause, this );
}

void StateGame::OnDestroy()
{
}

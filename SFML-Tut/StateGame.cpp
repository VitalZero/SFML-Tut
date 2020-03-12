#include "StateGame.h"

StateGame::StateGame( StateManager * stateManager )
	:
	BaseState( stateManager )
{
}

void StateGame::OnCreate()
{
	texture.loadFromFile( "img\\Mushroom.png" );
	sprite.setTexture( texture );
	sprite.setOrigin( texture.getSize().x / 2.0f, texture.getSize().y / 2.0f );
	sprite.setPosition( 100, 100 );
	increment = sf::Vector2f( 400.0f, 400.0f );

	EventManager* evtMgr = stateManager->GetContext()->eventManager;
	evtMgr->AddCallback( StateType::Game, "Key_Escape", &StateGame::MainMenu, this );
	evtMgr->AddCallback( StateType::Game, "Key_P", &StateGame::Pause, this );
}

void StateGame::OnDestroy()
{
	EventManager* evtMgr = stateManager->GetContext()->eventManager;
	evtMgr->RemoveCallback( StateType::Game, "Key_Escape" );
	evtMgr->RemoveCallback( StateType::Game, "Key_P" );
}

void StateGame::Update( const sf::Time & time )
{
	sf::Vector2u windSize = stateManager->GetContext()->window->GetWindowSize();
	sf::Vector2u textSize = texture.getSize();

	if ( (sprite.getPosition().x + (textSize.x / 2.0f) >= windSize.x  && increment.x > 0) ||
		(sprite.getPosition().x - (textSize.x / 2.0f) < 0 && increment.x < 0) )
	{
		increment.x = -increment.x;
	}
	if ( (sprite.getPosition().y + (textSize.y / 2.0f) > windSize.y && increment.y > 0) ||
		(sprite.getPosition().y - (textSize.y / 2.0f) < 0 && increment.y < 0) )
	{
		increment.y = -increment.y;
	}

	sprite.setPosition(
		sprite.getPosition().x + (increment.x * time.asSeconds()),
		sprite.getPosition().y + (increment.y * time.asSeconds()) );
}

void StateGame::Draw()
{
	stateManager->GetContext()->window->GetRenderWindow()->draw( sprite );
}

void StateGame::MainMenu( EventDetails * details )
{
	stateManager->SwitchTo( StateType::MainMenu );
}

void StateGame::Pause( EventDetails * details )
{
	stateManager->SwitchTo( StateType::Paused );
}

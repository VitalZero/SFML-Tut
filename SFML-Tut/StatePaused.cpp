#include "StatePaused.h"

StatePaused::StatePaused( StateManager * stateManager )
	:
	BaseState( stateManager )
{
}

void StatePaused::OnCreate()
{
	SetTransparent( true );
	font.loadFromFile( "fonts/arial.ttf" );
	text.setFont( font );
	text.setString( sf::String( "PAUSED" ) );
	text.setCharacterSize( 14 );
	text.setStyle( sf::Text::Bold );

	sf::Vector2u windowSize = stateManager->GetContext()->window->GetWindowSize();
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin( textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f );
	text.setPosition( windowSize.x / 2.0f, windowSize.y / 2.0f );

	rect.setSize( (sf::Vector2f)windowSize );
	rect.setPosition( 0, 0 );
	rect.setFillColor( sf::Color( 0, 0, 0, 150 ) );

	EventManager* evtMgr = stateManager->GetContext()->eventManager;
	evtMgr->AddCallback( StateType::Paused, "Key_P", &StatePaused::Unpause, this );
}

void StatePaused::OnDestroy()
{
	EventManager* evtMgr = stateManager->GetContext()->eventManager;
	evtMgr->RemoveCallback( StateType::Paused, "Key_P" );
}

void StatePaused::Draw()
{
	sf::RenderWindow* renderWindow = stateManager->GetContext()->window->GetRenderWindow();
	renderWindow->draw( rect );
	renderWindow->draw( text );
}

void StatePaused::Unpause( EventDetails * eventDetails )
{
	stateManager->SwitchTo( StateType::Game );
}

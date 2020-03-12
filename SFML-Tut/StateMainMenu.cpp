#include "StateMainMenu.h"

StateMainMenu::StateMainMenu( StateManager * stateManager )
	:
	BaseState( stateManager )
{
}

void StateMainMenu::OnCreate()
{
	font.loadFromFile( "fonts\\arial.ttf" );
	text.setFont( font );
	text.setString( { "MAIN MENU:" } );
	text.setCharacterSize( 18 );

	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin( textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f );
	text.setPosition( 400, 100 );

	buttonSize.x = 300.0f;
	buttonSize.y = 32.0f;
	buttonPos.x = 400.0f;
	buttonPos.y = 200.0f;
	buttonPadding = 4;

	std::string str[3] =
	{
		"PLAY",
		"CREDITS",
		"EXIT"
	};

	for ( int i = 0; i < 3; ++i )
	{
		sf::Vector2f tmpButtonPos( buttonPos.x, buttonPos.y + i * (buttonSize.y + buttonPadding) );

		rects[i].setSize( buttonSize );
		rects[i].setFillColor( sf::Color::Red );
		rects[i].setOrigin( buttonSize.x / 2.0f, buttonSize.y / 2.0f );
		rects[i].setPosition( tmpButtonPos );

		labels[i].setFont( font );
		labels[i].setString( sf::String( str[i] ) );
		labels[i].setCharacterSize( 12 );

		sf::FloatRect rect = labels[i].getLocalBounds();
		labels[i].setOrigin( rect.left + rect.width / 2.0f, rect.top + rect.height / 2.0f );
		labels[i].setPosition( tmpButtonPos );
	}

	EventManager* evMgr = stateManager->GetContext()->eventManager;
	evMgr->AddCallback( StateType::MainMenu, "Mouse_Left", &StateMainMenu::MouseClick, this );
}

void StateMainMenu::OnDestroy()
{
	EventManager* evMgr = stateManager->GetContext()->eventManager;
	evMgr->RemoveCallback( StateType::MainMenu, "Mouse_Left" );
}

void StateMainMenu::Activate()
{
	if ( stateManager->HasState( StateType::Game ) && labels[0].getString() == "PLAY" )
	{
		labels[0].setString( sf::String( "RESUME" ) );
		sf::FloatRect rect = labels[0].getLocalBounds();
		labels[0].setOrigin( rect.left + rect.width / 2.0f, rect.top + rect.height / 2.0f );
	}
}

void StateMainMenu::Draw()
{
	sf::RenderWindow* window = stateManager->GetContext()->window->GetRenderWindow();
	
	window->draw( text );

	for ( int i = 0; i < 3; ++i )
	{
		window->draw( rects[i] );
		window->draw( labels[i] );
	}
}

void StateMainMenu::MouseClick( EventDetails * eventDetails )
{
	sf::Vector2i mousePos = eventDetails->mouse;

	float halfX = buttonSize.x / 2.0f;
	float halfY = buttonSize.y / 2.0f;
	
	for( int i = 0; i < 3; ++i )
	{
		if ( mousePos.x >= rects[i].getPosition().x - halfX &&
			mousePos.x <= rects[i].getPosition().x + halfX &&
			mousePos.y >= rects[i].getPosition().y - halfY &&
			mousePos.y <= rects[i].getPosition().y + halfY )
		{
			if ( i == 0 )
			{
				stateManager->SwitchTo( StateType::Game );
			}
			else if ( i == 1 )
			{

			}
			else if ( i == 2 )
			{
				stateManager->GetContext()->window->Close();
			}
		}
	}
}

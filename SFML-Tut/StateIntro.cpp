#include "StateIntro.h"

StateIntro::StateIntro( StateManager * stateManager )
	:
	BaseState(stateManager)
{
}

void StateIntro::OnCreate()
{
	timePassed = 0.0f;

	sf::Vector2u windowSize = stateManager->GetContext()->window->GetRenderWindow()->getSize();

	introTexture.loadFromFile( "img\\intro.png" );
	introSprite.setTexture( introTexture );

	introSprite.setOrigin( introTexture.getSize().x / 2.0f, introTexture.getSize().y / 2.0f );
	introSprite.setPosition( windowSize.x / 2.0f, 0 );

	font.loadFromFile( "fonts\\arial.ttf" );
	text.setFont( font );
	text.setString( { "Press SPACE to continue" } );
	text.setCharacterSize( 15 );

	sf::FloatRect textRect = text.getLocalBounds();

	text.setOrigin( textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f );
	text.setPosition( windowSize.x / 2.0f, (windowSize.y / 2.0f) + 80.0f );

	EventManager* evMgr = stateManager->GetContext()->eventManager;
	evMgr->AddCallback( StateType::Intro, "Intro_Continue", &StateIntro::Continue, this );
}

void StateIntro::OnDestroy()
{
	EventManager* evMgr = stateManager->GetContext()->eventManager;
	evMgr->RemoveCallback( StateType::Intro, "Intro_Continue" );
}

void StateIntro::Update( const sf::Time & time )
{
	if ( timePassed < 5.0f )
	{
		timePassed += time.asSeconds();
		introSprite.setPosition( introSprite.getPosition().x, 
			introSprite.getPosition().y + ( 48 * time.asSeconds() ) );
	}
}

void StateIntro::Draw()
{
	sf::RenderWindow* window = stateManager->GetContext()->window->GetRenderWindow();
	window->draw( introSprite );
	if ( timePassed >= 5.0f )
	{
		window->draw( text );
	}
}

void StateIntro::Continue( EventDetails * details )
{
	if ( timePassed >= 5.0f )
	{
		stateManager->SwitchTo( StateType::MainMenu );
		stateManager->Remove( StateType::Intro );
	}
}

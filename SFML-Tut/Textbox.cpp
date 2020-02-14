#include "Textbox.h"
#include <algorithm>

Textbox::Textbox()
{
	Setup( 5, 9, 200, sf::Vector2f( 0, 0 ) );
}

Textbox::Textbox( int visible, int charSize, int width, sf::Vector2f screenPos )
{
	Setup( visible, charSize, width, screenPos );
}

Textbox::~Textbox()
{
	Clear();
}

void Textbox::Setup( int visible, int charSize, int width, sf::Vector2f screenPos )
{
	numVisible = visible;
	sf::Vector2f offset( 2.0f, 2.0f );

	font.loadFromFile( "fonts/arial.ttf" );
	content.setFont( font );
	content.setString( "" );
	content.setCharacterSize( charSize );
	content.setFillColor( sf::Color( 255, 255, 255, 150 ) );
	content.setPosition( screenPos + offset);

	backdrop.setSize( sf::Vector2f( width, (visible* charSize * 1.2f) ) );
	backdrop.setFillColor( sf::Color( 90, 90, 90, 90 ) );
	backdrop.setPosition( screenPos );
}

void Textbox::Add( std::string message )
{
	messages.push_back( message );

	if ( messages.size() >= 6 )
	{
		messages.erase( messages.begin() );
	}
}

void Textbox::Clear()
{
	messages.clear();
}

void Textbox::Render( sf::RenderWindow & window )
{
	std::string tmpContent;

	for ( auto& itr : messages )
	{
		tmpContent.append( itr + "\n" );
	}

	if ( tmpContent != "" )
	{
		content.setString( tmpContent );
		window.draw( backdrop );
		window.draw( content );
	}
}

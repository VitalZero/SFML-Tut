#include <SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow window( sf::VideoMode( 640, 480 ), "SFML tut!" );

	while ( window.isOpen() )
	{
		sf::RectangleShape rectangle( sf::Vector2f( 128.0f, 128.0f ) );
		rectangle.setPosition( 320, 240 );
		rectangle.setFillColor( sf::Color::Red );
		rectangle.setOrigin( rectangle.getSize().x / 2, rectangle.getSize().y / 2 );

		sf::Event event;
		while ( window.pollEvent( event ) )
		{
			if ( event.type == sf::Event::Closed )
			{
				window.close();
			}
		}

		window.clear( sf::Color::Black );
		// init draw
		window.draw( rectangle );
		// end draw
		window.display();
	}

	return 0;
}
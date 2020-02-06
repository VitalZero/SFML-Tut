#include <SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow window( sf::VideoMode( 640, 480 ), "SFML tut!" );

	while ( window.isOpen() )
	{
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

		// end draw
		window.display();
	}

	return 0;
}
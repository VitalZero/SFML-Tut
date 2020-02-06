#include <SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow window( sf::VideoMode( 640, 480 ), "SFML tut!" );

	sf::Texture texture;
	if ( !texture.loadFromFile( "img/Mushroom.png" ) )
	{
		throw("Error loading img Mushroom.png");
	}

	sf::Sprite sprite( texture );
	sf::Vector2u size = texture.getSize();
	sprite.setOrigin( (float)size.x / 2, (float)size.y / 2 );
	sf::Vector2f increment( 1.8f, 1.8f );

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
		// update
		if ( (sprite.getPosition().x + (size.x / 2) >= window.getSize().x && increment.x > 0) ||
			(sprite.getPosition().x - (size.x / 2) < 0 && increment.x < 0) )
		{
			increment.x = -increment.x;
		}
		if ( (sprite.getPosition().y + (size.y / 2) >= window.getSize().y && increment.y > 0) ||
			(sprite.getPosition().y - (size.y / 2) < 0 && increment.y < 0) )
		{
			increment.y = -increment.y;
		}
		sprite.setPosition( sprite.getPosition() + increment );
		//end update

		window.clear( sf::Color::White );
		// init draw
		window.draw( sprite );
		// end draw
		window.display();
	}

	return 0;
}
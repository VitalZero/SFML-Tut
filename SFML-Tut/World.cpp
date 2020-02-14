#include "World.h"

World::World( sf::Vector2u windowSize )
	:
	blockSize(16),
	windowSize(windowSize)
{
	RespawnApple();
	appleShape.setFillColor( sf::Color::Red );
	appleShape.setRadius( blockSize / 2 );

	for ( int i = 0; i < 4; ++i )
	{
		bounds[i].setFillColor( sf::Color( 150, 0, 0 ) );
		if ( !((i + 1) % 2) )
		{
			bounds[i].setSize( sf::Vector2f( windowSize.x, blockSize ) );
		}
		else
		{
			bounds[i].setSize( sf::Vector2f( blockSize, windowSize.y ) );
		}

		if ( i < 2 )
		{
			bounds->setPosition( 0, 0 );
		}
		else
		{
			bounds[i].setOrigin( bounds[i].getSize() );
			bounds[i].setPosition( sf::Vector2f( windowSize ) );
		}
	}
}

int World::GetBlockSize() const
{
	return blockSize;
}

void World::RespawnApple()
{
	int maxX = (windowSize.x / blockSize) - 2;
	int maxY = (windowSize.y / blockSize) - 2;

	item = sf::Vector2i( rand() % maxX + 1, rand() % maxY + 1 );

	appleShape.setPosition( item.x * blockSize, item.y * blockSize );
}

void World::Update( Snake & player, Textbox& textbox )
{
	if ( player.GetPosition() == item )
	{
		player.Extend();
		player.IncreaseScore();
		textbox.Add( "Ate an apple, score: " + std::to_string( player.Getscore() ) );
		RespawnApple();
	}

	int gridSizeX = windowSize.x / blockSize;
	int gridSizeY = windowSize.y / blockSize;

	if ( player.GetPosition().x <= 0 ||
		player.GetPosition().y <= 0 ||
		player.GetPosition().x >= gridSizeX - 1 ||
		player.GetPosition().y >= gridSizeY - 1 )
	{
		player.Lose();
		textbox.Add( "GAME OVER!, score: " + std::to_string( player.Getscore() ) );
	}
}

void World::Render( sf::RenderWindow & window )
{
	for ( int i = 0; i < 4; ++i )
	{
		window.draw( bounds[i] );
	}

	window.draw( appleShape );
}

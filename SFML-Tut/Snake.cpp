#include "Snake.h"

Snake::Snake( int blockSize )
	:
	size(blockSize)
{
	bodyRect.setSize( sf::Vector2f( size - 1, size - 1 ) );
	Reset();
}

void Snake::SetDirection( Direction dir )
{
	this->dir = dir;
}

Direction Snake::GetDirection() const
{
	return dir;
}

int Snake::GetSpeed() const
{
	return speed;
}

sf::Vector2i Snake::GetPosition() const
{
	return (!snakeBody.empty() ?
		snakeBody.front().position : sf::Vector2i( 1, 1 ));
}

int Snake::GetLives() const
{
	return lives;
}

int Snake::Getscore() const
{
	return score;
}

void Snake::IncreaseScore()
{
	score += 10;
}

bool Snake::HasLost() const
{
	return lost;
}

void Snake::Lose()
{
	lost = true;
}

void Snake::ToggleLost()
{
	lost = !lost;
}

void Snake::Extend()
{
	if ( !snakeBody.empty() )
	{
		SnakeSegment& tailHead = snakeBody[snakeBody.size() - 1];

		if ( snakeBody.size() > 1 )
		{
			SnakeSegment& tailBone = snakeBody[snakeBody.size() - 2];
		}
	}
}

void Snake::Reset()
{
	snakeBody.clear();

	snakeBody.push_back( SnakeSegment( 5, 7 ) );
	snakeBody.push_back( SnakeSegment( 5, 6 ) );
	snakeBody.push_back( SnakeSegment( 5, 5 ) );

	SetDirection( Direction::None );

	speed = 15;
	lives = 3;
	score = 0;
	lost = false;
}

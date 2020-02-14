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

Direction Snake::GetPhysicalDirection()
{
	if ( snakeBody.size() <= 1 )
	{
		return Direction::None;
	}
	SnakeSegment& head = snakeBody[0];
	SnakeSegment& neck = snakeBody[1];

	if ( head.position.x == neck.position.x )
	{
		return (head.position.y > neck.position.y ? Direction::Down : Direction::Up);
	}
	else if ( head.position.y == neck.position.y )
	{
		return (head.position.x > neck.position.x ? Direction::Right : Direction::Left);
	}
	return Direction::None;
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

			if ( tailHead.position.x == tailBone.position.x )
			{
				if ( tailHead.position.y > tailBone.position.y )
				{
					snakeBody.push_back( SnakeSegment( tailHead.position.x, tailHead.position.y + 1 ) );
				}
				else
				{
					snakeBody.push_back( SnakeSegment( tailHead.position.x, tailHead.position.y - 1 ) );
				}
			}
			else if ( tailHead.position.y == tailBone.position.y )
			{
				if ( tailHead.position.x > tailBone.position.x )
				{
					snakeBody.push_back( SnakeSegment( tailHead.position.x + 1, tailHead.position.y ) );
				}
				else
				{
					snakeBody.push_back( SnakeSegment( tailHead.position.x - 1, tailHead.position.y ) );
				}
			}
		}
		else
		{
			if ( dir == Direction::Up )
			{
				snakeBody.push_back( SnakeSegment( tailHead.position.x, tailHead.position.y + 1 ) );
			}
			else if ( dir == Direction::Down )
			{
				snakeBody.push_back( SnakeSegment( tailHead.position.x, tailHead.position.y - 1 ) );
			}
			else if ( dir == Direction::Left )
			{
				snakeBody.push_back( SnakeSegment( tailHead.position.x + 1, tailHead.position.y ) );
			}
			else if ( dir == Direction::Right )
			{
				snakeBody.push_back( SnakeSegment( tailHead.position.x - 1, tailHead.position.y ) );
			}
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

	speed = 5;
	lives = 3;
	score = 0;
	lost = false;
}

void Snake::Move()
{
	for ( unsigned int i = snakeBody.size() - 1; i > 0; --i )
	{
		snakeBody[i].position = snakeBody[i - 1].position;
	}

	if ( dir == Direction::Left )
	{
		--snakeBody[0].position.x;
	}
	else if ( dir == Direction::Right )
	{
		++snakeBody[0].position.x;
	}
	else if ( dir == Direction::Up )
	{
		--snakeBody[0].position.y;
	}
	else if ( dir == Direction::Down )
	{
		++snakeBody[0].position.y;
	}
}

void Snake::Tick()
{
	if ( !snakeBody.empty() )
	{
		if ( dir != Direction::None )
		{
			Move();
			CheckCollision();
		}
	}
}

void Snake::Cut( int segments )
{
	for ( int i = 0; i < segments; ++i )
	{
		snakeBody.pop_back();
	}
	--lives;

	if ( lives == 0 )
	{
		Lose();
	}
}

void Snake::Render( sf::RenderWindow & window )
{
	if ( !snakeBody.empty() )
	{
		auto head = snakeBody.begin();

		bodyRect.setFillColor( sf::Color::Yellow );
		bodyRect.setPosition( head->position.x * size, head->position.y * size );
		window.draw( bodyRect );

		bodyRect.setFillColor( sf::Color::Green );
		for ( auto itr = snakeBody.begin() + 1; itr != snakeBody.end(); ++itr )
		{
			bodyRect.setPosition( itr->position.x * size, itr->position.y * size );
			window.draw( bodyRect );
		}
	}
}

void Snake::CheckCollision()
{
	if ( snakeBody.size() >= 4 )
	{
		SnakeSegment& head = snakeBody.front();

		for ( auto itr = snakeBody.begin() + 1; itr != snakeBody.end(); ++itr )
		{
			if ( itr->position == head.position )
			{
				int segments = snakeBody.end() - itr;
				Cut( segments );
				break;
			}
		}
	}
}

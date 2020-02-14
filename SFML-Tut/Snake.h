#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class SnakeSegment
{
public:
	SnakeSegment( int x, int y ) : position( x, y ) {}
	sf::Vector2i position;
};

using SnakeContainer = std::vector<SnakeSegment>;

enum class Direction { None, Up, Down, Left, Right };

class Snake
{
public:
	Snake( int blockSize );
	~Snake() = default;

public:
	void SetDirection( Direction dir );
	Direction GetDirection() const;
	Direction GetPhysicalDirection();
	int GetSpeed() const;
	sf::Vector2i GetPosition() const;
	int GetLives() const;
	int Getscore() const;
	void IncreaseScore();
	bool HasLost() const;
	void Lose();
	void ToggleLost();
	void Extend();
	void Reset();
	void Move();
	void Tick();
	void Cut( int segments );
	void Render( sf::RenderWindow& window );

private:
	void CheckCollision();

private:
	SnakeContainer snakeBody;
	int size;
	Direction dir;
	int speed;
	int lives;
	int score = 0;
	bool lost;
	sf::RectangleShape bodyRect;
};
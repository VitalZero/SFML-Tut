#pragma once
#include <SFML/Graphics.hpp>

class Window
{
public:
	Window();
	Window( const std::string& title, const sf::Vector2u& size );
	~Window();

public:
	void BeginDraw();
	void EndDraw();
	void Update();
	bool IsDone() const;
	bool IsFullScreen() const;
	sf::Vector2u GetWindowSize() const;
	void ToggleFullScreen();
	void Draw( sf::Drawable& drawable );

private:
	void Setup( const std::string& title, const sf::Vector2u& size );
	void Destroy();
	void Create();

private:
	sf::RenderWindow window;
	sf::Vector2u windowSize;
	std::string windowTitle;
	bool isDone;
	bool isFullScreen;
};
#pragma once
#include <SFML/Graphics.hpp>
#include "EventManager.h"

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
	bool IsFocused() const;
	EventManager* GetEventManager() const;
	void ToggleFullScreen( EventDetails* details );
	void Close( EventDetails* details = nullptr );
	void Draw( sf::Drawable& drawable );
	sf::RenderWindow* GetRenderWindow();

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
	EventManager eventManager;
	bool hasFocus;
};
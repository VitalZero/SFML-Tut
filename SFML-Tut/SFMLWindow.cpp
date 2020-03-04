#include "SFMLWindow.h"

Window::Window() { Setup( "Window", sf::Vector2u( 640, 480 ) ); }

Window::Window( const std::string & title, const sf::Vector2u & size )
{
	Setup( title, size);
}

Window::~Window() { Destroy(); }

void Window::Setup( const std::string & title, const sf::Vector2u & size )
{
	hasFocus = true;

	eventManager.AddCallback( StateType(0), "Fullscreen_toggle", &Window::ToggleFullScreen, this );
	eventManager.AddCallback( StateType( 0 ), "Window_close", &Window::Close, this );

	windowTitle = title;
	windowSize = size;
	isFullScreen = false;
	isDone = false;
	Create();
}

void Window::Destroy() { window.close(); }

void Window::Create()
{
	sf::Uint32 style = (isFullScreen ? sf::Style::Fullscreen : sf::Style::Default);
	window.create( { windowSize.x, windowSize.y, 32 }, windowTitle, style );
}

void Window::BeginDraw()
{
	window.clear( sf::Color::Black );
}

void Window::EndDraw()
{
	window.display();
}

void Window::Update()
{
	sf::Event event;
	while ( window.pollEvent( event ) )
	{
		if ( event.type == sf::Event::LostFocus )
		{
			hasFocus = false;
			eventManager.SetFocus( false );
		}
		else if ( event.type == sf::Event::GainedFocus )
		{
			hasFocus = true;
			eventManager.SetFocus( true );
		}
		eventManager.HandleEvent( event );
	}
	eventManager.Update();
}

bool Window::IsDone() const { return isDone; }

bool Window::IsFullScreen() const { return isFullScreen; }

sf::Vector2u Window::GetWindowSize() const { return windowSize; }

bool Window::IsFocused() const
{
	return hasFocus;
}

EventManager * Window::GetEventManager()
{
	return &eventManager;
}

void Window::ToggleFullScreen( EventDetails* details )
{
	isFullScreen = !isFullScreen;
	Destroy();
	Create();
}

void Window::Close( EventDetails * details )
{
	isDone = true;
}

void Window::Draw( sf::Drawable & drawable )
{
	window.draw( drawable );
}

sf::RenderWindow* Window::GetRenderWindow()
{
	return &window;
}

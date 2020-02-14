#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <utility>
#include <unordered_map>
#include <functional>

enum class EventType
{
	KeyDown = sf::Event::KeyPressed,
	KeyUp = sf::Event::KeyReleased,
	MButtonDown = sf::Event::MouseButtonPressed,
	MButtonUp = sf::Event::MouseButtonReleased,
	MouseWheel = sf::Event::MouseWheelMoved,
	WindowResized = sf::Event::Resized,
	GainedFocus = sf::Event::GainedFocus,
	LostFocus = sf::Event::LostFocus,
	MouseEntered = sf::Event::MouseEntered,
	MouseLeft = sf::Event::MouseLeft,
	Closed = sf::Event::Closed,
	TextEndered = sf::Event::TextEntered,
	Keyboard = sf::Event::Count + 1,
	Mouse,
	Joystick
};

struct EventInfo
{
	EventInfo() { code = 0; }
	EventInfo( int event ) 
	{
		code = event;
	}
	int code;
};

using Events = std::vector<std::pair<EventType, EventInfo>>;

class EventDetails
{
public:
	EventDetails( const std::string& name )
		:
		name( name )
	{
		Clear();
	}
	void Clear()
	{
		size = sf::Vector2i( 0, 0 );
		textEntered = 0;
		mouse = sf::Vector2i( 0, 0 );
		mouseWheelData = 0;
		keyCode = -1;
	}

public:
	std::string name;
	sf::Vector2i size;
	sf::Uint32 textEntered;
	sf::Vector2i mouse;
	int mouseWheelData;
	int keyCode;
};

class Binding
{
public:
	Binding(const std::string& name)
		:
		name ( name),
		details(name)
	{
	}
	void EventInfo( EventType type, EventInfo info )
	{
		events.emplace_back( type, info );
	}
public:
	Events events;
	std::string name = "";
	int c;
	EventDetails details;
};

using Bindings = std::unordered_map<std::string, Binding*>;
using Callbacks = std::unordered_map<std::string, std::function<void( EventDetails* )>>;


class EventManager
{
public:
	EventManager();
	~EventManager();

public:
	bool AddBinding( Binding* binding );
	bool RemoveBinding( const std::string& name );
	void SetFocus( const bool focus );
	template<typename T>
	bool AddCallback( const std::string& name, void(T::*func)(EventDetails*), T* instance )
	{
		auto temp = std::bind( func, instance, std::placeholders_1 );
		return callbacks.emplace( name, temp ).second;
	}
	void RemoveCallback(const std::string& name);
	void HandleEvent( sf::Event& event );
	void Update();
	sf::Vector2i GetMousePos( sf::RenderWindow* window = nullptr );

private:
	void LoadBindings();

private:
	Bindings bindings;
	Callbacks callbacks;
	bool hasFocus;

};
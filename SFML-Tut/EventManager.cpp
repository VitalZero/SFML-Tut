#include "EventManager.h"

EventManager::EventManager()
	:
	hasFocus(true)
{
	LoadBindings();
}

EventManager::~EventManager()
{
	for ( auto& itr : bindings )
	{
		delete itr.second;
		itr.second = nullptr;
	}
}

bool EventManager::AddBinding( Binding * binding )
{
	if ( bindings.find( binding->name ) != bindings.end() )
	{
		return false;
	}

	return bindings.emplace( binding->name, binding ).second;
}

bool EventManager::RemoveBinding( const std::string & name )
{
	auto itr = bindings.find( name );
	if ( itr == bindings.end() )
	{
		return false;
	}

	delete itr->second;
	bindings.erase( itr );

	return true;
}

void EventManager::SetFocus( const bool focus )
{
	hasFocus = focus;
}

void EventManager::RemoveCallback( const std::string & name )
{
	callbacks.erase( name );
}

void EventManager::HandleEvent( sf::Event & event )
{
	for ( auto& itrBind : bindings )
	{
		Binding* bind = itrBind.second;

		for ( auto& itrEvent : bind->events )
		{
			EventType sfmlEvent = (EventType)event.type;
			if ( itrEvent.first != sfmlEvent )
			{
				continue;
			}
			if ( sfmlEvent == EventType::KeyDown || sfmlEvent == EventType::KeyUp )
			{
				if ( itrEvent.second.code == event.key.code )
				{
					if ( bind->details.keyCode != -1 )
					{
						bind->details.keyCode = itrEvent.second.code;
					}
					++(bind->c);
					break;
				}
			}
			else if ( sfmlEvent == EventType::MButtonDown || sfmlEvent == EventType::MButtonUp )
			{
				if ( itrEvent.second.code == event.mouseButton.button )
				{
					bind->details.mouse.x = event.mouseButton.x;
					bind->details.mouse.y = event.mouseButton.y;

					if ( bind->details.keyCode != -1 )
					{
						bind->details.keyCode = itrEvent.second.code;
					}
					++(bind->c);
					break;
				}
			}
			else
			{
				if ( sfmlEvent == EventType::MouseWheel )
				{
					bind->details.mouseWheelData = event.mouseWheel.delta;
				}
				else if ( sfmlEvent == EventType::WindowResized )
				{
					bind->details.size.x = event.size.width;
					bind->details.size.y = event.size.height;
				}
				else if ( sfmlEvent == EventType::TextEndered )
				{
					bind->details.textEntered = event.text.unicode;
				}
				++(bind->c);
			}
		}
	}
}

void EventManager::Update()
{
	if ( hasFocus ) {}

	for ( auto& itrBind : bindings )
	{
		Binding* bind = itrBind.second;

		for ( auto& itrEvent : bind->events )
		{
			switch ( itrEvent.first )
			{
			case EventType::Keyboard:
				if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Key(itrEvent.second.code) ) )
				{
					if ( bind->details.keyCode != -1 )
					{
						bind->details.keyCode = itrEvent.second.code;
					}
					++(bind->c);
				}
				break;
			case EventType::Mouse:
				if ( sf::Mouse::isButtonPressed( sf::Mouse::Button( itrEvent.second.code ) ) )
				{
					if ( bind->details.keyCode != -1 )
					{
						bind->details.keyCode = itrEvent.second.code;
					}
					++(bind->c);
				}
				break;
			case EventType::Joystick:
				break;

			default:
				break;
			}
		}

		if ( bind->events.size() == bind->c )
		{
			auto callItr = callbacks.find( bind->name );
			if ( callItr != callbacks.end() )
			{
				callItr->second( &bind->details );
			}
		}
		bind->c = 0;
		bind->details.Clear();
	}
}

sf::Vector2i EventManager::GetMousePos( sf::RenderWindow* window )
{
	return (window ? sf::Mouse::getPosition( *window ) : sf::Mouse::getPosition());
}

void EventManager::LoadBindings()
{
}

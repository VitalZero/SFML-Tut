#include "EventManager.h"
#include <fstream>
#include <iostream>
#include <sstream>

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

bool EventManager::RemoveCallback( StateType state, const std::string & name )
{
	auto itrCallb = callbacks.find( state );
	if ( itrCallb == callbacks.end() )
	{
		return false;
	}
	auto itrCallb2 = itrCallb->second.find( name );
	if ( itrCallb2 == itrCallb->second.end() )
	{
		return false;
	}

	itrCallb->second.erase( name );

	return true;
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
	if ( hasFocus )
	{
		for ( auto& itrBind : bindings )
		{
			Binding* bind = itrBind.second;

			for ( auto& itrEvent : bind->events )
			{
				switch ( itrEvent.first )
				{
				case EventType::Keyboard:
					if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Key( itrEvent.second.code ) ) )
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
				auto stateCallbacks = callbacks.find( currentState );
				auto otherCallbacks = callbacks.find( StateType( 0 ) );

				if ( stateCallbacks != callbacks.end() )
				{
					auto callItr = stateCallbacks->second.find( bind->name );
					if ( callItr != stateCallbacks->second.end() )
					{
						callItr->second( &bind->details );
					}
				}

				if ( otherCallbacks != callbacks.end() )
				{
					auto callItr = otherCallbacks->second.find( bind->name );
					if ( callItr != otherCallbacks->second.end() )
					{
						callItr->second( &bind->details );
					}
				}
			}
			bind->c = 0;
			bind->details.Clear();
		}
	}
}

sf::Vector2i EventManager::GetMousePos( sf::RenderWindow* window )
{
	return (window ? sf::Mouse::getPosition( *window ) : sf::Mouse::getPosition());
}

void EventManager::LoadBindings()
{
	std::string delimiter = ":";

	std::ifstream bindings;
	bindings.open( "keys.cfg" );
	if ( bindings )
	{
		std::string line;
		while ( std::getline( bindings, line ) )
		{
			std::stringstream keyStream( line );
			std::string callbackName;

			keyStream >> callbackName;

			Binding* bind = new Binding( callbackName );

			while ( !keyStream.eof() )
			{
				std::string keyVal;
				keyStream >> keyVal;
				
				int start = 0;
				int end = keyVal.find( delimiter );

				if ( end == std::string::npos )
				{
					delete bind;
					bind = nullptr;
					break;
				}

				EventType type = (EventType)std::stoi( keyVal.substr( start, end - start ) );
				int code = std::stoi( keyVal.substr( end + delimiter.length() ) );
				EventInfo eventInfo;

				eventInfo.code = code;

				bind->BindEvent( type, eventInfo );
			}

			if ( !AddBinding( bind ) )
			{
				delete bind;
			}
			bind = nullptr;
		}
		bindings.close();
	}
	else
	{
		std::cerr << "Failed to load cfg file" << std::endl;
	}


}

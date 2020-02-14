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

sf::Vector2i EventManager::GetMousePos( sf::RenderWindow* window )
{
	return (window ? sf::Mouse::getPosition( *window ) : sf::Mouse::getPosition());
}

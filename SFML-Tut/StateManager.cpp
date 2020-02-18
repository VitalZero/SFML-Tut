#include "StateManager.h"

StateManager::StateManager( SharedContext * shared )
	:
	shared(shared)
{
	RegisterState<State_Intro>( StateType::Intro );
	RegisterState<State_MainMenu>( StateType::MainMenu );
	RegisterState<State_Game>( StateType::Game );
	RegisterState<State_Paused>( StateType::Paused );
}

StateManager::~StateManager()
{
	for ( auto& itr : states )
	{
		itr.second->OnDestroy();
		delete itr.second;
	}
}

void StateManager::Update( const sf::Time & time )
{
	if ( !states.empty() )
	{
		if ( states.back().second->IsTrascendent() &&
			states.size() > 1 )
		{
			auto itrState = states.end();
			while ( itrState != states.begin() )
			{
				if ( itrState != states.end() )
				{
					if ( !itrState->second->IsTrascendent() )
					{
						break;
					}
				}
				--itrState;
			}
			for ( ; itrState != states.end(); ++itrState )
			{
				itrState->second->Update( time );
			}
		}
		else
		{
			states.back().second->Update( time );
		}
	}
}

void StateManager::Draw()
{
	if ( !states.empty() )
	{
		if ( states.back().second->IsTransparent() &&
			states.size() > 1 )
		{
			auto itrState = states.end();
			while ( itrState != states.begin() )
			{
				if ( itrState != states.end() )
				{
					if ( !itrState->second->IsTransparent() )
					{
						break;
					}
				}
				--itrState;
			}
			for ( ; itrState != states.end(); ++itrState )
			{
				itrState->second->Draw();
			}
		}
		else
		{
			states.back().second->Draw();
		}
	}
}

SharedContext * StateManager::GetContext() const
{
	return shared;
}

bool StateManager::HasState( const StateType & type ) const
{
	for ( auto itrState = states.begin(); itrState != states.end(); ++itrState )
	{
		if ( itrState->first == type )
		{
			auto removed = std::find( toRemove.begin(), toRemove.end(), type );

			if ( removed == toRemove.end() )
			{
				return true;
			}
			return false;
		}
	}
	return false;
}

void StateManager::Remove( const StateType & type )
{
	toRemove.push_back( type );
}

#include "StateManager.h"
#include "StateIntro.h"
#include "StateMainMenu.h"
#include "StateGame.h"

StateManager::StateManager( SharedContext * shared )
	:
	shared(shared)
{
	RegisterState<StateIntro>( StateType::Intro );
	RegisterState<StateMainMenu>( StateType::MainMenu );
	RegisterState<StateGame>( StateType::Game );
	//RegisterState<State_Paused>( StateType::Paused );
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

void StateManager::ProcessRequests()
{
	while ( toRemove.begin() != toRemove.end() )
	{
		RemoveState( *toRemove.begin() );
		toRemove.erase( toRemove.begin() );
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

void StateManager::SwitchTo( const StateType & state )
{
	shared->eventManager->SetCurrentState( state );
	for ( auto itrStates = states.begin(); itrStates != states.end(); ++itrStates )
	{
		if ( itrStates->first == state )
		{
			states.back().second->Deactivate();
			StateType tmpType = itrStates->first;

			BaseState* tmpState = itrStates->second;
			states.erase( itrStates );
			states.emplace_back( tmpType, tmpState );
			tmpState->Activate();
			break;
		}
	}
	if ( !states.empty() )
	{
		states.back().second->Deactivate();
	}
	CreateState( state );
	states.back().second->Activate();
}

void StateManager::Remove( const StateType & type )
{
	toRemove.push_back( type );
}

void StateManager::CreateState( const StateType & type )
{
	auto newState = stateFactory.find( type );
	if ( newState != stateFactory.end() )
	{
		BaseState* tmpState = newState->second();
		states.emplace_back( type, tmpState );
		tmpState->OnCreate();
	}
}

void StateManager::RemoveState( const StateType & type )
{
	for ( auto itrState = states.begin(); itrState != states.end(); ++itrState )
	{
		if ( itrState->first == type )
		{
			itrState->second->OnDestroy();
			delete itrState->second;
			states.erase( itrState );
			break;
		}
	}
}

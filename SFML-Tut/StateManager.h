#pragma once
#include "BaseState.h"
#include "SFMLWindow.h"
#include "EventManager.h"
#include "SharedContext.h"
#include <vector>
#include <unordered_map>

enum class StateType
{
	Intro = 1,
	MainMenu,
	Game,
	Paused,
	GameOver,
	Credits
};

using StateContainer = std::vector<std::pair<StateType, BaseState*>>;
using TypeContainer = std::vector<StateType>;
using StateFactory = std::unordered_map<StateType, std::function<BaseState*(void)>>;

class StateManager
{
public:
	StateManager( SharedContext* shared );
	~StateManager();

public:
	void Update( const sf::Time& time );
	void Draw();
	void ProcessRequests();
	SharedContext* GetContext() const;
	bool HasState( const StateType& type ) const;
	void SwitchTo( const StateType& type );
	void Remove( const StateType& type );

private:
	void CreateState( const StateType& type );
	void RemoveState( const StateType& type );
	template<class T>
	void RegisterState( const StateType& type ) 
	{
		stateFactory[type] = [this]()->BaseState* 
		{
			return new T(this);
		};
	};

private:
	SharedContext* shared;
	StateContainer states;
	TypeContainer toRemove;
	StateFactory stateFactory;
};
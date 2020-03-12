#pragma once
#include <SFML/Graphics.hpp>

class StateManager;

class BaseState
{
	friend class StateManager;
public:
	BaseState( StateManager* stateManager )
		:
		stateManager( stateManager ),
		transparent(false),
		trascendent(false)
	{
	}
	virtual ~BaseState() {}

public:
	virtual void OnCreate() = 0;
	virtual void OnDestroy() = 0;
	virtual void Activate() = 0;
	virtual void Deactivate() = 0;
	virtual void Update(const sf::Time& time) = 0;
	virtual void Draw() = 0;

public:
	void SetTransparent( bool transparent )
	{
		this->transparent = transparent;
	}
	void SetTrascendent( bool trascendent )
	{
		this->trascendent = trascendent;
	}
	bool IsTransparent() const { return transparent; }
	bool IsTrascendent() const { return trascendent; }
	StateManager* GetStateManager() const { return stateManager; }
	sf::View& GetView() { return view; }

protected:
	StateManager* stateManager;
	bool transparent;
	bool trascendent;
	sf::View view;
};
#pragma once
#include "Component.h"
#include "COGFiniteStateMachine_State.h"
#include <vector>

class COGFiniteStateMachine_State;

class COGFiniteStateMachine : public Component
{
public:
	static std::vector<COGFiniteStateMachine*> mStateMachineComponents;

private:
	COGFiniteStateMachine_State * mCurrentState;
	COGFiniteStateMachine_State* mNextState;

public:
	COGFiniteStateMachine(GameObject* pGameObject);
	~COGFiniteStateMachine();

	void Initialize(COGFiniteStateMachine_State* pInitialState);
	void SetState(COGFiniteStateMachine_State* pStateToSetTo);
	void Update(float fDeltaTime);

	// Overridden Functions
	virtual void Destroy() override;
	virtual ComponentType GetType() const override;

	// Templated Functions
	template<class T>
	T* CreateState()
	{
		// Used for creating an instance of the states
		return new T(mGameObject, this);
	}
};
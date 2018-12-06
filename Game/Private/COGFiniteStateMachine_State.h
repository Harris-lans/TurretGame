#pragma once
#include "Component.h"
#include "COGFiniteStateMachine.h"

class COGFiniteStateMachine;

class COGFiniteStateMachine_State : public Component
{
protected:
	COGFiniteStateMachine_State(GameObject* pGameObject, COGFiniteStateMachine* pFiniteStateMachine );

public:
	~COGFiniteStateMachine_State();

	virtual void OnEnterState();
	virtual void OnExitState();

	virtual void Update(float fDeltaTime) = 0;

	// Overridden Functions
	virtual void Destroy() override;
	virtual ComponentType GetType() const override;

protected:
	COGFiniteStateMachine * mFiniteStateMachine;
};
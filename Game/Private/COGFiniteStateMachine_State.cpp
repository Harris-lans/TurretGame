#include "COGFiniteStateMachine_State.h"


COGFiniteStateMachine_State::COGFiniteStateMachine_State(GameObject* pGameObject, COGFiniteStateMachine* pFiniteStateMachine)
	:Component(pGameObject)
{
	mFiniteStateMachine = pFiniteStateMachine;
}

COGFiniteStateMachine_State::~COGFiniteStateMachine_State()
{
	Destroy();
}

void COGFiniteStateMachine_State::Destroy()
{
	// Removing self from the component list of the gameObject
	mGameObject->RemoveComponent(this);
}

ComponentType COGFiniteStateMachine_State::GetType() const
{
	return ComponentType::FiniteStateMachine_State;
}

void COGFiniteStateMachine_State::OnEnterState()
{
	// Empty as this serves as an abstract class for states
}

void COGFiniteStateMachine_State::OnExitState()
{
	// Empty as this serves as an abstract class for states
}
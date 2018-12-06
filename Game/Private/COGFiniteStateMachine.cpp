#include "COGFiniteStateMachine.h"
#include <algorithm>
#include <assert.h>

std::vector<COGFiniteStateMachine*> COGFiniteStateMachine::mStateMachineComponents;

COGFiniteStateMachine::COGFiniteStateMachine(GameObject* pGameObject)
	:Component(pGameObject)
{
	mStateMachineComponents.push_back(this);
}

COGFiniteStateMachine::~COGFiniteStateMachine()
{
	// Destroying the Component
	Destroy();
}

void COGFiniteStateMachine::Initialize(COGFiniteStateMachine_State* pInitialState)
{
	// Checking if the currentstate has been already set
	//assert(mCurrentState != nullptr);

	// Setting the initial state of the state machine
	mCurrentState = pInitialState;
	pInitialState->Initialize();
	mCurrentState->OnEnterState();
}

void COGFiniteStateMachine::Destroy()
{
	// Removing the component from the static vector
	mStateMachineComponents.erase(std::remove(mStateMachineComponents.begin(), mStateMachineComponents.end(), this), mStateMachineComponents.end());

	// Removing self from the component list of the gameObject
	mGameObject->RemoveComponent(this);
}

ComponentType COGFiniteStateMachine::GetType() const
{
	return ComponentType::FiniteStateMachine;
}

void COGFiniteStateMachine::SetState(COGFiniteStateMachine_State* pStateToChangeTo)
{
	if (mNextState != nullptr)
	{
		delete mNextState;
	}

	mNextState = pStateToChangeTo;
	pStateToChangeTo->Initialize();
}

void COGFiniteStateMachine::Update(float fDeltaTime)
{
	// Checking if it is time to change to the next state
	if (mNextState != nullptr)
	{
		mCurrentState->OnExitState();
		delete mCurrentState;

		mCurrentState = mNextState;
		mCurrentState->OnEnterState();

		mNextState = nullptr;
	}

	mCurrentState->Update(fDeltaTime);
}
#pragma once
#include "COGFiniteStateMachine_State.h"
#include "COGTurret.h"
#include "GameObjectManager.h"
#include "InputManager.h"

class COGPulseDisruption_TurretState : public COGFiniteStateMachine_State
{
public:
	COGPulseDisruption_TurretState(GameObject* pGameObject, COGFiniteStateMachine* pFiniteStateMachine);
	~COGPulseDisruption_TurretState();

	// Overriden Pure Virtual Functions
	virtual void Initialize() override;
	virtual void OnEnterState() override;
	virtual void Update(float fDeltaTime) override;

private:
	const float FIRE_DELAY = 3.0f;

	GameObjectManager * mGameObjectManager;
	InputManager* mInputManager;
	COGTurret* mTurretComponent;
};
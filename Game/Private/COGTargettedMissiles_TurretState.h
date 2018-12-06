#pragma once
#include "COGFiniteStateMachine_State.h"
#include "COGTurret.h"
#include "GameObjectManager.h"
#include "InputManager.h"

class COGTargettedMissiles_TurretState : public COGFiniteStateMachine_State
{
public:
	COGTargettedMissiles_TurretState(GameObject* pGameObject, COGFiniteStateMachine* pFiniteStateMachine);
	~COGTargettedMissiles_TurretState();

	// Overriden Pure Virtual Functions
	virtual void Initialize() override;
	virtual void OnEnterState() override;
	virtual void Update(float fDeltaTime) override;

private:
	const float FIRE_DELAY = 2.0f;

	GameObjectManager * mGameObjectManager;
	InputManager* mInputManager;
	COGTurret* mTurretComponent;
};
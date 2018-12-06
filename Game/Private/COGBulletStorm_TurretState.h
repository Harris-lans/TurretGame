#pragma once
#include "COGFiniteStateMachine_State.h"
#include "COGTurret.h"
#include "GameObjectManager.h"
#include "InputManager.h"

class COGBulletStorm_TurretState : public COGFiniteStateMachine_State
{
public:
	COGBulletStorm_TurretState(GameObject* pGameObject, COGFiniteStateMachine* pFiniteStateMachine);
	~COGBulletStorm_TurretState();

	// Overriden Pure Virtual Functions
	virtual void Initialize() override;
	virtual void OnEnterState() override;
	virtual void Update(float fDeltaTime) override;

private:
	const float FIRE_DELAY = 0.1f;

	GameObjectManager * mGameObjectManager;
	InputManager* mInputManager;
	COGTurret* mTurretComponent;
};
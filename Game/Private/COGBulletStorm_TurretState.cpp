#include "COGBulletStorm_TurretState.h"
#include "COGPulseDisruption_TurretState.h"
#include "COGTargettedMissiles_TurretState.h"

COGBulletStorm_TurretState::COGBulletStorm_TurretState(GameObject* pGameObject, COGFiniteStateMachine* pFiniteStateMachine)
	:COGFiniteStateMachine_State(pGameObject, pFiniteStateMachine)
{
	mGameObjectManager = GameObjectManager::GetInstance();
	mInputManager = InputManager::GetInstance();
}

COGBulletStorm_TurretState::~COGBulletStorm_TurretState()
{
	Destroy();
}

void COGBulletStorm_TurretState::Initialize()
{
	// Finding the Turret Component
	mTurretComponent = mGameObject->FindComponent<COGTurret>(ComponentType::Turret);
}

void COGBulletStorm_TurretState::OnEnterState()
{
	Console::LogString("Entered Bullet Storm State\n");

	// Changing the settings of the turret according to the bullet storm state
	std::string newTag = "Bullet Storm";
	mTurretComponent->SetStateTag(newTag);
	mTurretComponent->SetFireDelay(FIRE_DELAY);
}

void COGBulletStorm_TurretState::Update(float fDeltaTime)
{
	if (mInputManager->GetInputState()->HoldingFireButton())
	{
		// Fire Bullets
		mTurretComponent->FireBulletStorm();
	}

	// Checking if the turret should change state
	//===========================================
	if (mInputManager->GetInputState()->PressedPulseDisruptionButton())
	{
		// Switch to Pulse Disruption State
		mFiniteStateMachine->SetState(mFiniteStateMachine->CreateState<COGPulseDisruption_TurretState>());
	}
	else if (mInputManager->GetInputState()->PressedTargettedMissilesButton())
	{
		// Switch to Targetted Missile
		mFiniteStateMachine->SetState(mFiniteStateMachine->CreateState<COGTargettedMissiles_TurretState>());
	}
}
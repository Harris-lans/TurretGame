#include "COGTargettedMissiles_TurretState.h"
#include "COGBulletStorm_TurretState.h"
#include "COGPulseDisruption_TurretState.h"

COGTargettedMissiles_TurretState::COGTargettedMissiles_TurretState(GameObject* pGameObject, COGFiniteStateMachine* pFiniteStateMachine)
	:COGFiniteStateMachine_State(pGameObject, pFiniteStateMachine)
{
	mGameObjectManager = GameObjectManager::GetInstance();
	mInputManager = InputManager::GetInstance();
}

COGTargettedMissiles_TurretState::~COGTargettedMissiles_TurretState()
{
	Destroy();
}

void COGTargettedMissiles_TurretState::Initialize()
{
	// Finding the Turret Component
	mTurretComponent = mGameObject->FindComponent<COGTurret>(ComponentType::Turret);
}

void COGTargettedMissiles_TurretState::OnEnterState()
{
	Console::LogString("Entered Targetted Missile State\n");

	// Changing the settings of the turret according to the missile state
	std::string newTag = "Targetted Missiles";
	mTurretComponent->SetStateTag(newTag);
	mTurretComponent->SetFireDelay(FIRE_DELAY);
}

void COGTargettedMissiles_TurretState::Update(float fDeltaTime)
{
	if (mInputManager->GetInputState()->PressedFireButton())
	{
		// Firing Targetted Missiles
		mTurretComponent->FireTargettedMissiles();
	}

	// Checking if the turret should change state
	// ==========================================
	if (mInputManager->GetInputState()->PressedBulletStormButton())
	{
		// Switch to BulletStorm State
		mFiniteStateMachine->SetState(mFiniteStateMachine->CreateState<COGBulletStorm_TurretState>());
	}
	else if (mInputManager->GetInputState()->PressedPulseDisruptionButton())
	{
		// Switch to Pulse Disruptions
		mFiniteStateMachine->SetState(mFiniteStateMachine->CreateState<COGPulseDisruption_TurretState>());
	}
}
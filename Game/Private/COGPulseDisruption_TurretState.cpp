#include "COGPulseDisruption_TurretState.h"
#include "COGBulletStorm_TurretState.h"
#include "COGTargettedMissiles_TurretState.h"

COGPulseDisruption_TurretState::COGPulseDisruption_TurretState(GameObject* pGameObject, COGFiniteStateMachine* pFiniteStateMachine)
	:COGFiniteStateMachine_State(pGameObject, pFiniteStateMachine)
{
	mGameObjectManager = GameObjectManager::GetInstance();
	mInputManager = InputManager::GetInstance();
}

COGPulseDisruption_TurretState::~COGPulseDisruption_TurretState()
{
	Destroy();
}

void COGPulseDisruption_TurretState::Initialize()
{
	// Finding the Turret Component
	mTurretComponent = mGameObject->FindComponent<COGTurret>(ComponentType::Turret);
}

void COGPulseDisruption_TurretState::OnEnterState()
{
	Console::LogString("Entered Pulse Disruption State\n");

	// Changing the settings of the turret according to the pulse state
	std::string newTag = "Pulse Disruption";
	mTurretComponent->SetStateTag(newTag);
	mTurretComponent->SetFireDelay(FIRE_DELAY);
}

void COGPulseDisruption_TurretState::Update(float fDeltaTime)
{
	if (mInputManager->GetInputState()->PressedFireButton())
	{
		// Spawn Pulse Disruptions
		mTurretComponent->FirePulseDisruptions();

	}

	// Checking if the turret should change state
	//===========================================
	if (mInputManager->GetInputState()->PressedBulletStormButton())
	{
		// Switch to BulletStorm State
		mFiniteStateMachine->SetState(mFiniteStateMachine->CreateState<COGBulletStorm_TurretState>());
	}
	else if (mInputManager->GetInputState()->PressedTargettedMissilesButton())
	{
		// Switch to Targetted Missile
		mFiniteStateMachine->SetState(mFiniteStateMachine->CreateState<COGTargettedMissiles_TurretState>());
	}
}
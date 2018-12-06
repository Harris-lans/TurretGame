//
// * ENGINE-X
// * SAMPLE GAME
//
// + Game.cpp
// implementation of MyGame, an implementation of exGameInterface
//

#include "Game/Private/Game.h"
#include "Engine/Public/EngineInterface.h"
#include "Engine/Public/SDL.h"
#include <time.h>

#include "COGPhysics.h"
#include "COGBulletStorm_TurretState.h"
#include "COGPulseDisruption_TurretState.h"
#include "COGDamageOnCollisionWithTurret.h"
#include "COGTargettedMissiles_TurretState.h"

//-----------------------------------------------------------------
//-----------------------------------------------------------------

const char* gWindowName = "Let Them Come";
const float CITY_HEIGHT = 30.0f;
const float CITY_WIDTH = 100.0f;
const int MAXIUMUM_NUMBER_OF_ENEMY_MISSILES = 2;
//-----------------------------------------------------------------
//-----------------------------------------------------------------

MyGame::MyGame()
	: mEngine( nullptr )
	, mFontID( -1 )
	,mGameOver(false)
	,mGameOverText("")
{
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

MyGame::~MyGame()
{
	mGameObjectManager->ClearAllGameObjects();
	mGameObjectManager->DeleteInstance();
	mInputManager->DeleteInstance();
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MyGame::Initialize( exEngineInterface* pEngine )
{
	srand(time(NULL));

	mEngine = pEngine;
	mGameObjectManager = GameObjectManager::GetInstance();
	mGameObjectManager->Initialize(mEngine);
	mInputManager = InputManager::GetInstance();

	InitializeGame();

	mFontID = mEngine->LoadFont("randomFont.ttf", 15.0f);

	mGameOverTextPosition = { (kViewportWidth / 2) , (kViewportHeight / 2) };
	mScoreFontColor.SetColor(255, 255, 0, 255);
	mSelectedWeaponTextColor.SetColor(255, 0, 0);
	mHealthColor.SetColor(0, 255, 0);
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

const char* MyGame::GetWindowName() const
{
	return gWindowName;
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MyGame::GetClearColor( exColor& color ) const
{
	color.mColor[0] = 0;
	color.mColor[1] = 0;
	color.mColor[2] = 0;
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MyGame::OnEvent( SDL_Event* pEvent )
{

}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MyGame::OnEventsConsumed()
{

}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MyGame::Run( float fDeltaT )
{		
	mInputManager->Update();
	mGameObjectManager->Update(fDeltaT);
	mGameObjectManager->Render();
		
	// Running the game until the turret is valid
	if (mTurret.IsValid() && !mGameOver)
	{
		// Updating Turret and enmy spawner only when the turret is alive
		mTurretComponent->Update(fDeltaT);
		mEnemySpawnerComponent->Update(fDeltaT);

		// Displaying the turret stats
		// ===========================

		// Displaying the Health of the Turret
		std::string healthStats = "Health: " + std::to_string(mTurretComponent->GetHealth());
		const char*	healthStatsText = healthStats.c_str();
		// Changing Colors depending upon current health
		if (mTurretComponent->GetHealth() > 30)
		{
			mEngine->DrawText(mFontID, { 10, 50 }, healthStatsText, mHealthColor, 10);
		}
		else
		{
			mEngine->DrawText(mFontID, { 10, 50 }, healthStatsText, mSelectedWeaponTextColor, 10);
		}

		// Displaying the pulses left in the turret
		std::string pulseStats = "Pulses left: " + std::to_string(mTurretComponent->GetPulsesLeft());
		const char*	pulseStatsText = pulseStats.c_str();
		mEngine->DrawText(mFontID, { 10, 100 }, pulseStatsText, mScoreFontColor, 10);

		// Displaying the missiles left in the turret
		std::string missileStats = "Missiles Left: " + std::to_string(mTurretComponent->GetMissilesLeft());
		const char*	missileStatsText = missileStats.c_str();
		mEngine->DrawText(mFontID, { 10, 150 }, missileStatsText, mScoreFontColor, 10);

		// Displaying the selected weapon
		std::string selectedWeapon = mTurretComponent->GetStateTag();
		const char* selectedWeaponText = selectedWeapon.c_str();
		mEngine->DrawText(mFontID, { 3, 400 }, selectedWeaponText, mSelectedWeaponTextColor, 10);

	}
	else if (!mTurret.IsValid() && !mGameOver)
	{
		mGameOver = true;

		// Deleting all game objects after the turret is destroyed
		mGameObjectManager->ClearAllGameObjects();
		// Loading Bigger Fonts to show the Game Over Screen
		mFontID = mEngine->LoadFont("randomFont.ttf", 40.0f);
	}

	if (mGameOver)
	{
		mGameOverText = "Your Turret has been Destroyed!";
		const char* gameOverTextChar = mGameOverText.c_str();
		mEngine->DrawText(mFontID, { kViewportWidth / 5 - 100, kViewportHeight / 2 }, gameOverTextChar, mScoreFontColor, 10);
	}
}


void MyGame::InitializeGame()
{
	// Creating Turret
	mTurret = CreateTurret({ 0 , (kViewportHeight/2) });
	mTurretComponent = mTurret.Get()->FindComponent<COGTurret>(ComponentType::Turret);

	// Creating Turret Boundary
	CreateTurretBoundary();

	// Creating Enemy Spawner
	mEnemySpawner = CreateEnemySpawner();
	mEnemySpawnerComponent = mEnemySpawner.Get()->FindComponent<COGEnemySpawner>(ComponentType::EnemySpawner);
}

GameObjectHandle MyGame::CreateTurret(exVector2 pTurretPosition)
{
	GameObjectHandle turret = mGameObjectManager->CreateGameObject();
	GameObject* pTurret = turret.Get();

	exColor turretColor;
	turretColor.SetColor(128, 128, 128);

	// Adding the required Components
	pTurret->AddComponent(new COGTransform(pTurret, pTurretPosition));
	COGBoxShape* pTurretBoxShapeComponent = new COGBoxShape(mEngine, pTurret, 100.0f, 30.0f, turretColor);
	pTurret->AddComponent(pTurretBoxShapeComponent);
	COGFiniteStateMachine* pTurretStateMachine = new COGFiniteStateMachine(pTurret);
	pTurret->AddComponent(pTurretStateMachine);
	//pTurretStateMachine->SetState(pTurretStateMachine->CreateState<COGBulletStorm_TurretState>());
	COGTurret* pTurretComponent = new COGTurret(pTurret, mEngine, 20, 5, 100);
	pTurret->AddComponent(pTurretComponent);

	// Initializing the components
	pTurretBoxShapeComponent->Initialize();
	pTurretStateMachine->Initialize(pTurretStateMachine->CreateState<COGBulletStorm_TurretState>());
	pTurretComponent->Initialize();

	return turret;
}

GameObjectHandle MyGame::CreateTurretBoundary()
{
	GameObjectHandle turretBoundary = mGameObjectManager->CreateGameObject();
	GameObject* pTurretBoundary = turretBoundary.Get();

	exColor turretBoundaryColor;
	turretBoundaryColor.SetColor(128, 128, 128, 255);

	// Adding the required Components
	pTurretBoundary->AddComponent(new COGTransform(pTurretBoundary, { 150, 0 }));
	COGBoxShape* pTurretBoxShapeComponent = new COGBoxShape(mEngine, pTurretBoundary, 2.0f, kViewportHeight, turretBoundaryColor);
	pTurretBoundary->AddComponent(pTurretBoxShapeComponent);
	COGPhysics* pTurretPhysicsComponent = new COGPhysics(mEngine, pTurretBoundary, true, 0);
	pTurretBoundary->AddComponent(pTurretPhysicsComponent);
	COGDamageOnCollisionWithTurret* pTurretCollisionEvent = new COGDamageOnCollisionWithTurret(pTurretBoundary, mTurret.Get(), ComponentType::EnemyController);
	pTurretBoundary->AddComponent(pTurretCollisionEvent);

	// Initializing Components
	pTurretBoxShapeComponent->Initialize();
	pTurretPhysicsComponent->Initialize();
	pTurretCollisionEvent->Initialize();
	return turretBoundary;
}

GameObjectHandle MyGame::CreateEnemySpawner()
{
	GameObjectHandle enemySpawner = mGameObjectManager->CreateGameObject();
	GameObject*	pEnemySpawner = enemySpawner.Get();

	// Putting in the necessary components
	pEnemySpawner->AddComponent(new COGEnemySpawner(mEngine, pEnemySpawner, 5, 40, 150));

	return enemySpawner;
}
#include "COGEnemySpawner.h"
#include "COGDestroyOnCollisionWith.h"
#include "COGPhysics.h"
#include <time.h>

COGEnemySpawner::COGEnemySpawner(exEngineInterface* pEngine, GameObject* pGameObject, int iTotalEnemiesToSpawn, float fDelayBetweenSpawns, float fInitialEnemyVelocity)
	:Component(pGameObject)
{
	// Initializing Variables
	mEngine = pEngine;
	mTotalEnemiesToSpawn = iTotalEnemiesToSpawn;
	mDelayBetweenSpawns = fDelayBetweenSpawns;
	mEnemyVelocity = fInitialEnemyVelocity;
	mSpawnedWave = false;
	mTimer = 0;
	mGameObjectManager = GameObjectManager::GetInstance();
}

COGEnemySpawner::~COGEnemySpawner()
{
	Destroy();
}

void COGEnemySpawner::Destroy()
{
	// Removing from the component's list
	mGameObject->RemoveComponent(this);
}

ComponentType COGEnemySpawner::GetType() const
{
	return ComponentType::EnemySpawner;
}

void COGEnemySpawner::Update(float fDeltaTime)
{
	// Spawning Enemies when it is time for the next wave or when all the enemies are destroyed
	if (!mSpawnedWave || COGEnemyController::mEnemiesSpawned.size() <= 0)
	{
		mSpawnedWave = true;
		srand(time(NULL));

		// Spawning a Wave
		for (int i = 0; i < mTotalEnemiesToSpawn; i++)
		{
			exVector2 spawnPosition = { (kViewportWidth - 10) , (rand() % kViewportHeight) };
			CreateEnemy(spawnPosition);
		}

		// Incrementing number of enemies and their speed to increase difficultie after each wave
		++mTotalEnemiesToSpawn;
		mEnemyVelocity += 10;
	}

	else
	{
		mTimer += fDeltaTime;
		if (mTimer >= mDelayBetweenSpawns)
		{
			mTimer = 0;
			mSpawnedWave = false;
		}
	}
}

void COGEnemySpawner::CreateEnemy(exVector2& spawnLocation)
{
	GameObjectHandle enemyHandle = mGameObjectManager->CreateGameObject();
	GameObject* pEnemy = enemyHandle.Get();

	exColor enemyColor;
	enemyColor.SetColor(0, 255, 0);

	// Putting in all the required components
	pEnemy->AddComponent(new COGTransform(pEnemy, spawnLocation));
	COGCircleShape* pEnemyShapeComponent = new COGCircleShape(mEngine, pEnemy, 10.0f, enemyColor);
	pEnemy->AddComponent(pEnemyShapeComponent);
	COGPhysics* pEnemyPhysicsComponent = new COGPhysics(mEngine, pEnemy, true, (rand() % (int)mEnemyVelocity) + 20);
	pEnemy->AddComponent(pEnemyPhysicsComponent);
	pEnemy->AddComponent(new COGEnemyController(pEnemy));
	COGDestroyOnCollisionWith* pEnemyCollisionEvent1 = new COGDestroyOnCollisionWith(pEnemy, ComponentType::Explosion);
	pEnemy->AddComponent(pEnemyCollisionEvent1);
	COGDestroyOnCollisionWith* pEnemyCollisionEvent2 = new COGDestroyOnCollisionWith(pEnemy, ComponentType::Bullet);
	pEnemy->AddComponent(pEnemyCollisionEvent2);
	COGDestroyOnCollisionWith* pEnemyCollisionEvent3 = new COGDestroyOnCollisionWith(pEnemy, ComponentType::BoxShape);
	pEnemy->AddComponent(pEnemyCollisionEvent3);

	// Changing the direction
	exVector2& direction = pEnemyPhysicsComponent->GetFacingDirection();
	// Enemies always move to the left
	direction = { -1 , 0 };

	// Initializing the components
	pEnemyShapeComponent->Initialize();
	pEnemyPhysicsComponent->Initialize();
	pEnemyCollisionEvent1->Initialize();
	pEnemyCollisionEvent2->Initialize();
	pEnemyCollisionEvent3->Initialize();
}
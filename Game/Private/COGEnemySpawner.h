#pragma once
#include "Component.h"
#include "COGEnemyController.h"
#include "GameObjectManager.h"

class COGEnemySpawner : public Component
{
public:
	COGEnemySpawner(exEngineInterface* pEngine, GameObject* pGameObject, int iTotalEnemiesToSpawn, float fDelayBetweenSpawns, float fInitialEnemyVelocity);
	~COGEnemySpawner();

	// Overridden Functions
	virtual void Destroy() override;
	virtual ComponentType GetType() const override;
	virtual void Update(float fDeltaTime);

private:
	void CreateEnemy(exVector2& spawnLocation);

private:
	float mTimer;
	bool mSpawnedWave;
	int mTotalEnemiesToSpawn;
	float mEnemyVelocity;
	float mDelayBetweenSpawns;

	exEngineInterface* mEngine;
	GameObjectManager* mGameObjectManager;
};
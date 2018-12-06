#include "COGEnemyController.h"
#include <algorithm>

std::vector<COGEnemyController*> COGEnemyController::mEnemiesSpawned;

COGEnemyController::COGEnemyController(GameObject* pGameObject)
	:Component(pGameObject)
{
	mEnemiesSpawned.push_back(this);
}

COGEnemyController::~COGEnemyController()
{
	Destroy();
}

void COGEnemyController::Destroy()
{
	Console::LogString("Deleted an Enemy Controller!\n");

	// Removing the component from the static vector
	mEnemiesSpawned.erase(std::remove(mEnemiesSpawned.begin(), mEnemiesSpawned.end(), this), mEnemiesSpawned.end());

	// Remove Component from the gameObject's component list
	mGameObject->RemoveComponent(this);
}

ComponentType COGEnemyController::GetType() const
{
	return ComponentType::EnemyController;
}
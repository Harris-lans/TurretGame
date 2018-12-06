#include "GameObjectInventory.h"

// Initializing the singleton with a nullptr
GameObjectInventory* Singleton<GameObjectInventory>::existingInstance = nullptr;

void GameObjectInventory::Register(GameObject* pGameObject)
{
	mMap.InsertNoCheck(pGameObject);
}

void GameObjectInventory::Unregister(GameObject* pGameObject)
{
	mMap.Delete(pGameObject);
}

void GameObjectInventory::ClearGameObjectInventory()
{
	mMap.ClearData();
}

bool GameObjectInventory::Exists(Hash hash) const
{
	return (mMap.Find(hash) != nullptr);
}

GameObject* GameObjectInventory::LookUp(Hash hash)
{
	return mMap.Find(hash);
}

const GameObject* GameObjectInventory::LookUp(Hash hash) const
{
	return mMap.Find(hash);
}

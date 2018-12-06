#include "GameObjectHandle.h"

GameObjectHandle::GameObjectHandle()
{
	mHash = NULL;
	mGameObjectInventory = GameObjectInventory::GetInstance();
}

bool GameObjectHandle::IsValid() const
{
	return (mGameObjectInventory->Exists(mHash));
}

GameObject* GameObjectHandle::Get() const
{
	return mGameObjectInventory->LookUp(mHash);
}

void GameObjectHandle::SetHash(Hash hash)
{
	mHash = hash;
}
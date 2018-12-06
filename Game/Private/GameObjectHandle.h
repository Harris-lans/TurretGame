#pragma once
#include "GameObjectInventory.h"

class GameObjectHandle
{
public:

	Hash mHash;
	GameObjectInventory* mGameObjectInventory;

public:

	GameObjectHandle();

	bool IsValid() const;
	GameObject* Get() const;
	void SetHash(Hash hash);
};
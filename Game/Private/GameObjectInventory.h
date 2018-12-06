#pragma once
#include "Singleton.h"
#include "HashMap.h"
#include "GameObject.h"

class GameObjectInventory : public Singleton<GameObjectInventory>
{
public:

	void Register(GameObject* pGameObject);
	
	void Unregister(GameObject* pGameObject);

	void ClearGameObjectInventory();

	bool Exists(Hash hash) const;

	GameObject* LookUp(Hash hash);
	
	const GameObject* LookUp(Hash hash) const;

private:
	HashMap<GameObject*, 256> mMap;
};


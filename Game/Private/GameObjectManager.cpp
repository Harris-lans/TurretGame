#include "GameObjectManager.h"
#include "COGPhysics.h"
#include "COGFriendlyMissile.h"
#include "COGDestroyWhenOutOfBounds.h"
#include "COGExplode.h"
#include <functional>
#include <string>

// Using an alias for the hash functions for strings
std::hash<std::string> string_hash;

// Initializing the singleton
GameObjectManager* Singleton<GameObjectManager>::existingInstance = nullptr;

GameObjectManager::GameObjectManager()
{
	// Nothing to do here for now
}

GameObjectManager::~GameObjectManager()
{
	// Nothing to do here for now
	mGameObjectInventory->DeleteInstance();
}


void GameObjectManager::Initialize(exEngineInterface* pEngine)
{
	mEngine = pEngine;
	mGameObjectInventory = GameObjectInventory::GetInstance();
}

GameObjectHandle GameObjectManager::CreateGameObject()
{
	GameObjectHandle gameObjectHandle;
	GameObject * gameObject = new GameObject(string_hash(std::to_string(GameObject::gameObjectNumber) + "empty-game-object-"));
	mGameObjectInventory->Register(gameObject);
	gameObjectHandle.SetHash(gameObject->mHash);
	return gameObjectHandle;
	
}

void GameObjectManager::DeleteGameObject(GameObject* pGameObject)
{
	bool alreadyMarkedForDelete = false;
	// Passing the gameobject pointer
	for (auto object : mStaleObjects)
	{
		// Checking if the gameObject is already marked for delete
		if (object == pGameObject)
		{
			alreadyMarkedForDelete = true;
			return;
		}
	}

	if (!alreadyMarkedForDelete)
	{
		mStaleObjects.push_back(pGameObject);
	}
}


void GameObjectManager::ClearAllGameObjects()
{
	mGameObjectInventory->ClearGameObjectInventory();
}


// Updating and rendering the gameobject
void GameObjectManager::Update(float fDeltaTime)
{
	// Updating the physics component and the input reader components

	for (COGPhysics* pPhysicsComponent : COGPhysics::mPhysicsComponents)
	{
		pPhysicsComponent->Update(fDeltaTime);
	}


	for (COGExplode* explosion : COGExplode::mExplosionComponents)
	{
		explosion->Update();
	}

	for (COGFriendlyMissile* friendlyMissile : COGFriendlyMissile::mFriendlyMissiles)
	{
		friendlyMissile->Update();
	}

	//Destroying objects when they are out of bounds
	for (COGDestroyWhenOutOfBounds* pComponent : COGDestroyWhenOutOfBounds::mDestroyWhenOutOfBoundsComponents)
	{
		pComponent->Update();
	}

	// Cleaning up all the deleted gameObjects
	for (GameObject* pGameObject : mStaleObjects)
	{
		mGameObjectInventory->Unregister(pGameObject);
	}

	mStaleObjects.clear();
}

void GameObjectManager::Render()
{
	// Rendering all the shape components
	for (COGShape* pShapeComponent : COGShape::mShapeComponents)
	{
		pShapeComponent->Render();
	}
}
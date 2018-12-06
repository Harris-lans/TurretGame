#include "COGDestroyOnCollisionWith.h"

COGDestroyOnCollisionWith::COGDestroyOnCollisionWith(GameObject* pGameObject, ComponentType pComponentToSearchFor)
	:Component(pGameObject)
{
	mComponentToSearchFor = pComponentToSearchFor;
	mGameObjectManager = GameObjectManager::GetInstance();
}

COGDestroyOnCollisionWith::~COGDestroyOnCollisionWith()
{
	Destroy();
}

ComponentType COGDestroyOnCollisionWith::GetType() const
{
	return ComponentType::DestroyOnCollision;
}


void COGDestroyOnCollisionWith::Initialize()
{
	mPhysicsComponent = mGameObject->FindComponent<COGPhysics>(ComponentType::Physics);
	if (mPhysicsComponent != nullptr)
	{
		// Adding to the physics event vector
		mPhysicsComponent->AddPhysicsEvent(this);
	}
}

void COGDestroyOnCollisionWith::Destroy()
{
	// Removing from the physics event vector
	mPhysicsComponent->RemovePhysicsEvent(this);

	// Removing from the component's vector
	mGameObject->RemoveComponent(this);
}

void COGDestroyOnCollisionWith::OnCollision(COGPhysics* pPhysicsComponent, COGPhysics* pOtherPhysicsComponent, exVector2 pNormalVector)
{
	if (pOtherPhysicsComponent != nullptr)
	{
		Component* component = pOtherPhysicsComponent->mGameObject->FindComponent<Component>(mComponentToSearchFor);
		if (component != nullptr)
		{
			mGameObjectManager->DeleteGameObject(this->mGameObject);
		}
	}
}
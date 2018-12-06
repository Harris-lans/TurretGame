#include "COGDestroyWhenOutOfBounds.h"
#include <algorithm>

std::vector<COGDestroyWhenOutOfBounds*> COGDestroyWhenOutOfBounds::mDestroyWhenOutOfBoundsComponents;

COGDestroyWhenOutOfBounds::COGDestroyWhenOutOfBounds(GameObject* pGameObject)
	:Component(pGameObject)
{
	mDestroyWhenOutOfBoundsComponents.push_back(this);
	mGameObjectManager = GameObjectManager::GetInstance();
}

COGDestroyWhenOutOfBounds::~COGDestroyWhenOutOfBounds()
{
	Destroy();
}

void COGDestroyWhenOutOfBounds::Initialize()
{
	mTransformComponent = mGameObject->FindComponent<COGTransform>(ComponentType::Transform);
}

void COGDestroyWhenOutOfBounds::Destroy()
{
	// Removing the component from the static vector
	mDestroyWhenOutOfBoundsComponents.erase(std::remove(mDestroyWhenOutOfBoundsComponents.begin(), mDestroyWhenOutOfBoundsComponents.end(), this), mDestroyWhenOutOfBoundsComponents.end());

	// Remove Component from the gameObject's component list
	mGameObject->RemoveComponent(this);
}

ComponentType COGDestroyWhenOutOfBounds::GetType() const
{
	return ComponentType::DestroyWhenOutOfBounds;
}

void COGDestroyWhenOutOfBounds::Update()
{
	exVector2& objectPosition = mTransformComponent->GetPosition();
	
	// Checking if the object is out of bounds and deleting the object if it is out of bounds
	if (objectPosition.x < 0 || objectPosition.x > kViewportWidth || objectPosition.y < 0 || objectPosition.y > kViewportHeight)
	{
		mGameObjectManager->DeleteGameObject(mGameObject);
	}
}
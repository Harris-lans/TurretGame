#include "COGExplode.h"
#include <algorithm>

std::vector<COGExplode*> COGExplode::mExplosionComponents;

COGExplode::COGExplode(GameObject* pGameObject, float fRateOfExplosion, float fMaximumRadius)
	:Component(pGameObject)
{
	mGameObjectManager = GameObjectManager::GetInstance();
	mRateOfExplosion = fRateOfExplosion;
	mExplosionComponents.push_back(this);
	mMaximumRadius = fMaximumRadius;
}

COGExplode::~COGExplode()
{
	Destroy();
}

void COGExplode::Initialize()
{
	mShapeComponent = mGameObject->FindComponent<COGCircleShape>(ComponentType::CircleShape);
}

void COGExplode::Destroy()
{
	Console::LogString("Deleted Explosion Component!");

	// Removing the component from the static vector
	mExplosionComponents.erase(std::remove(mExplosionComponents.begin(), mExplosionComponents.end(), this), mExplosionComponents.end());

	// Remove Component from the gameObject's component list
	mGameObject->RemoveComponent(this);
}

ComponentType COGExplode::GetType() const
{
	return ComponentType::Explosion;
}

void COGExplode::Update()
{
	// Checking if the Explosion Component has been initialized
	if (mShapeComponent != nullptr)
	{
		float& explosionRadius = mShapeComponent->GetRadius();

		if (explosionRadius >= mMaximumRadius)
		{
			mGameObjectManager->DeleteGameObject(this->mGameObject);
		}

		// Increasing the size of the explosion
		explosionRadius += mRateOfExplosion;

	}

}
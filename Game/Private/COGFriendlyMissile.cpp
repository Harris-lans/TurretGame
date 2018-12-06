#include "COGFriendlyMissile.h"
#include <algorithm>

std::vector<COGFriendlyMissile*> COGFriendlyMissile::mFriendlyMissiles;

COGFriendlyMissile::COGFriendlyMissile(exEngineInterface* pEngine, GameObject* pGameObject, exVector2& targetPosition)
	:Component(pGameObject)
{
	mEngine = pEngine;
	mTargetPosition = targetPosition;
	mHasExploded = false;
	mFriendlyMissiles.push_back(this);
	mGameObjectManager = GameObjectManager::GetInstance();
}

COGFriendlyMissile::~COGFriendlyMissile()
{
	Destroy();
}

ComponentType COGFriendlyMissile::GetType() const
{
	return ComponentType::FriendlyMissile;
}

void COGFriendlyMissile::Initialize()
{
	mTransformComponent = mGameObject->FindComponent<COGTransform>(ComponentType::Transform);
	mPhysicsComponent = mGameObject->FindComponent<COGPhysics>(ComponentType::Physics);
	mMissileTrail = mGameObject->FindComponent<COGLineShape>(ComponentType::LineShape);
}

void COGFriendlyMissile::Destroy()
{
	// Removing the component from the static vector
	mFriendlyMissiles.erase(std::remove(mFriendlyMissiles.begin(), mFriendlyMissiles.end(), this), mFriendlyMissiles.end());

	// Removing from the component's list
	mGameObject->RemoveComponent(this);
	
}

void COGFriendlyMissile::Update()
{
	exVector2& position = mTransformComponent->GetPosition();
	exVector2& trailPosition = mMissileTrail->GetEndPoint();
	
	// Updating the endpoint of the missile trail
	trailPosition = position;

	// Check if the missile has reached the target
	if (!mHasExploded && (position.x > mTargetPosition.x))
	{
		float& velocity = mPhysicsComponent->GetVelocity();
		velocity = 0;

		mHasExploded = true;
		mExplosionHandle = CreateExplosion(position);
	}

	else if (mHasExploded)
	{
		// Waiting for the explosion to be destroyed
		if (!mExplosionHandle.IsValid())
		{
			// Destroy self
			mGameObjectManager->DeleteGameObject(mGameObject);
		}
	}
}

GameObjectHandle COGFriendlyMissile::CreateExplosion(exVector2& explosionLocation)
{
	// Create Pulses
	GameObjectHandle explosionHandle = mGameObjectManager->CreateGameObject();
	GameObject* pExplosion = explosionHandle.Get();

	exColor pulseColor;
	pulseColor.SetColor(255, 255, 255, 255);

	// Adding the required components for the pulse
	pExplosion->AddComponent(new COGTransform(pExplosion, explosionLocation));
	COGCircleShape* pExplosionShapeComponent = new COGCircleShape(mEngine, pExplosion, 1.0f, pulseColor);
	pExplosion->AddComponent(pExplosionShapeComponent);
	COGPhysics* pExplosionPhysicsComponent = new COGPhysics(mEngine, pExplosion, true, 0);
	pExplosion->AddComponent(pExplosionPhysicsComponent);
	COGExplode* pExplosionComponent = new COGExplode(pExplosion, 2, 100);
	pExplosion->AddComponent(pExplosionComponent);

	// Initializing the Components
	pExplosionShapeComponent->Initialize();
	pExplosionPhysicsComponent->Initialize();
	pExplosionComponent->Initialize();

	return explosionHandle;
}
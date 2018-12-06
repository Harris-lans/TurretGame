#include "COGDamageOnCollisionWithTurret.h"
#include "COGTurret.h"

COGDamageOnCollisionWithTurret::COGDamageOnCollisionWithTurret(GameObject* pGameObject, GameObject* pTurretToDamage, ComponentType pComponentToCheckFor)
	:Component(pGameObject)
{
	// Nothing to do here for now
	mTurretToDamage = pTurretToDamage->FindComponent<COGTurret>(ComponentType::Turret);
	mComponentToSearchFor = pComponentToCheckFor;
}

COGDamageOnCollisionWithTurret::~COGDamageOnCollisionWithTurret()
{
	Destroy();
}

ComponentType COGDamageOnCollisionWithTurret::GetType() const
{
	return ComponentType::DamageOnCollisionWithTurret;
}


void COGDamageOnCollisionWithTurret::Initialize()
{
	mPhysicsComponent = mGameObject->FindComponent<COGPhysics>(ComponentType::Physics);
	if (mPhysicsComponent != nullptr)
	{
		// Adding to the physics event vector
		mPhysicsComponent->AddPhysicsEvent(this);
	}
}

void COGDamageOnCollisionWithTurret::Destroy()
{
	// Removing from the physics event vector
	mPhysicsComponent->RemovePhysicsEvent(this);

	// Removing from the component's vector
	mGameObject->RemoveComponent(this);
}

void COGDamageOnCollisionWithTurret::OnCollision(COGPhysics* pPhysicsComponent, COGPhysics* pOtherPhysicsComponent, exVector2 pNormalVector)
{
	if (pOtherPhysicsComponent != nullptr)
	{
		Component* componentToSearchFor = pOtherPhysicsComponent->mGameObject->FindComponent<Component>(mComponentToSearchFor);
		if (componentToSearchFor != nullptr)
		{
			mTurretToDamage->DamageTurret(10);
		}
	}
}
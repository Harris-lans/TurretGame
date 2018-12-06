#pragma once
#include "COGPhysics.h"
#include "COGTurret.h"
#include "GameObjectManager.h"

class COGDamageOnCollisionWithTurret : public Component, public IPhysicsCollisionEvent
{
public:
	COGDamageOnCollisionWithTurret(GameObject* pGameObject, GameObject* pTurretToDamage, ComponentType pComponentToCheckFor);
	~COGDamageOnCollisionWithTurret();

	virtual ComponentType GetType() const override;
	virtual void Initialize() override;
	virtual void Destroy() override;
	virtual void OnCollision(COGPhysics* pPhysicsComponent, COGPhysics* pOtherPhysicsComponent, exVector2 pNormalVector) override;

private:
	ComponentType			mComponentToSearchFor;
	GameObjectManager*		mGameObjectManager;
	COGPhysics*				mPhysicsComponent;
	COGTurret*				mTurretToDamage;
};

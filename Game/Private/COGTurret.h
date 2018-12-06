#pragma once
#include "Component.h"
#include "COGTransform.h"
#include "COGBoxShape.h"
#include "GameObjectManager.h"
#include "COGFiniteStateMachine.h"
#include "COGReticle.h"
#include <string>

class COGTurret : public Component
{
private:
	const float BULLET_VELOCITY = 200.0f;
	const float MISSILE_VELOCITY = 100.0f;

public:
	COGTurret(GameObject* pGameObject, exEngineInterface* pEngine, int iTotalMissiles, int iTotalPulses, int iTurretHealth);
	~COGTurret();

	// Overridden Functions
	virtual void Initialize() override;
	virtual void Destroy() override;
	virtual ComponentType GetType() const override;

	// Main Update Function -> Used for moving the reticle
	virtual void Update(float fDeltaTime);

	// Shooting Functions
	virtual void FireBulletStorm();
	virtual void FirePulseDisruptions();
	virtual void FireTargettedMissiles();

	// Damage Fucntions
	void DamageTurret(int iDamage);

	// Getters and Setters
	void SetStateTag(std::string& sTag);
	void SetFireDelay(float fFireDelay);
	std::string& GetStateTag();
	int GetHealth() const;
	int GetPulsesLeft() const;
	int GetMissilesLeft() const;

private:
	// Helper functions
	GameObjectHandle CreateBullet();
	GameObjectHandle CreatePulse();
	GameObjectHandle CreateMissile();
	GameObjectHandle CreateReticle();

private:

	int mHealth;

	// Bullet Storm has infinite bullets
	int mMissilesLeft;
	int mPulsesLeft;

	std::string mSelectedWeaponTag;

	float mTurretTimer;
	float mFireDelay;
	bool mCanFire;
	bool mReticleInRange;
	exVector2 mTurretNozzle;
	exVector2 mReticlePosition;
	float mHorizontalTurretRangeLimit;

	// Reticle Transform
	COGTransform* mReticleTransform;

	// Related Component
	COGFiniteStateMachine* mStateMachineComponent;
	COGBoxShape* mBoxShapeComponent;
	COGTransform* mTransformComponent;
	COGReticle* mReticleComponent;

	// Helper Objects
	GameObjectManager* mGameObjectManager;
	exEngineInterface* mEngine;
};
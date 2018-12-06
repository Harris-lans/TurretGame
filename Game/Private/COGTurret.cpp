#include "COGTurret.h"
#include "COGPhysics.h"
#include "COGLineCircleShape.h"
#include "COGDestroyOnCollisionWith.h"
#include "COGBullet.h"
#include "COGFriendlyMissile.h"
#include "COGDestroyWhenOutOfBounds.h"

COGTurret::COGTurret(GameObject* pGameObject, exEngineInterface* pEngine, int iTotalMissiles, int iTotalPulses, int iTurretHealth)
	:Component(pGameObject)
{
	mMissilesLeft = iTotalMissiles;
	mPulsesLeft = iTotalPulses;
	mSelectedWeaponTag = "No Weapons Selected";
	mHealth = iTurretHealth;

	// Initializing Timer
	mTurretTimer = 0;
	mFireDelay = 0;
	bool mCanFire = true;

	// Initializing Helper Objects
	mGameObjectManager = GameObjectManager::GetInstance();
	mEngine = pEngine;

	// Creating Reticle for the Turret and storing it's reticle component
	GameObjectHandle reticleHandle = CreateReticle();
	mReticleTransform = reticleHandle.Get()->FindComponent<COGTransform>(ComponentType::Transform);
}

COGTurret::~COGTurret()
{
	Destroy();

	// Destroying the reticle when the turret is destroyed
	mGameObjectManager->DeleteGameObject(mReticleComponent->mGameObject);
}

void COGTurret::Initialize()
{
	mStateMachineComponent = mGameObject->FindComponent<COGFiniteStateMachine>(ComponentType::FiniteStateMachine);
	mBoxShapeComponent = mGameObject->FindComponent<COGBoxShape>(ComponentType::BoxShape);
	mTransformComponent = mGameObject->FindComponent<COGTransform>(ComponentType::Transform);

	// Setting up Turret Nozzle Position
	mTurretNozzle = { (mTransformComponent->GetPosition().x + mBoxShapeComponent->GetWidth() + 5.0f) , (mTransformComponent->GetPosition().y + (1/2 * mBoxShapeComponent->GetHeight())) };
}

void COGTurret::Destroy()
{
	// Removing from the component's list
	mGameObject->RemoveComponent(this);
}

ComponentType COGTurret::GetType() const
{
	return (ComponentType::Turret);
}

void COGTurret::Update(float fDeltaTime)
{
	// Getting the reticle position of the reticle gameObject
	mReticleComponent->Update();
	mReticlePosition = mReticleTransform->GetPosition();

	// Checking if the reticle is in front of the turret nozzle
	mReticleInRange = false;
	if (mReticlePosition.x > mTurretNozzle.x)
	{
		mReticleInRange = true;
	}


	// Updating the timer
	mTurretTimer += fDeltaTime;

	// Updating the State Machine
	mStateMachineComponent->Update(fDeltaTime);
}

void COGTurret::FireBulletStorm()
{
	if (mTurretTimer >= mFireDelay && mReticleInRange)
	{
		GameObjectHandle bulletHandle = CreateBullet();
		COGPhysics* pBulletPhysicsComponent = bulletHandle.Get()->FindComponent<COGPhysics>(ComponentType::Physics);

		// Calculating and Setting the direction of the bullet
		exVector2& directionOfBullet = pBulletPhysicsComponent->GetFacingDirection();
		directionOfBullet = { ( mReticlePosition.x - mTurretNozzle.x ), ( mReticlePosition.y - mTurretNozzle.y ) };
		directionOfBullet.Normalize();
		Console::LogString("Direction of the Bullet X - : " + std::to_string(directionOfBullet.x) + "   Y - " + std::to_string(directionOfBullet.y) + "\n ");
		// Resetting turret timer
		mTurretTimer = 0;
	}
}

void COGTurret::FirePulseDisruptions()
{
	if (mPulsesLeft > 0 && mReticleInRange && mTurretTimer >= mFireDelay)
	{
		--mPulsesLeft;
		CreatePulse();

		// Resetting turret timer
		mTurretTimer = 0;
	}
}

void COGTurret::FireTargettedMissiles()
{
	if (mMissilesLeft > 0 && mReticleInRange && mTurretTimer >= mFireDelay)
	{
		--mMissilesLeft;
		GameObjectHandle missileHandle = CreateMissile();
		COGPhysics* pMissilePhysicsComponent = missileHandle.Get()->FindComponent<COGPhysics>(ComponentType::Physics);

		// Calculating the direction and setting the direction of the missile
		exVector2& directionOfMissile = pMissilePhysicsComponent->GetFacingDirection();
		directionOfMissile = { (mReticlePosition.x - mTurretNozzle.x), (mReticlePosition.y - mTurretNozzle.y) };
		directionOfMissile.Normalize();

		// Resetting turret timer
		mTurretTimer = 0;
	}
}


// Getters and Setters
void COGTurret::SetStateTag(std::string& sTag)
{
	mSelectedWeaponTag = sTag;
}

void COGTurret::SetFireDelay(float fFireDelay)
{
	// Setting Fire Delay 
	mFireDelay = fFireDelay;
}

int COGTurret::GetHealth() const
{
	return mHealth;
}

std::string& COGTurret::GetStateTag()
{
	return mSelectedWeaponTag;
}

int COGTurret::GetPulsesLeft() const
{
	return mPulsesLeft;
}

int COGTurret::GetMissilesLeft() const
{
	return mMissilesLeft;
}


// Turret Damage Function
void COGTurret::DamageTurret(int iDamage)
{
	// Receiving Damage
	mHealth -= iDamage;

	// Checking if the turret has no health and destroying it if there is no health
	if (mHealth <= 0)
	{
		mGameObjectManager->DeleteGameObject(mGameObject);
	}
}

// Helper Functions
GameObjectHandle COGTurret::CreateBullet()
{
	// Create Bullets 
	GameObjectHandle bulletHandle = mGameObjectManager->CreateGameObject();
	GameObject* pBullet = bulletHandle.Get();

	exColor bulletColor;
	bulletColor.SetColor(255, 0, 0);

	// Adding the required components for the bullet
	pBullet->AddComponent(new COGTransform(pBullet, mTurretNozzle));
	Console::LogString("Nozzle : " + std::to_string(mTurretNozzle.x));
	COGCircleShape* pBulletShapeComponent = new COGCircleShape(mEngine, pBullet, 5.0f, bulletColor);
	pBullet->AddComponent(pBulletShapeComponent);
	COGPhysics* pBulletPhysicsComponent = new COGPhysics(mEngine, pBullet, true, BULLET_VELOCITY);
	pBullet->AddComponent(pBulletPhysicsComponent);
	COGDestroyWhenOutOfBounds* pBulletDestroyWhenOutOfBoundsComponent = new COGDestroyWhenOutOfBounds(pBullet);
	pBullet->AddComponent(pBulletDestroyWhenOutOfBoundsComponent);
	pBullet->AddComponent(new COGBullet(pBullet));

	// Adding Required Events
	COGDestroyOnCollisionWith* pBulletOnCollisionEvent = new COGDestroyOnCollisionWith(pBullet, ComponentType::EnemyController);
	pBullet->AddComponent(pBulletOnCollisionEvent);

	// Initializing the Components
	pBulletShapeComponent->Initialize();
	pBulletPhysicsComponent->Initialize();
	pBulletOnCollisionEvent->Initialize();
	pBulletDestroyWhenOutOfBoundsComponent->Initialize();

	return bulletHandle;
}

GameObjectHandle COGTurret::CreateMissile()
{
	// Create Missiles
	GameObjectHandle missileHandle = mGameObjectManager->CreateGameObject();
	GameObject* pMissile = missileHandle.Get();

	exColor missileColor;
	missileColor.SetColor(0, 0, 255, 255);
	
	// Addding the required components for the missile
	pMissile->AddComponent(new COGTransform(pMissile, mTurretNozzle));
	COGCircleShape* pMissileShapeComponent = new COGCircleShape(mEngine, pMissile, 5.0f, missileColor);
	pMissile->AddComponent(pMissileShapeComponent);
	COGPhysics* pMissilePhysicsComponent = new COGPhysics(mEngine, pMissile, false, MISSILE_VELOCITY);
	pMissile->AddComponent(pMissilePhysicsComponent);
	COGFriendlyMissile* pMissileComponent = new COGFriendlyMissile(mEngine, pMissile, mReticlePosition);
	pMissile->AddComponent(pMissileComponent);
	COGDestroyWhenOutOfBounds* pMissileDestroyWhenOutOfBoundsComponent = new COGDestroyWhenOutOfBounds(pMissile);
	pMissile->AddComponent(pMissileDestroyWhenOutOfBoundsComponent);
	COGLineShape* pMissileTrailComponent = new COGLineShape(mEngine, pMissile, mTurretNozzle, missileColor);
	pMissile->AddComponent(pMissileTrailComponent);

	// Initializing Components
	pMissileShapeComponent->Initialize();
	pMissilePhysicsComponent->Initialize();
	pMissileComponent->Initialize();
	pMissileDestroyWhenOutOfBoundsComponent->Initialize();
	pMissileTrailComponent->Initialize();

	return missileHandle;
}

GameObjectHandle COGTurret::CreatePulse()
{
	// Create Pulses
	GameObjectHandle pulseHandle = mGameObjectManager->CreateGameObject();
	GameObject* pPulse = pulseHandle.Get();

	exColor pulseColor;
	pulseColor.SetColor(255, 255, 255, 255);

	// Adding the required components for the pulse
	pPulse->AddComponent(new COGTransform(pPulse, mTurretNozzle));
	COGLineCircleShape* pPulseShapeComponent = new COGLineCircleShape(mEngine, pPulse, 5.0f, pulseColor);
	pPulse->AddComponent(pPulseShapeComponent);
	COGPhysics* pPulsePhysicsComponent = new COGPhysics(mEngine, pPulse, true, 0);
	pPulse->AddComponent(pPulsePhysicsComponent);
	COGExplode* pPulseExplosionComponent = new COGExplode(pPulse, 10, 800);
	pPulse->AddComponent(pPulseExplosionComponent);

	// Initializing the Components
	pPulseShapeComponent->Initialize();
	pPulsePhysicsComponent->Initialize();
	pPulseExplosionComponent->Initialize();

	return pulseHandle;
}

GameObjectHandle COGTurret::CreateReticle()
{
	// Creating Reticle
	GameObjectHandle reticleHandle = mGameObjectManager->CreateGameObject();
	GameObject* pReticle = reticleHandle.Get();

	exColor reticleColor;
	reticleColor.SetColor(255, 255, 255, 255);

	// Adding the required components for the reticle
	pReticle->AddComponent(new COGTransform(pReticle, mTurretNozzle));
	COGLineCircleShape* pReticleShapeComponent = new COGLineCircleShape(mEngine, pReticle, 5.0f, reticleColor);
	pReticle->AddComponent(pReticleShapeComponent);
	mReticleComponent = new COGReticle(pReticle);
	pReticle->AddComponent(mReticleComponent);

	// Initializing Reticle Component
	pReticleShapeComponent->Initialize();
	mReticleComponent->Initialize();

	return reticleHandle;
}

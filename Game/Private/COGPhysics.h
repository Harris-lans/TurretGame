#pragma once
#include "COGTransform.h"
#include "COGBoxShape.h"
#include "COGCircleShape.h"

enum class PhysicsEvents : int
{
	Bounce = 0
};

class IPhysicsCollisionEvent;

class COGPhysics : public Component
{
public:

	COGPhysics(exEngineInterface* pEngine, GameObject* pGameObject, bool bGenerateCollisionEvents, float fVelocity);
	~COGPhysics();

	virtual ComponentType GetType() const;
	virtual void Initialize() override;
	virtual void Destroy() override;
	virtual void Update(float fDeltaT);

	exVector2 IsColliding(COGPhysics* pOther);
	exVector2 CheckCollision_BoxAndCircle(COGPhysics* pCircle, COGPhysics* pBox);
	exVector2 CheckCollision_CircleAndCircle(COGPhysics* pCircle1, COGPhysics* pCircle2);
	
	void SetVelocity(float pVelocity);
	void SetFacingDirection(exVector2& pFacingDirection);
	exVector2& GetFacingDirection();
	float& GetVelocity();

	void AddPhysicsEvent(IPhysicsCollisionEvent* pPhysicsEvent);
	void RemovePhysicsEvent(IPhysicsCollisionEvent* pPhysicsEvent);
	void TriggerCollisionEvents(COGPhysics*, const exVector2);

public:
	static std::vector<COGPhysics*> mPhysicsComponents;

private:
	exEngineInterface * mEngine;
	exColor mDebugColor;

	COGTransform * mTransform;
	COGBoxShape* mBoxShape;
	COGCircleShape* mCircleShape;

	float mVelocity;
	exVector2 mFacingDirection;

	bool mGenerateCollisionEvents;
	std::vector<IPhysicsCollisionEvent*> mCollisionEventListeners;
};

// Collision Event Interface
class IPhysicsCollisionEvent
{
public:
	virtual void OnCollision(COGPhysics* pPhysicsComponent, COGPhysics* pOtherPhysicsComponent, exVector2 pNormalVector) = 0;
};
#pragma once
#include "COGPhysics.h"
#include "Mathf.h"
#include <algorithm>

std::vector<COGPhysics*> COGPhysics::mPhysicsComponents;

COGPhysics::COGPhysics(exEngineInterface* pEngine, GameObject* pGameObject, bool bGenerateCollisionEvents, float fVelocity)
	:Component(pGameObject)
{
	mEngine = pEngine;
	mDebugColor.SetColor(0, 255, 0, 255);

	mGenerateCollisionEvents = bGenerateCollisionEvents;
	mVelocity = fVelocity;

	// Storing the object in the static variable
	AddToComponentVector(mPhysicsComponents);
}

COGPhysics::~COGPhysics()
{
	Destroy();
}

ComponentType COGPhysics::GetType() const
{
	return ComponentType::Physics;
}

void COGPhysics::Initialize()
{
	// Storing reference to transform and shape of the game object
	mTransform = mGameObject->FindComponent<COGTransform>(ComponentType::Transform);
	mBoxShape = mGameObject->FindComponent<COGBoxShape>(ComponentType::BoxShape);
	mCircleShape = mGameObject->FindComponent<COGCircleShape>(ComponentType::CircleShape);
}

void COGPhysics::Destroy()
{
	// Removing the component from the static vector
	mPhysicsComponents.erase(std::remove(mPhysicsComponents.begin(), mPhysicsComponents.end(), this), mPhysicsComponents.end());

	// Removing from the component's list
	mGameObject->RemoveComponent(this);
	Console::LogString("Deleted Physics Component! \n");
}

void COGPhysics::AddPhysicsEvent(IPhysicsCollisionEvent* pPhysicsEvent)
{
	mCollisionEventListeners.push_back(pPhysicsEvent);
}

void COGPhysics::RemovePhysicsEvent(IPhysicsCollisionEvent* pEvent)
{
	// Removing the component from the vector
	if (mCollisionEventListeners.size() > 0)
	{
		mCollisionEventListeners.erase(std::remove(mCollisionEventListeners.begin(), mCollisionEventListeners.end(), pEvent), mCollisionEventListeners.end());
	}
}

exVector2 COGPhysics::IsColliding(COGPhysics* pOther)
{
	// Checking if the collsion check is between a circle and a box
	if (mCircleShape != nullptr && pOther->mBoxShape != nullptr)
	{
		return CheckCollision_BoxAndCircle(this, pOther);
	}
	else if (mBoxShape != nullptr && pOther->mCircleShape != nullptr)
	{
		return CheckCollision_BoxAndCircle(pOther, this);
	}
	else if (mCircleShape != nullptr && pOther->mCircleShape != nullptr)
	{
		return CheckCollision_CircleAndCircle(this, pOther);
	}

	return {NULL , NULL};
}

exVector2 COGPhysics::CheckCollision_BoxAndCircle(COGPhysics* pCircle, COGPhysics* pBox)
{
	exVector2 nearestPositionOnRectangle = { 0 , 0 };
	exVector2 point1Box;
	exVector2 point2Box;
	exVector2 centerCircle;
	float radiusOfCircle;

	// Getting the dimensions of the box
	point1Box = { (pBox->mTransform->GetPosition().x) , (pBox->mTransform->GetPosition().y) };
	point2Box = { (pBox->mTransform->GetPosition().x + pBox->mBoxShape->GetWidth()) , (pBox->mTransform->GetPosition().y + pBox->mBoxShape->GetHeight()) };
	
	// Getting the dimensions of the circle
	centerCircle = { (pCircle->mTransform->GetPosition().x) , (pCircle->mTransform->GetPosition().y) };
	radiusOfCircle = pCircle->mCircleShape->GetRadius();

	// Finding the nearest point on the rectangle's border to the circle
	nearestPositionOnRectangle.x = Mathf::Max(point1Box.x, (Mathf::Min(point2Box.x, centerCircle.x)));
	nearestPositionOnRectangle.y = Mathf::Max(point1Box.y, (Mathf::Min(point2Box.y, centerCircle.y)));

	// Calculating the distance between the nearest point and the center of the circle
	exVector2 distanceVector = { (centerCircle.x - nearestPositionOnRectangle.x) , (centerCircle.y - nearestPositionOnRectangle.y) };
	float distanceFloat = distanceVector.Magnitude();


	// Collision Check
	if (distanceFloat <= radiusOfCircle)
	{
		// Finding the normal of the surface of the box; 
		distanceVector.Normalize();

		// Returning the Normal
		return distanceVector;
	}

	return { NULL, NULL };
}

exVector2 COGPhysics::CheckCollision_CircleAndCircle(COGPhysics* pCircle1, COGPhysics* pCircle2)
{
	exVector2& circle1Center = pCircle1->mTransform->GetPosition();
	exVector2& circle2Center = pCircle2->mTransform->GetPosition();
	exVector2 distance = { (circle1Center.x - circle2Center.x), (circle1Center.y - circle2Center.y) };
	float distanceMagnitude = distance.Magnitude();

	if (distanceMagnitude <= (pCircle1->mCircleShape->GetRadius() + pCircle2->mCircleShape->GetRadius()))
	{
		// The two circles are colliding
		distance.Normalize();
		
		return distance;
	}

	return { NULL, NULL };
}

exVector2& COGPhysics::GetFacingDirection()
{
	return mFacingDirection;
}

float& COGPhysics::GetVelocity()
{
	return mVelocity;
}

void COGPhysics::SetFacingDirection(exVector2& pFacingDirection)
{
	mFacingDirection = pFacingDirection;
}

void COGPhysics::SetVelocity(float fVelocity)
{
	mVelocity = fVelocity;
}

void COGPhysics::Update(float fDeltaTime)
{
	// Adding Velocity to the object
	exVector2& myPosition = mTransform->GetPosition();
	myPosition.x += mFacingDirection.x * mVelocity * fDeltaTime;
	myPosition.y += mFacingDirection.y * mVelocity * fDeltaTime;

	// Check collisions
	if (mGenerateCollisionEvents)
	{
		for (COGPhysics* pPhysicsOther : COGPhysics::mPhysicsComponents)
		{
			// Do not collide with self
			if (pPhysicsOther == this)
			{
				continue;
			}

			const exVector2 pNormal = IsColliding(pPhysicsOther);

			// If the normal is null there is no collision
			if (pNormal.x == NULL && pNormal.y == NULL)
			{
				continue;
			}
			else
			{
				// Trigger all events that should happen on a collision
				for (IPhysicsCollisionEvent* pCollisionEventListener : mCollisionEventListeners)
				{
					pCollisionEventListener->OnCollision(this, pPhysicsOther, pNormal);
				}
				// Triggering events on both objects
				pPhysicsOther->TriggerCollisionEvents(this, pNormal);
			}
		}
	}
}

void COGPhysics::TriggerCollisionEvents(COGPhysics* pPhysicsOther, const exVector2 pNormal)
{
	for (IPhysicsCollisionEvent* pCollisionEventListener : mCollisionEventListeners)
	{
		pCollisionEventListener->OnCollision(this, pPhysicsOther, pNormal);
	}
}
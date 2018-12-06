#include "COGShape.h"
#include <algorithm>

std::vector<COGShape*> COGShape::mShapeComponents;

COGShape::COGShape(exEngineInterface* pEngine, GameObject* pGameObject, exColor& pColor)
	:Component(pGameObject)
{
	mEngine = pEngine;
	mColor = pColor;

	// Adding the shape component to the static vector
	AddToComponentVector(mShapeComponents);
}

COGShape::~COGShape()
{
	Destroy();
}

void COGShape::Destroy()
{
	// Removing the component from the static vector
	mShapeComponents.erase(std::remove(mShapeComponents.begin(), mShapeComponents.end(), this), mShapeComponents.end());

	// Removing from the component's list
	mGameObject->RemoveComponent(this);

	Console::LogString("Deleted Shape Component! \n");
}

void COGShape::Initialize()
{
	// Getting the transform of the gameobject
	mTransform = mGameObject->FindComponent<COGTransform>(ComponentType::Transform);
}

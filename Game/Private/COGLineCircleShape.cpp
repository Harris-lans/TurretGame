#include "COGLineCircleShape.h"

COGLineCircleShape::COGLineCircleShape(exEngineInterface* pEngine, GameObject* pGameObject, float fRadius, exColor& pColor)
	:COGCircleShape(pEngine, pGameObject, fRadius, pColor)
{
	// No extra initializations required
}

ComponentType COGLineCircleShape::GetType() const
{
	return ComponentType::CircleShape;
}

void COGLineCircleShape::Render()
{
	// Checking if the game object has a transform
	if (mTransform != nullptr)
	{
		exVector2& position = mTransform->GetPosition();

		// Drawing the line circle
		mEngine->DrawLineCircle(position, mRadius, mColor, 11);
	}
}
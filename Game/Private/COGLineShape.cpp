#include "COGLineShape.h"

COGLineShape::COGLineShape(exEngineInterface* pEngine, GameObject* pGameObject, exVector2 pStartingPoint, exColor& pColor)
	:COGShape(pEngine, pGameObject, pColor)
{
	mOrigin = pStartingPoint;
	mEndPoint = pStartingPoint;
}

ComponentType COGLineShape::GetType() const
{
	return ComponentType::LineShape;
}

exVector2& COGLineShape::GetEndPoint()
{
	return mEndPoint;
}

void COGLineShape::Render()
{
	// Drawing the line from the origin to the end
	mEngine->DrawLine(mOrigin, mEndPoint, mColor, 2);
}
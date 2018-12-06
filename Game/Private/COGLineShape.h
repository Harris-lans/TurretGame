#pragma once
#include "COGShape.h"

class COGLineShape : public COGShape
{
public:
	COGLineShape(exEngineInterface* pEngine, GameObject* pGameObject, exVector2 startingPoint, exColor& pColor);

	virtual void Render() override;
	virtual ComponentType GetType() const override;

	exVector2& GetEndPoint();

protected:
	exVector2 mEndPoint;
	exVector2 mOrigin;
};
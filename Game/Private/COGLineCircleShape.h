#pragma once
#include "COGCircleShape.h"

class COGLineCircleShape : public COGCircleShape
{
public:
	COGLineCircleShape(exEngineInterface* pEngine, GameObject* pGameObject, float fRadius, exColor& pColor);

	// Overriding the Rendering method of the Circle Shape Component
	virtual ComponentType GetType() const override;
	virtual void Render() override;
};
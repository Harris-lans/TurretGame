#pragma once
#include "COGCircleShape.h"

class COGBullet : public Component
{
public:
	COGBullet(GameObject* pGameObject);
	~COGBullet();

	virtual ComponentType GetType() const override;
};
#pragma once
#include "COGCircleShape.h"

class COGEnemyController : public Component
{
public:
	static std::vector<COGEnemyController*> mEnemiesSpawned;

public:
	COGEnemyController(GameObject* pGameObject);
	~COGEnemyController();

	virtual void Destroy() override;
	virtual ComponentType GetType() const override;
};
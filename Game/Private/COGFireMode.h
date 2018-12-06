#pragma once
#include "Component.h"
#include <vector>

class COGFireMode : public Component
{
public:
	static std::vector<COGFireMode*> mFireModeComponents;

protected:
	COGFireMode(GameObject* pGameObject, float fAmmoCount, float fTimeBeforeFiringNextShot, bool bSingleShotWeapons);

public:
	~COGFireMode();

	// Overridden Functions
	virtual void Destroy() override;
	virtual ComponentType GetType() const override;
	virtual void Update() = 0;
	virtual void FireWeapon() = 0;

private:
	float mTimer;
	float mAmmoCount;
	float mTimeBeforeFiringNextShot;
};
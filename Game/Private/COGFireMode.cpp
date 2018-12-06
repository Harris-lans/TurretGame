#include "COGFireMode.h"
#include <algorithm>

std::vector<COGFireMode*> COGFireMode::mFireModeComponents;

COGFireMode::COGFireMode(GameObject* pGameObject, float fAmmoCount, float fTimeBeforeFiringNextShot, bool bSingleShotWeapons)
	:Component(pGameObject)
{
	mAmmoCount = fAmmoCount;
	mTimeBeforeFiringNextShot = fTimeBeforeFiringNextShot;

	// Adding the weapon to the static list
	mFireModeComponents.push_back(this);
}

COGFireMode::~COGFireMode()
{
	// Destroying the component
	Destroy();
}

void COGFireMode::Destroy()
{
	// Removing the component from the static vector
	mFireModeComponents.erase(std::remove(mFireModeComponents.begin(), mFireModeComponents.end(), this), mFireModeComponents.end());

	// Removing self from the component list of the gameObject
	mGameObject->RemoveComponent(this);
}

ComponentType COGFireMode::GetType() const
{
	return ComponentType::FireMode;
}


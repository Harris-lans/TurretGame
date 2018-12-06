#include "COGBullet.h"

COGBullet::COGBullet(GameObject* pGameObject)
	:Component(pGameObject)
{
	// Nothing to do here for now
}

COGBullet::~COGBullet()
{
	Destroy();
}

ComponentType COGBullet::GetType() const
{
	return ComponentType::Bullet;
}
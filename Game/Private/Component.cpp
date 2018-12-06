#include "Component.h"

Component::Component(GameObject* pGameObject)
{
	mGameObject = pGameObject;
}

Component::~Component()
{
	Destroy();
}

void Component::Initialize()
{

}

void Component::Destroy()
{
	mGameObject->RemoveComponent(this);
}
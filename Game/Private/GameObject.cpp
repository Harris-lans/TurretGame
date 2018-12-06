#include "GameObject.h"
#include <algorithm>

int GameObject::gameObjectNumber = rand() % 999;

GameObject::GameObject(Hash hash)
{
	mHash = hash;
	++gameObjectNumber;
}

GameObject::~GameObject()
{
	std::size_t numberOfComponents = mComponents.size();
	for (std::size_t i = 0; i < numberOfComponents; i++)
	{
		delete mComponents[0];
	}
}

void GameObject::Initialize()
{
	for (Component* pComponent : mComponents)
	{
		pComponent->Initialize();
	}
}

void GameObject::AddComponent(Component* pComponent)
{
	mComponents.push_back(pComponent);
}

void GameObject::RemoveComponent(Component* pComponent)
{
	mComponents.erase(std::remove(mComponents.begin(), mComponents.end(), pComponent), mComponents.end());
}

int GameObject::NumberOfComponents() const
{
	return mComponents.size();
}


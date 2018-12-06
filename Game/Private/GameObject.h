#pragma once
#include "Engine\Public\EngineInterface.h"
#include "Component.h"
#include "HashMap.h"
#include <vector>


// Forward declaring the component class
class Component;

enum class ComponentType : int;

class GameObject
{
public:

	GameObject(Hash hash);

	~GameObject();

	void Initialize();
	
	void AddComponent(Component* pComponent);
	
	void RemoveComponent(Component* pComponent);

	int NumberOfComponents() const;

	template<class T>
	T* FindComponent(ComponentType eType)
	{
		for (Component* pComponent : mComponents)
		{
			if (pComponent->GetType() == eType)
			{
				return (T*)pComponent;
			}
		}

		return nullptr;
	}

private:
	std::vector<Component*> mComponents;

public:
	Hash mHash;
	static int gameObjectNumber;
};


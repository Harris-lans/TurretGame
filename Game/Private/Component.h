#pragma once
#include "GameObject.h"
#include <vector>

class GameObject;

// All the different types of components
enum class ComponentType : int
{
	Transform = 0,
	Physics,
	BoxShape,
	CircleShape,
	Explosion,
	LineShape,
	LineCircleShape,
	LineBoxShape,
	FriendlyMissile,
	TextRenderer,
	DestroyOnCollision,
	DestroyWhenOutOfBounds,
	DamageOnCollisionWithTurret,
	FiniteStateMachine,
	FiniteStateMachine_State,
	Turret,
	TurretState,
	FireMode,
	EnemyController,
	EnemySpawner,
	Reticle,
	Bullet,
};


class Component
{
public:
	Component(GameObject* gameObject);
	virtual ~Component();

public:

	virtual ComponentType GetType() const = 0;

	virtual void Initialize();
	virtual void Destroy();

protected:

	template<class T>
	void AddToComponentVector(std::vector<T*>& componentVector)
	{
		componentVector.push_back((T*)this);
	}

	template<class T>
	void RemoveFromComponentVector(std::vector<T*>& componentVector)
	{
		for (int i = 0; i < componentVector.size(); i++)
		{
			if (componentVector[i] == this)
			{
				componentVector.erase(componentVector.begin() + i);
				return;
			}
		}
	}

public:

	GameObject * mGameObject;

};
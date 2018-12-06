#pragma once
#include "Component.h"
#include "COGTransform.h"
#include "InputManager.h"

class COGReticle : public Component
{
public:
	COGReticle(GameObject* pGameObject);
	~COGReticle();

	// Overidden Function
	virtual void Initialize() override;
	virtual void Destroy() override;
	virtual ComponentType GetType() const override;

	virtual void Update();
	exVector2& GetReticlePosition();

private:
	InputManager*	mInputManager;
	COGTransform*	mTransformComponent;
};
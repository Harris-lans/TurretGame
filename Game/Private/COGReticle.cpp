#include "COGReticle.h"

COGReticle::COGReticle(GameObject* pGameObject)
	:Component(pGameObject)
{
	mInputManager = InputManager::GetInstance();
}

COGReticle::~COGReticle()
{
	Destroy();
}

void COGReticle::Initialize()
{
	mTransformComponent = mGameObject->FindComponent<COGTransform>(ComponentType::Transform);
}

void COGReticle::Destroy()
{
	// Removing from the component's list
	mGameObject->RemoveComponent(this);
}

ComponentType COGReticle::GetType() const
{
	return ComponentType::Reticle;
}

void COGReticle::Update()
{
	exVector2 mousePosition = mInputManager->GetInputState()->GetMousePosition();
	exVector2& currentObjectPosition = mTransformComponent->GetPosition();

	// Setting the new position of the reticle
	currentObjectPosition = mousePosition;
}
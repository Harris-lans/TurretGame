#pragma once
#include "COGTransform.h"
#include "GameObjectManager.h"

class COGDestroyWhenOutOfBounds : public Component
{
public:
	static std::vector<COGDestroyWhenOutOfBounds*> mDestroyWhenOutOfBoundsComponents;

public:
	COGDestroyWhenOutOfBounds(GameObject* pGameObject);
	~COGDestroyWhenOutOfBounds();
	virtual void Update();

	// Overriden Function
	virtual ComponentType GetType() const override;
	virtual void Initialize() override;
	virtual void Destroy() override;

private:
	GameObjectManager * mGameObjectManager;
	COGTransform*		mTransformComponent;
};
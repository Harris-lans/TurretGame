#include "COGPhysics.h"
#include "GameObjectManager.h"

class COGDestroyOnCollisionWith : public Component, public IPhysicsCollisionEvent
{
public:
	COGDestroyOnCollisionWith(GameObject* pGameObject, ComponentType pComponentToSearchFor);
	~COGDestroyOnCollisionWith();

	virtual ComponentType GetType() const override;
	virtual void Initialize() override;
	virtual void Destroy() override;
	virtual void OnCollision(COGPhysics* pPhysicsComponent, COGPhysics* pOtherPhysicsComponent, exVector2 pNormalVector) override;

private:
	ComponentType			mComponentToSearchFor;
	GameObjectManager*		mGameObjectManager;
	COGPhysics*				mPhysicsComponent;
};

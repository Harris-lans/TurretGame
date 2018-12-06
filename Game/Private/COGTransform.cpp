#include "COGTransform.h"

COGTransform::COGTransform(GameObject* gameObject, exVector2 pPosition)
	:Component(gameObject)
{
	mPosition = pPosition;
}

COGTransform::~COGTransform()
{
	Destroy();
	Console::LogString("Deleted Transform Component! \n");
}

ComponentType COGTransform::GetType() const
{
	return ComponentType::Transform;
}

exVector2& COGTransform::GetPosition()
{
	return mPosition;
}

void COGTransform::SetPosition(exVector2& newPosition)
{
	mPosition.x = newPosition.x;
	mPosition.y = newPosition.y;
}
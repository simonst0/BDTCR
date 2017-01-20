//////////////////////////////////////////////////////
// Game Development			- BrainDamaged Engine	//
// Simon Steiner			- 1510601034, fhs38598	//
// Katrin-Anna Zibuschka	- 1510601044, fhs38708	//
//////////////////////////////////////////////////////

#pragma once

#include <memory>

class GameObject;

class IComponent
{
public:
	typedef std::unique_ptr<IComponent> Ptr;

	IComponent(GameObject& gameObject)
		: m_gameObject(gameObject)
	{
	}

	virtual ~IComponent() = default;

	virtual bool VInit() = 0;
	virtual void VUpdate(float fDeltaTime) = 0;

protected:

	GameObject& m_gameObject;
};
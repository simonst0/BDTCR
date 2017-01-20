//////////////////////////////////////////////////////
// Game Development			- BrainDamaged Engine	//
// Simon Steiner			- 1510601034, fhs38598	//
// Katrin-Anna Zibuschka	- 1510601044, fhs38708	//
//////////////////////////////////////////////////////

#include "stdafx.h"

#include "GameObject.h"

using namespace sf;

void
GameObject::AddComponent(IComponent::Ptr component)
{
	m_componentList.push_back(move(component));
}

void GameObject::Update(float fDeltaTime)
{
	for (auto& comp : m_componentList)
		comp->VUpdate(fDeltaTime);
}

bool GameObject::Init()
{
	for (auto& comp : m_componentList)
	{
		if (!comp->VInit())
		{
			err() << "Could not initialize component of object " << m_id << std::endl;
			return false;
		}
	}
	return true;
}
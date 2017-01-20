//////////////////////////////////////////////////////
// Game Development			- BrainDamaged Engine	//
// Simon Steiner			- 1510601034, fhs38598	//
// Katrin-Anna Zibuschka	- 1510601044, fhs38708	//
//////////////////////////////////////////////////////

#pragma once

#include "IComponent.h"

class IControlComponent : public IComponent 
{
public:
	IControlComponent(GameObject& gameObject)
		: IComponent(gameObject) {}

	virtual bool VInit() = 0;
	virtual void VUpdate(float fDeltaTime) = 0;
};

//////////////////////////////////////////////////////
// Game Development			- Assignment 2			//
// Simon Steiner			- 1510601034, fhs38598	//
// Katrin-Anna Zibuschka	- 1510601044, fhs38708	//
//////////////////////////////////////////////////////

#pragma once

#include "IComponent.h"

class PlayerMoveComponent : public IComponent
{
public:
	typedef std::unique_ptr<PlayerMoveComponent> Ptr;

	PlayerMoveComponent(
		GameObject &gameObject,
		int playerIndex);

	virtual bool VInit() override;
	virtual void VUpdate(float fDeltaTime) override;

private:
	int m_iPlayerIndex;
};
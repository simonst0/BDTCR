//////////////////////////////////////////////////////
// Game Development			- BrainDamaged Engine	//
// Simon Steiner			- 1510601034, fhs38598	//
// Katrin-Anna Zibuschka	- 1510601044, fhs38708	//
//////////////////////////////////////////////////////

#pragma once
#include "stdafx.h"
#include "Box2D/Box2D.h"

class Box2DContactListener : public b2ContactListener
{
	virtual void BeginContact(b2Contact* contact);
	virtual void EndContact(b2Contact* contact);
};

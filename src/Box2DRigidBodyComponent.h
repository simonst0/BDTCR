//////////////////////////////////////////////////////
// Game Development			- BrainDamaged Engine	//
// Simon Steiner			- 1510601034, fhs38598	//
// Katrin-Anna Zibuschka	- 1510601044, fhs38708	//
//////////////////////////////////////////////////////

#pragma once
#include "stdafx.h"
#include "IComponent.h"
#include "Box2D\Box2D.h"

class Box2DRigidBodyComponent: public IComponent
{
public:
	Box2DRigidBodyComponent(GameObject& gameObject, float startX, float startY, float angle, float damping, std::string id, b2BodyType type);

	virtual bool VInit() override;
	virtual void VUpdate(float fDeltaTime) override;
	void AddFixture(float width, float height, float mass, int groupIndex, float restitution, float friction);
	std::string m_id;

private:
	b2BodyDef m_bodyDef;
	b2Body* m_body;
	std::vector<b2PolygonShape*> m_shapes;
	enum colliderCategory
	{
		WAYPOINT = 0x0003,
		PLAYER = 0x0002,
		ENVIRONMENT = 0x0001,
		NONE = 0x0004,
	};
};
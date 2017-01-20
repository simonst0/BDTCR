//////////////////////////////////////////////////////
// Game Development			- BrainDamaged Engine	//
// Simon Steiner			- 1510601034, fhs38598	//
// Katrin-Anna Zibuschka	- 1510601044, fhs38708	//
//////////////////////////////////////////////////////

#include "stdafx.h"
#include "Box2DRigidBodyComponent.h"
#include "GameObject.h"
#include "IComponent.h"
#include "GameObjectManager.h"
#include "Box2DPhysicsManager.h"

//gameobject startX startY angle damping id bodyType
Box2DRigidBodyComponent::Box2DRigidBodyComponent(GameObject& gameObject, float startX, float startY, float angle, float damping, std::string id, b2BodyType type)
	: IComponent(gameObject)
{
	m_id = id;
	m_bodyDef.type = type;
	m_bodyDef.position.Set(startX/100, startY/100);
	m_bodyDef.angle = angle;
	//linear not used
	m_bodyDef.linearDamping = damping; 
	m_bodyDef.angularDamping = damping;
	//rest phase with low cpu overhead allowed
	m_bodyDef.allowSleep = true;
	m_bodyDef.awake = true;
	m_body = Box2DPhysicsManager::GetInstance().CreateBodyInWorld(&m_bodyDef, id);
	m_body->SetUserData(this);
}
bool Box2DRigidBodyComponent::VInit()
{
	return true;
}
void Box2DRigidBodyComponent::VUpdate(float fDeltaTime)
{
}
void Box2DRigidBodyComponent::AddFixture(float width, float height, float mass, int groupIndex, float restitution, float friction)
{
	b2PolygonShape shape;
	shape.SetAsBox((width / 2)/100, (height / 2)/100);
	m_shapes.push_back(&shape);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = mass/(width*height);
	fixtureDef.friction = friction;
	fixtureDef.restitution = restitution;
	uint16 category, mask;
	if (groupIndex == -1)
	{
		category = WAYPOINT;
		mask = PLAYER;
		fixtureDef.isSensor = true;
	}
	else if (groupIndex == 1)
	{
		category = ENVIRONMENT;
		mask = (PLAYER | ENVIRONMENT);
	}
	else
	{
		category = PLAYER;
		mask = (PLAYER | ENVIRONMENT);
	}
	fixtureDef.filter.categoryBits = category;
	fixtureDef.filter.maskBits = mask;
	
	m_body->CreateFixture(&fixtureDef);
}

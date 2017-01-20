//////////////////////////////////////////////////////
// Game Development			- BrainDamaged Engine	//
// Simon Steiner			- 1510601034, fhs38598	//
// Katrin-Anna Zibuschka	- 1510601044, fhs38708	//
//////////////////////////////////////////////////////

#include "stdafx.h"
#include "Box2DContactListener.h"
#include "Box2DRigidBodyComponent.h"
#include "EventBus.h"
#include "IEvent.h"

void Box2DContactListener::BeginContact(b2Contact* contact)
{
	std::string idA, idB;
	void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
	if (bodyUserDataA)
		idA = static_cast<Box2DRigidBodyComponent*>(bodyUserDataA)->m_id;

	void* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();
	if (bodyUserDataB)
		idB = static_cast<Box2DRigidBodyComponent*>(bodyUserDataB)->m_id;

	CollisionStartEvent* e = new CollisionStartEvent(idA, idB);
	EventBus::GetInstance().FireEvent(e);
	delete e;
}
void Box2DContactListener::EndContact(b2Contact* contact)
{
	std::string idA, idB;
	void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
	if (bodyUserDataA)
		idA = static_cast<Box2DRigidBodyComponent*>(bodyUserDataA)->m_id;

	void* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();
	if (bodyUserDataB)
		idB = static_cast<Box2DRigidBodyComponent*>(bodyUserDataB)->m_id;

	CollisionEndEvent* e = new CollisionEndEvent(idA, idB);
	EventBus::GetInstance().FireEvent(e);
	delete e;
}
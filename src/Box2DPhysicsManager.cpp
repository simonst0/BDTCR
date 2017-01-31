//////////////////////////////////////////////////////
// Game Development			- BrainDamaged Engine	//
// Simon Steiner			- 1510601034, fhs38598	//
// Katrin-Anna Zibuschka	- 1510601044, fhs38708	//
//////////////////////////////////////////////////////

#include "stdafx.h"
#include "Box2DPhysicsManager.h"
#include <iostream>

Box2DPhysicsManager& Box2DPhysicsManager::GetInstance()
{
	static Box2DPhysicsManager instance;
	return instance;
}
void Box2DPhysicsManager::Unbind(std::string bodyId)
{
	if (m_bodies.count(bodyId) > 0)
		m_world->DestroyBody(m_bodies[bodyId]);

	if (m_bodies.count(bodyId) > 0)
		m_bodies.erase(bodyId);
}
b2Body* Box2DPhysicsManager::GetBodyById(std::string id)
{
	if (m_bodies.count(id) > 0)
		return m_bodies[id];

	return nullptr;
}
float Box2DPhysicsManager::GetAngleById(std::string id)
{
	float rotation = 0;
	if (m_bodies.count(id) <= 0)
		rotation;
	rotation = m_bodies[id]->GetAngle();
	return rotation;
}
b2Vec2 Box2DPhysicsManager::GetPositionById(std::string id)
{
	if (m_bodies.count(id) <= 0)
		return b2Vec2(0, 0);
	auto shape = m_bodies[id]->GetFixtureList()->GetShape();
	b2AABB aabb;
	shape->ComputeAABB(&aabb, m_bodies[id]->GetTransform(), 0);
	auto vec = aabb.GetExtents();
	auto position = m_bodies[id]->GetPosition();
	position.x = (position.x - vec.x)*100;
	position.y = (position.x - vec.y)*100;
	return position;
}
sf::Transform Box2DPhysicsManager::GetTransformById(std::string id, sf::Transform spriteTransform)
{
	if (m_bodies.count(id) <= 0)
		return sf::Transform();

	auto transform = m_bodies[id]->GetTransform();

	auto shape = m_bodies[id]->GetFixtureList()->GetShape();
	b2AABB aabb;
	shape->ComputeAABB(&aabb, m_bodies[id]->GetTransform(), 0);
	auto vec = aabb.GetExtents();

	auto p = transform.p;
	auto q = transform.q;
	//Translation * Rotation (* Vector)
	return sf::Transform().translate(sf::Vector2f(p.x*100, p.y*100)) * sf::Transform().rotate(q.GetAngle()*57.2958f);
}
b2Vec2 Box2DPhysicsManager::GetVelocityById(std::string id)
{
	b2Vec2 b2Velocity;
	if (m_bodies.count(id) <= 0)
		return b2Velocity;

	b2Velocity = m_bodies[id]->GetLinearVelocity();

	return b2Velocity;
}
void Box2DPhysicsManager::DebugDraw()
{
	auto body = m_world->GetBodyList();

	while (body)
	{
		auto actFixture = body->GetFixtureList();
		while (actFixture)
		{
			auto shape = actFixture->GetShape();
			b2AABB aabb;
			shape->ComputeAABB(&aabb, body->GetTransform(), 0);
			auto vec = aabb.GetExtents();

			auto transform = body->GetTransform();
			auto p = transform.p;
			auto q = transform.q;

			auto rect = sf::RectangleShape(sf::Vector2f(vec.x * 200, vec.y * 200));
			rect.setFillColor(sf::Color(0, 0, 0, 0));
			rect.setOutlineColor(sf::Color(255, 0, 0, 255));
			rect.setOutlineThickness(3);

			auto trans = rect.getTransform();
			trans.translate(sf::Vector2f((p.x-vec.x)*100, (p.y-vec.y)*100)) * sf::Transform().rotate(q.GetAngle()* 57.2958f);
		
			m_game->getWindow().draw(rect, trans);

			actFixture = actFixture->GetNext();
		}
		body = body->GetNext();
	}
}
void Box2DPhysicsManager::ApplyForce(std::string id, b2Vec2 force)
{
	if (m_bodies.count(id) <= 0)
		return;
	auto body = m_bodies[id];
	body->ApplyForceToCenter(force, true);
}
void Box2DPhysicsManager::SetAngle(std::string id, float angle)
{
	if (m_bodies.count(id) <= 0)
		return;
	auto body = m_bodies[id];
	auto transform = body->GetTransform();
	auto p = transform.p;
	auto q = transform.q;

	body->SetTransform(p, angle);	
}
void Box2DPhysicsManager::ApplyImpulse(std::string id, b2Vec2 impulse)
{
	if (m_bodies.count(id) <= 0)
		return;
	m_bodies[id]->ApplyLinearImpulseToCenter(impulse, true);
}
void Box2DPhysicsManager::Update(float deltaTime)
{
	//for (int i = 0; i < 1 / m_timeStep; i++)
	//{
		//m_world.Step(m_timeStep, m_velocityIterations, m_positionIterations);
	//}
	m_world->Step(deltaTime, 1, 1);
	//Manual states this needs to be done
	m_world->ClearForces();
}
b2Body* Box2DPhysicsManager::CreateBodyInWorld(b2BodyDef* bodyDef, std::string id)
{
	auto body = m_world->CreateBody(bodyDef);
	m_bodies[id] = body;
	return body;
}
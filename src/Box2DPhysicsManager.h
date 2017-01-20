//////////////////////////////////////////////////////
// Game Development			- BrainDamaged Engine	//
// Simon Steiner			- 1510601034, fhs38598	//
// Katrin-Anna Zibuschka	- 1510601044, fhs38708	//
//////////////////////////////////////////////////////

#pragma once
#include "stdafx.h"
#include "Box2D\Box2D.h"
#include "Game.h"
#include "Box2DContactListener.h"

class Box2DPhysicsManager
{
public:
	~Box2DPhysicsManager() { delete m_world; }
	static Box2DPhysicsManager& GetInstance();
	void Unbind(std::string gameObjectId);
	b2Body* CreateBodyInWorld(b2BodyDef* bodyDef, std::string id);
	void ApplyForce(std::string id, b2Vec2 force);
	void SetAngle(std::string id, float angle);
	void ApplyImpulse(std::string id, b2Vec2 impulse);
	b2Body* GetBodyById(std::string id);
	b2Vec2 GetPositionById(std::string id);
	float GetAngleById(std::string id);
	sf::Transform GetTransformById(std::string id, sf::Transform spriteTransform);
	b2Vec2 GetVelocityById(std::string id);
	void DebugDraw();
	void Update(float deltaTime);
	void SetGame(Game* game) { m_game = game; }

private:
	Box2DPhysicsManager() { m_world->SetContactListener(new Box2DContactListener()); }
	b2World* m_world = new b2World(b2Vec2(0, 0));
	std::map<std::string, b2Body*> m_bodies;

	//config 
	const float32 m_timeStep = 1.0f / 60.0f;
	const int32 m_velocityIterations = 4;
	const int32 m_positionIterations = 2;
	Game* m_game;
};
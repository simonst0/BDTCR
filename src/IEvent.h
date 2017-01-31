//////////////////////////////////////////////////////
// Game Development			- BrainDamaged Engine	//
// Simon Steiner			- 1510601034, fhs38598	//
// Katrin-Anna Zibuschka	- 1510601044, fhs38708	//
//////////////////////////////////////////////////////

#pragma once
#include "stdafx.h"

class IEvent
{
public:
	IEvent(EventIDs id)
		: ID(id)
	{}
	EventIDs ID;
};

class CollisionStartEvent : public IEvent
{
public:
	CollisionStartEvent(std::string bodyId1, std::string bodyId2)
		: IEvent(EventIDs::CollisionStart)
		, m_bodyId1(bodyId1)
		, m_bodyId2(bodyId2)
	{}

	std::string m_bodyId1, m_bodyId2;
};

class CollisionEndEvent : public IEvent
{
public:
	CollisionEndEvent(std::string bodyId1, std::string bodyId2)
		: IEvent(EventIDs::CollisionEnd)
		, m_bodyId1(bodyId1)
		, m_bodyId2(bodyId2)
	{}

	std::string m_bodyId1, m_bodyId2;
};

class PlayerDeathEvent : public IEvent
{
public:
	PlayerDeathEvent(std::string gameObjectID, int playerID) 
		: IEvent(EventIDs::PlayerDeath)
		, m_gameObjectID(gameObjectID)
		, m_playerID(playerID)
	{}

	std::string m_gameObjectID;
	int m_playerID;
};
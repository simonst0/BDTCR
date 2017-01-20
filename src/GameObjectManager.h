//////////////////////////////////////////////////////
// Game Development			- BrainDamaged Engine	//
// Simon Steiner			- 1510601034, fhs38598	//
// Katrin-Anna Zibuschka	- 1510601044, fhs38708	//
//////////////////////////////////////////////////////

#pragma once
#include "stdafx.h"
#include "Game.h"
#include "GameObject.h"
#include "Player.h"
#include "ScoreComponent.h"

class GameObjectManager
{
public:
	static GameObjectManager& GetInstance();
	std::vector<GameObject*> findObjectByArea(sf::Vector2f position, float radius);
	GameObject* findObjectById(std::string id);
	void AddGameObject(std::unique_ptr<GameObject> gameObject);
	void GameObjectWantsToDie(std::string id);
	void Update(float deltaTime);
	void Clear();

	std::vector<int> GetRegisteredPlayerIDs();
	std::vector<int> GetDeregisteredPlayerIDs();
	int GetRegisteredPlayersCounter() { return GetRegisteredPlayerIDs().size(); }

	int GetMultipleNameCounter(string name);
	void IncreaseMultipleNameCounter(string name);

	void AddPlayer(int gamepadID);
	void AddPlayerScore(int gamepadID, ScoreComponent* score);
	void RemovePlayer(int gamepadID);
	void RemoveAllPlayers();
	ScoreComponent* GetPlayerScore(int gamepadID);
	std::map<std::string, int> GetPlayerScores();

private:
	GameObjectManager()
		: m_gameObjects()
		, m_startingPositions()
	{}
	~GameObjectManager() = default;

	void RemoveGameObject(std::string id);
	void UnbindManagers(std::string id);

	std::map<std::string, std::unique_ptr<GameObject>> m_gameObjects;
	std::map<std::string, sf::Vector2f> m_startingPositions;
	std::unique_ptr<Player> m_players[Game::PLAYER_COUNT];
	std::map<std::string, int> m_multipleNameCounter;
};
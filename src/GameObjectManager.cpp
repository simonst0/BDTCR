//////////////////////////////////////////////////////
// Game Development			- BrainDamaged Engine	//
// Simon Steiner			- 1510601034, fhs38598	//
// Katrin-Anna Zibuschka	- 1510601044, fhs38708	//
//////////////////////////////////////////////////////

#include "stdafx.h"
#include "GameObjectManager.h"
#include "Box2DPhysicsManager.h"
#include "RenderManager.h"

GameObjectManager& GameObjectManager::GetInstance()
{
	static GameObjectManager instance;
	return instance;
}
std::vector<GameObject*> GameObjectManager::findObjectByArea(sf::Vector2f position, float radius)
{
	std::vector<GameObject*> temp;
	for (auto const& pair : m_gameObjects)
	{
		GameObject* actGameObject = pair.second.get();
		auto pos = Box2DPhysicsManager::GetInstance().GetPositionById(actGameObject->GetId());
		sf::Vector2f actGameObjectPosition = sf::Vector2f(pos.x, pos.y);

		float distanceX = actGameObjectPosition.x - position.x;
		float distanceY = actGameObjectPosition.y - position.y;
		if (std::sqrt(distanceX*distanceX + distanceY*distanceY) <= radius)
			temp.push_back(actGameObject);
	}
	return temp;
}
GameObject* GameObjectManager::findObjectById(std::string id)
{
	if (m_gameObjects.count(id) >0) 
		return m_gameObjects[id].get(); 
	
	return nullptr;
}

void GameObjectManager::AddGameObject(std::unique_ptr<GameObject> gameObject)
{
	std::string id = gameObject->GetId();
	m_gameObjects[id] = move(gameObject);
}

void GameObjectManager::RemoveGameObject(std::string id)
{
	UnbindManagers(id);
	m_gameObjects.erase(id);
	m_startingPositions.erase(id);
}

void GameObjectManager::GameObjectWantsToDie(std::string id)
{
	auto gameObject = findObjectById(id);

	if (gameObject == nullptr) return;

	gameObject->MarkForDelete();
}

void GameObjectManager::Update(float deltaTime)
{
	std::list<std::string> removeList;
	for (auto& gameObject : m_gameObjects)
	{
		if (gameObject.second->IsMarkedForDelete())
			removeList.push_back(gameObject.second->GetId());
		else
			gameObject.second->Update(deltaTime);
	}

	auto IDs = GetRegisteredPlayerIDs();

	for (auto it = IDs.begin(); it != IDs.end(); it++) {
		m_players[*it]->Update(deltaTime);
	}

	for (auto& id : removeList)
	{
		RemoveGameObject(id);
	}
}

void GameObjectManager::AddPlayer(int gamepadID) 
{	
	if (gamepadID < 0 || gamepadID >= Game::PLAYER_COUNT || m_players[gamepadID] != nullptr)
		return;

	m_players[gamepadID] = make_unique<Player>(gamepadID);
	sf::err() << "Gamepad " << gamepadID << " registered" << std::endl;
}

void GameObjectManager::AddPlayerScore(int gamepadID, std::unique_ptr<ScoreComponent> score)
{
	if (!PlayerExists(gamepadID))
		return;

	m_players[gamepadID]->AddScore(move(score));
}

void GameObjectManager::AddPlayerHealth(int gamepadID, std::unique_ptr<HealthComponent> health)
{
	if (!PlayerExists(gamepadID))
		return;

	m_players[gamepadID]->AddHealth(move(health));
}

std::map<std::string, int> GameObjectManager::GetPlayerScores()
{
	std::map<std::string, int> scores;
	for (auto id : GetRegisteredPlayerIDs())
	{
		scores["Player " + to_string(id+1)] = m_players[id]->GetScore();
	}

	return scores;
}

std::vector<HealthComponent*> GameObjectManager::GetPlayerHealths()
{
	std::vector<HealthComponent*> healths;

	for (auto id : GetRegisteredPlayerIDs())
	{
		if(m_players[id]->IsAlive())
			healths.push_back(m_players[id]->GetHealthComponent());
	}

	return healths;
}

void GameObjectManager::RemovePlayer(int gamepadID) {
	if (gamepadID < 0 || gamepadID >= Game::PLAYER_COUNT)
		return;

	m_players[gamepadID] = nullptr;
	sf::err() << "Gamepad " << gamepadID << " deregistered" << std::endl;
}

void GameObjectManager::RemoveAllPlayers() 
{
	auto IDs = GetRegisteredPlayerIDs();

	for (auto it = IDs.begin(); it != IDs.end(); it++) {
		m_players[*it] = nullptr;
	}
}

void GameObjectManager::PlayerDies(int gamepadID)
{
	if (!PlayerExists(gamepadID))
		return;

	m_players[gamepadID]->Die();
}

void GameObjectManager::Reset(int gamepadID)
{
	if (!PlayerExists(gamepadID))
		return;
	m_players[gamepadID]->Reset();
}

HealthComponent* GameObjectManager::GetPlayerHealth(int gamepadID)
{
	if (!PlayerExists(gamepadID))
		return nullptr;

	return m_players[gamepadID]->GetHealthComponent();
}

ScoreComponent* GameObjectManager::GetPlayerScore(int gamepadID)
{
	if (!PlayerExists(gamepadID))
		return nullptr;

	return m_players[gamepadID]->GetScoreComponent();
}

std::vector<int> GameObjectManager::GetRegisteredPlayerIDs()
{
	std::vector<int> ids;

	for (int i = 0; i < Game::PLAYER_COUNT; i++) {
		if (m_players[i] != nullptr)
			ids.push_back(i);
	}
	return ids;
}

std::vector<int> GameObjectManager::GetDeregisteredPlayerIDs()
{
	std::vector<int> ids;

	for (int i = 0; i < Game::PLAYER_COUNT; i++) {
		if (m_players[i] == nullptr)
			ids.push_back(i);
	}
	return ids;
}

void GameObjectManager::Clear()
{
	for (auto& gameObject : m_gameObjects) {
		UnbindManagers(gameObject.second->GetId());
	}

	m_gameObjects.clear();
	m_startingPositions.clear();

	auto IDs = GetRegisteredPlayerIDs();

	for (auto it = IDs.begin(); it != IDs.end(); it++) {
		m_players[*it]->DeactivateGUI();
	}
}

void GameObjectManager::UnbindManagers(std::string id) {
	RenderManager::getInstance().Unbind(id);
	Box2DPhysicsManager::GetInstance().Unbind(id);
}

int GameObjectManager::GetMultipleNameCounter(std::string name) 
{
	if (m_multipleNameCounter.count(name) > 0)
		return m_multipleNameCounter[name];
	return 0;
}

void GameObjectManager::IncreaseMultipleNameCounter(std::string name) 
{
	if (m_multipleNameCounter.count(name) == 0)
		m_multipleNameCounter[name] = 0;
	m_multipleNameCounter[name]++;
}

bool GameObjectManager::PlayerExists(int gamepadID)
{
	return !(gamepadID < 0 || gamepadID >= Game::PLAYER_COUNT || m_players[gamepadID] == nullptr);
}


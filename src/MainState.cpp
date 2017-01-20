//////////////////////////////////////////////////////
// Game Development			- BrainDamaged Engine	//
// Simon Steiner			- 1510601034, fhs38598	//
// Katrin-Anna Zibuschka	- 1510601044, fhs38708	//
//////////////////////////////////////////////////////

#include "stdafx.h"

#include "MainState.h"
#include "Game.h"

#include "SpriteRenderComponent.h"
#include "SteeringComponent.h"
#include "PlayerGamepadControlComponent.h"
#include "PlayerBorderComponent.h"
#include "LayerComponent.h"
#include "InputManager.h"
#include "RenderManager.h"
#include "NLTmxMap.h"
#include "TextureFactory.h"
#include "HealthComponent.h"
#include "ScoreComponent.h"
#include "GameObjectManager.h"
#include "Box2DPhysicsManager.h"
#include "Box2DRigidBodyComponent.h"
#include "ViewManager.h"
#include "BoosterComponent.h"
#include <iostream>


using namespace sf;
using namespace std;

void MainState::VInit()
{
	LoadTMXInput(StaticStrings::ResourcePath + "game.tmx");
	
	SetCamera();

	BindInput();

	m_deathCounter = 0;
	m_environmentCounter = 0;
}

void MainState::LoadTMXInput(const string& filename) {

	FileInputStream mapStream;
	if (!mapStream.open(filename))
	{
		err() << "loadMap: could not open file " << filename << endl;
		return;
	}

	// convert FileInputStream to char* mapBuffer
	char* mapBuffer = new char[mapStream.getSize() + 1];
	mapStream.read(mapBuffer, mapStream.getSize());
	mapBuffer[mapStream.getSize()] = '\0';

	// now lets load a NLTmxMap
	NLTmxMap* tilemap = NLLoadTmxMap(mapBuffer);
	delete mapBuffer;
	err() << "Load tilemap with size: " << tilemap->width << ", "
		<< tilemap->height << " and tilesize: " << tilemap->tileWidth
		<< ", " << tilemap->tileHeight << std::endl;

	// load textures for every tileset
	for (auto tileset : tilemap->tilesets)
	{
		m_textureFactory.LoadTexture(tileset->filename);
	}

	auto map = make_unique<GameObject>("Map");

	// go through all layers
	for (int layerIdx = 0; layerIdx < (int)tilemap->layers.size(); layerIdx++)
	{
		NLTmxMapLayer* layer = tilemap->layers[layerIdx];
		err() << "Load layer: " << layer->name << " with width: "
			<< layer->width << " and height: " << layer->height << std::endl;

		int size = layer->width * layer->height;

		auto layerComponent = make_unique<LayerComponent>(*map.get(), m_game->getWindow());

		// go over all elements in the layer
		for (int i = 0; i < size; i++)
		{
			int grid = layer->data[i];

			if (grid == 0)
			{
				// 0 means there is no tile at this grid position.

				// This continue also indicates that the layers are not 
				// represented as two-dimensional arrays, but 
				// only a list of tiles sorted by position from top left
				// to bottom right. (Hint: position could be useful for 
				// quickly finding, which tiles to cull from current 
				// viewport.)					
				continue;
			}

			// get tileset and tileset texture
			NLTmxMapTileset* tileset = tilemap->getTilesetForGrid(grid);
			Vector2i tileSize(tilemap->tileWidth, tilemap->tileHeight);
			Texture* texture = m_textureFactory.GetTexture(tileset->filename);

			// horizontal tile count in tileset texture
			int tileCountX = texture->getSize().x / tileSize.x;

			// calculate position of tile
			Vector2f position;
			position.x = (i % layer->width) * (float)tileSize.x;
			position.y = (i / layer->width) * (float)tileSize.y;
			//position += offset;

			// calculate 2d idx of tile in tileset texture
			int idx = grid - tileset->firstGid;
			int idxX = idx % tileCountX;
			int idxY = idx / tileCountX;

			// calculate source area of tile in tileset texture
			IntRect source(idxX * tileSize.x, idxY * tileSize.y, tileSize.x, tileSize.y);

			// add the tile to the layer
			layerComponent->AddTile(texture, source, position);
		}

		// bind the layer to the rendermanager and then to the object
		RenderManager::getInstance().Bind(map->GetId(), layerIdx, layerComponent.get());
		map->AddComponent(move(layerComponent));
	}

	GameObjectManager::GetInstance().AddGameObject(move(map));
	auto registeredIDs = GameObjectManager::GetInstance().GetRegisteredPlayerIDs();

	// go through all object layers (player etc)
	for (auto group : tilemap->groups)
	{
		// go over all objects per layer
		for (auto object : group->objects)
		{
			LoadGameObjectFromTMX(object, registeredIDs);
		}
	}
}

void MainState::LoadGameObjectFromTMX(NLTmxMapObject* object, std::vector<int> registeredPlayers)
{
	bool initializeTextureRectLeft = false;
	bool initializeTextureRectTop = false;
	bool initializeTexture = false;
	bool initializeInputComponent = false;
	bool initializeScale = false;
	bool isUnregisteredPlayer = false;

	float scale = 1;
	int RectLeft = 0; int RectTop = 0;
	int InputPlayerId;
	string texturePath;
	float mass = 0;
	float restititution = 0;
	float damping = 0;
	int groupIndex = 1;

	//handle empty Bodies as static body
	if (object->properties.capacity() <= 0)
	{
		GameObject* gameObject = new GameObject("environment" + to_string(m_environmentCounter));
		m_environmentCounter++;
		float width, height;
		if (object->width == 0)
		{
			width = 10; height = 10;
		}
		else
		{
			width = object->width;
			height = object->height;
		}
		auto body = make_unique<Box2DRigidBodyComponent>(*gameObject, object->x + width / 2, object->y + height / 2, 0, 0, gameObject->GetId(), b2_staticBody);
		body->AddFixture(width, height, 0, groupIndex, 1, 1);
		gameObject->AddComponent(move(body));
		gameObject->Init();
		GameObjectManager::GetInstance().AddGameObject(unique_ptr<GameObject>(gameObject));
		return;
	}

	for (auto property : object->properties)
	{
		auto name = property->name;
		if (name == "TextureRectLeft")
		{
			initializeTextureRectLeft = true;
			RectLeft = stoi(property->value);
		}
		else if (name == "TextureRectTop")
		{
			initializeTextureRectTop = true;
			RectTop = stoi(property->value);
		}
		else if (name == "Texture")
		{
			initializeTexture = true;
			texturePath = property->value;
		}
		else if (name == "InputComponent")
		{
			auto inputID = stoi(property->value) - 1;

			for (auto it = registeredPlayers.begin(); it != registeredPlayers.end(); ++it) {
				if (inputID == *it) {
					initializeInputComponent = true;
					InputPlayerId = inputID;
				}
			}

			if (!initializeInputComponent) {
				isUnregisteredPlayer = true;
			}
		}
		else if (name == "scale")
		{
			initializeScale = true;
			scale = stof(property->value);
		}
		else if (name == "Mass")
			mass = stof(property->value);
		else if (name == "Restitution")
			restititution = stof(property->value);
		else if (name == "Damping")
			damping = stof(property->value);
		else if (name == "GroupIndex")
			groupIndex = stoi(property->value);
	}

	// if the player isn't registered, the GameObject shouldn't be initialized
	if (object->type == "Player" && isUnregisteredPlayer)
		return;

	GameObject* gameObject;
	if (m_gameObjectManager.findObjectById(object->name) != nullptr)
	{
		auto counter = m_gameObjectManager.GetMultipleNameCounter(object->name);
		gameObject = new GameObject(object->name + std::to_string(counter + 1));
		m_gameObjectManager.IncreaseMultipleNameCounter(object->name);
	}
	else
	{
		gameObject = new GameObject(object->name);
	}
	unique_ptr<SpriteRenderComponent> renderComp;
	IntRect textureRect{};
	textureRect.width = object->width;
	textureRect.height = object->height;

	if (initializeTextureRectLeft)
		textureRect.left = RectLeft;
	if (initializeTextureRectTop)
		textureRect.top = RectTop;
	if (initializeTexture)
	{
		renderComp = make_unique<SpriteRenderComponent>(*gameObject, this->m_game->getWindow(), StaticStrings::ResourcePath + texturePath);
		renderComp->GetSprite().setTextureRect(textureRect);
		renderComp->GetSprite().setOrigin(object->x + textureRect.width * 0.5f, object->y + textureRect.height *0.5f);
		renderComp->GetSprite().setPosition(object->x, object->y);

		if (initializeScale)
			renderComp->GetSprite().setScale(scale, scale);

		RenderManager::getInstance().Bind(gameObject->GetId(), 2, renderComp.get());

		if(object->type == "Player")
			EventBus::GetInstance().RegisterToEvent(EventIDs::PlayerDeath, renderComp.get());

		gameObject->AddComponent(move(renderComp));
	}
	if (initializeInputComponent)
	{
		auto inputComp = make_unique<PlayerGamepadControlComponent>(*gameObject, InputPlayerId, object->name);
		auto steeringComp = make_unique<SteeringComponent>(*gameObject, move(inputComp), object->name);
		EventBus::GetInstance().RegisterToEvent(EventIDs::CollisionStart, steeringComp.get());
		gameObject->AddComponent(move(steeringComp));

		auto healthComponent = make_unique<HealthComponent>(*gameObject, this->m_game->getWindow(), object->name, InputPlayerId + 1);
		auto health = healthComponent.get();
		m_healths.push_back(health);
		EventBus::GetInstance().RegisterToEvent(EventIDs::CollisionEnd, health);
		gameObject->AddComponent(move(healthComponent));

		auto scoreComponent = make_unique<ScoreComponent>(*gameObject, object->name);
		auto score = scoreComponent.get();
		m_gameObjectManager.AddPlayerScore(InputPlayerId, score);
		EventBus::GetInstance().RegisterToEvent(EventIDs::CollisionStart, score);
		EventBus::GetInstance().RegisterToEvent(EventIDs::PlayerDeath, score);
		gameObject->AddComponent(move(scoreComponent));

		auto boostComponent = make_unique<BoosterComponent>(*gameObject, object->name);
		auto boost = boostComponent.get();
		EventBus::GetInstance().RegisterToEvent(EventIDs::CollisionStart, boost);
		gameObject->AddComponent(move(boostComponent));
	}

	std::unique_ptr<Box2DRigidBodyComponent> body;
	if (mass > 0)
	{
		body = make_unique<Box2DRigidBodyComponent>(*gameObject, object->x + object->width / 2, object->y + object->height / 2, 0, 2.0f, gameObject->GetId(), b2_dynamicBody);
	}
	else
	{
		body = make_unique<Box2DRigidBodyComponent>(*gameObject, object->x + object->width / 2, object->y + object->height / 2, 0, 0, gameObject->GetId(), b2_staticBody);
	}
	m_rigidBodies.push_back(body.get());
	body->AddFixture(object->width*scale, object->height*scale, mass, groupIndex, restititution, 0.5f);
	gameObject->AddComponent(move(body));

	gameObject->Init();
	GameObjectManager::GetInstance().AddGameObject(unique_ptr<GameObject>(gameObject));
}

void MainState::BindInput()
{
	auto players = m_gameObjectManager.GetRegisteredPlayerIDs();

	for (auto it = players.begin(); it != players.end(); it++)
	{
		m_inputManager.Bind(StaticStrings::Pause, GamepadButtons::Options, *it);
		m_inputManager.Bind(StaticStrings::Accelerate, GamepadButtons::R2, *it);
		m_inputManager.Bind(StaticStrings::Break, GamepadButtons::L2, *it);
	}
}

void MainState::UnbindInput()
{
	m_inputManager.Unbind(StaticStrings::Accelerate);
	m_inputManager.Unbind(StaticStrings::Pause);
}

void MainState::VUpdate(float fDeltaTime)
{
	if (InputManager::getInstance().IsButtonPressed(StaticStrings::Pause))
	{
		m_gameStateManager->SetState(StaticStrings::StatePause);
		return;
	}

	int playerCounter = m_gameObjectManager.GetRegisteredPlayersCounter();

	for (auto it = m_healths.begin(); it != m_healths.end();)
	{
		auto health = *it;
		if (health->isDestroyed())
		{
			EventBus::GetInstance().Deregister(health);
			EventBus::GetInstance().Deregister(m_gameObjectManager.GetPlayerScore(health->GetPlayerID() - 1));
			auto gameObject = m_gameObjectManager.findObjectById(health->GetGameObjectID());
			m_deathCounter++;
			it = m_healths.erase(it);						
		}
		else
		{
			it++;
		}
	}

	if (m_deathCounter == playerCounter - 1)
	{
		m_gameStateManager->SetState(StaticStrings::StateGameOver);
		return;
	}

	Box2DPhysicsManager::GetInstance().Update(fDeltaTime);
	// update remaining game objects
	GameObjectManager::GetInstance().Update(fDeltaTime);
}

void MainState::VExit()
{
	EventBus::GetInstance().DeregisterEverything();
	m_healths.clear();

	ViewManager::GetInstance().Clear();

	GameObjectManager::GetInstance().Clear();
	m_rigidBodies.clear();

	UnbindInput();
	ResetCamera();
}

void MainState::SetCamera()
{
	m_menuCamera = m_game->getWindow().getView();

	auto ids = m_gameObjectManager.GetRegisteredPlayerIDs();
	for (auto id : ids)
	{
		ViewManager::GetInstance().RegisterBodyByID("Player" + to_string(id + 1));
	}
}

void MainState::ResetCamera()
{
	m_game->getWindow().setView(m_menuCamera);
}
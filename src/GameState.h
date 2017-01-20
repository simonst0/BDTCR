//////////////////////////////////////////////////////
// Game Development			- BrainDamaged Engine	//
// Simon Steiner			- 1510601034, fhs38598	//
// Katrin-Anna Zibuschka	- 1510601044, fhs38708	//
//////////////////////////////////////////////////////

#pragma once

#include <memory>

class GameStateManager;
class Game;

class GameState
{
public:
	typedef std::unique_ptr<GameState> Ptr;
	
	GameState(GameStateManager* gameStateManager, Game* game, std::string id)
		: m_gameStateManager(gameStateManager)
		, m_game(game)
		, m_id(id)
	{}
	virtual ~GameState() = default;

	/// called when game state is entered.
	virtual void VInit() {};

	/// called when game state is left.
	virtual void VExit() {};

	virtual void VDestroy() {};

	virtual void VUpdate(float delta) = 0;

	virtual std::string GetID() { return m_id; }
	
protected:
	virtual void BindInput() {};
	virtual void UnbindInput() {};
	
	GameStateManager* m_gameStateManager;
	Game* m_game;

	std::string m_id;
};

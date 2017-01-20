//////////////////////////////////////////////////////
// Game Development			- BrainDamaged Engine	//
// Simon Steiner			- 1510601034, fhs38598	//
// Katrin-Anna Zibuschka	- 1510601044, fhs38708	//
//////////////////////////////////////////////////////

#pragma once

#include <string>

#include "GameStateManager.h"

#include "SFML/Window.hpp"
#include "TGUI\TGUI.hpp"

class InputManager;

class Game
{
public:
	struct Config
	{
		sf::Vector2i resolution{ 1280, 768 };
		std::string windowName = StaticStrings::Title;
	};
	
	Config &getConfig() { return m_Config; }
	sf::RenderWindow &getWindow() { return m_window;  }

	void Run();
	
	static void QuitGame();

	static const int PLAYER_COUNT = 4;
	static const int MINIMUM_PLAYER_COUNT = 2;
	
	static tgui::Gui GUI;

private:

	bool init();
	void update();
	void draw();
	void shutdown();

	static bool m_shouldBeClosed;

	Config m_Config;
	
	sf::RenderWindow m_window;
	GameStateManager m_gameStateManager;
};

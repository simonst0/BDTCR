//////////////////////////////////////////////////////
// Game Development			- BrainDamaged Engine	//
// Simon Steiner			- 1510601034, fhs38598	//
// Katrin-Anna Zibuschka	- 1510601044, fhs38708	//
//////////////////////////////////////////////////////

#include "stdafx.h"

#include "InputManager.h"
#include "GameObjectManager.h"

using namespace sf;

InputManager& InputManager::getInstance()
{
	static InputManager instance;
	return instance;
}

void
InputManager::Process(const Event &event)
{
	switch (event.type)
	{
	case Event::KeyPressed:
		eventKeyboardFrame.keys[event.key.code] = true;
		break;
	case Event::KeyReleased:
		eventKeyboardFrame.keys[event.key.code] = false;
		break;
	case Event::JoystickButtonPressed:
		eventGamepadFrame.buttons[event.joystickButton.joystickId][event.joystickButton.button] = true;
		break;
	case Event::JoystickButtonReleased:
		eventGamepadFrame.buttons[event.joystickButton.joystickId][event.joystickButton.button] = false;
		break;
	case Event::JoystickConnected:
		eventGamepadFrame.gamepadConnected[event.joystickConnect.joystickId] = true;
		break;
	case Event::JoystickDisconnected:
		eventGamepadFrame.gamepadConnected[event.joystickConnect.joystickId] = false;
		break;
	}
}

void 
InputManager::Update()
{
	lastKeyboardFrame = currentKeyboardFrame;
	currentKeyboardFrame = eventKeyboardFrame;

	lastGamepadFrame = currentGamepadFrame;
	currentGamepadFrame = eventGamepadFrame;
}

#pragma region binding

void
InputManager::Bind(const std::string& action, GamepadButtons button, int gamepadID)
{
	if (gamepadID == -1)
	{
		for (int i = 0; i < Game::PLAYER_COUNT; i++)
		{
			gamepadActionBinding[i][action] = button;
		}
	}
	else 
	{
		//ASSERT_MSG(gamepadID < Game::PLAYER_COUNT && gamepadID >= 0, "player out of bounds");
		gamepadActionBinding[gamepadID][action] = button;
	}
}
//
//void
//InputManager::Bind(const std::string& action, int key, int playerID) {
//	ASSERT_MSG(playerID < Game::PLAYER_COUNT, "player out of bounds");
//	keyboardActionBinding[playerID][action] = key;
//}

void 
InputManager::Unbind(const std::string& action, int gamepadID)
{
	if (gamepadID == -1)
	{
		for (int i = 0; i < Game::PLAYER_COUNT; i++)
		{
			gamepadActionBinding[i].erase(action);
		}
	}
	else
	{
		//ASSERT_MSG(gamepadID < Game::PLAYER_COUNT, "player out of bounds");
		gamepadActionBinding[gamepadID].erase(action);
		keyboardActionBinding[gamepadID].erase(action);
	}
}

#pragma endregion

GamepadButtons 
InputManager::getButtonForAction(const std::string& action, int playerIdx)
{
	//ASSERT_MSG(playerIdx < Game::PLAYER_COUNT, "player out of bounds");

	auto it = gamepadActionBinding[playerIdx].find(action);
	if (it != gamepadActionBinding[playerIdx].end())
	{
		return it->second;
	}
	return GamepadButtons::Default;
}

int
InputManager::getKeyForAction(const std::string& action, int playerIdx)
{
	//ASSERT_MSG(playerIdx < Game::PLAYER_COUNT, "player out of bounds");

	auto it = keyboardActionBinding[playerIdx].find(action);
	if (it != keyboardActionBinding[playerIdx].end())
	{
		return it->second;
	}
	return -1;
}

#pragma region only keyboard keys

bool 
InputManager::IsKeyDown(const std::string& action, int player)
{
	return IsKeyDown(getKeyForAction(action, player));
}

bool 
InputManager::IsKeyUp(const std::string& action, int player)
{
	return IsKeyUp(getKeyForAction(action, player));
}

bool
InputManager::IsKeyPressed(const std::string& action, int player)
{
	return IsKeyPressed(getKeyForAction(action, player));
}

bool 
InputManager::IsKeyReleased(const std::string& action, int player)
{
	return IsKeyDown(getKeyForAction(action, player));
}

bool
InputManager::IsKeyDown(const std::string& action)
{
	for (int i = 0; i < Game::PLAYER_COUNT; i++)
	{
		if (IsKeyDown(action, i))
			return true;
	}

	return false;
}

bool
InputManager::IsKeyUp(const std::string& action)
{
	for (int i = 0; i < Game::PLAYER_COUNT; i++)
	{
		if (IsKeyUp(action, i))
			return true;
	}
	return false;
}

bool
InputManager::IsKeyPressed(const std::string& action)
{
	for (int i = 0; i < Game::PLAYER_COUNT; i++)
	{
		if (IsKeyPressed(action, i))
			return true;
	}
	return false;
}

bool
InputManager::IsKeyReleased(const std::string& action)
{
	for (int i = 0; i < Game::PLAYER_COUNT; i++)
	{
		if (IsKeyReleased(action, i))
			return true;
	}
	return false;
}

bool 
InputManager::IsKeyDown(int keyCode)
{
	if (keyCode < 0 || keyCode >= sf::Keyboard::KeyCount)
		return false;
	return currentKeyboardFrame.keys[keyCode];
}

bool 
InputManager::IsKeyUp(int keyCode)
{
	if (keyCode < 0 || keyCode >= sf::Keyboard::KeyCount)
		return false;
	return !currentKeyboardFrame.keys[keyCode];
}

bool 
InputManager::IsKeyPressed(int keyCode)
{
	if (keyCode < 0 || keyCode >= sf::Keyboard::KeyCount)
		return false;
	return currentKeyboardFrame.keys[keyCode] && !lastKeyboardFrame.keys[keyCode];
}

bool 
InputManager::IsKeyReleased(int keyCode)
{
	if (keyCode < 0 || keyCode >= sf::Keyboard::KeyCount)
		return false;
	return !currentKeyboardFrame.keys[keyCode] && lastKeyboardFrame.keys[keyCode];
}

#pragma endregion

#pragma region only gamepad buttons

bool
InputManager::IsButtonDown(const std::string& action, bool checkOnlyRegisteredPlayers) {
	std::vector<int> players;
	if (checkOnlyRegisteredPlayers)
	{
		players = GameObjectManager::GetInstance().GetRegisteredPlayerIDs();
	}
	else
	{
		players = { 0,1,2,3 };
	}

	for (auto it = players.begin(); it != players.end(); ++it)
	{
		if (IsButtonDown(action, *it))
			return true;
	}
	return false;
}

bool
InputManager::IsButtonUp(const std::string& action, bool checkOnlyRegisteredPlayers) {
	std::vector<int> players;
	if (checkOnlyRegisteredPlayers)
	{
		players = GameObjectManager::GetInstance().GetRegisteredPlayerIDs();
	}
	else
	{
		players = { 0,1,2,3 };
	}

	for (auto it = players.begin(); it != players.end(); ++it)
	{
		if (IsButtonUp(action, *it))
			return true;
	}
	return false;
}

bool
InputManager::IsButtonPressed(const std::string& action, bool checkOnlyRegisteredPlayers) {
	std::vector<int> players;
	if (checkOnlyRegisteredPlayers)
	{
		players = GameObjectManager::GetInstance().GetRegisteredPlayerIDs();
	}
	else
	{
		players = { 0,1,2,3 };
	}

	for (auto it = players.begin(); it != players.end(); ++it)
	{
		if (IsButtonPressed(action, *it))
			return true;
	}
	return false;
}

bool
InputManager::IsButtonReleased(const std::string& action, bool checkOnlyRegisteredPlayers) {
	std::vector<int> players;
	if (checkOnlyRegisteredPlayers)
	{
		players = GameObjectManager::GetInstance().GetRegisteredPlayerIDs();
	}
	else
	{
		players = { 0,1,2,3 };
	}

	for (auto it = players.begin(); it != players.end(); ++it)
	{
		if (IsButtonReleased(action, *it))
			return true;
	}
	return false;
}

bool
InputManager::IsButtonDown(const std::string& action, int gamepadID) {
	return IsButtonDown(getButtonForAction(action, gamepadID), gamepadID);
}

bool
InputManager::IsButtonUp(const std::string& action, int gamepadID) {
	return IsButtonUp(getButtonForAction(action, gamepadID), gamepadID);
}

bool
InputManager::IsButtonPressed(const std::string& action, int gamepadID) {
	return IsButtonPressed(getButtonForAction(action, gamepadID), gamepadID);
}

bool
InputManager::IsButtonReleased(const std::string& action, int gamepadID) {
	return IsButtonReleased(getButtonForAction(action, gamepadID), gamepadID);
}

bool
InputManager::IsButtonDown(GamepadButtons button, int gamepadID) 
{
	int buttonCode = (int)button;
	if (button == GamepadButtons::Default || buttonCode < 0 || buttonCode > sf::Joystick::ButtonCount)
		return false;

	return currentGamepadFrame.buttons[gamepadID][buttonCode];
}

bool 
InputManager::IsButtonUp(GamepadButtons button, int gamepadID)
{
	int buttonCode = (int)button;
	if (button == GamepadButtons::Default || buttonCode < 0 || buttonCode > sf::Joystick::ButtonCount)
		return false;

	return !currentGamepadFrame.buttons[gamepadID][buttonCode];
}

bool 
InputManager::IsButtonPressed(GamepadButtons button, int gamepadID)
{
	int buttonCode = (int)button;
	if (button == GamepadButtons::Default || buttonCode < 0 || buttonCode > sf::Joystick::ButtonCount)
		return false;

	return currentGamepadFrame.buttons[gamepadID][buttonCode] && !lastGamepadFrame.buttons[gamepadID][buttonCode];
}

bool 
InputManager::IsButtonReleased(GamepadButtons button, int gamepadID)
{
	int buttonCode = (int)button;
	if (button == GamepadButtons::Default || buttonCode < 0 || buttonCode > sf::Joystick::ButtonCount)
		return false;

	return !currentGamepadFrame.buttons[gamepadID][buttonCode] && lastGamepadFrame.buttons[gamepadID][buttonCode];
}

#pragma endregion

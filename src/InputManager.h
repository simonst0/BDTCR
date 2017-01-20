//////////////////////////////////////////////////////
// Game Development			- BrainDamaged Engine	//
// Simon Steiner			- 1510601034, fhs38598	//
// Katrin-Anna Zibuschka	- 1510601044, fhs38708	//
//////////////////////////////////////////////////////

#pragma once

#include <unordered_map>

#include "SFML/Window.hpp"
#include "Util.h"
#include "Game.h"

class InputManager
{
public:

	static InputManager& getInstance();
	
	/// Must be called at beginning of game update, before the update
	/// method. The events are
	/// classified and processed internally.
	/// \param event a single event coming from the sf polling.
	void Process(const sf::Event &event);

	/// Must be called after all events have been processed.
	void Update();

	/// Binds an action for gamepad
	void Bind(const std::string& action, GamepadButtons button, int gamepadID = -1);

	/// Unbinds an action.
	void Unbind(const std::string& action, int playerIdx = 0);

#pragma region only keyboard keys

	/// Returns true if the button for the given Action is currently down.
	bool IsKeyDown(const std::string& action, int playerIdx);

	/// Returns true if the button for the given Action is currently up.
	bool IsKeyUp(const std::string& action, int playerIdx);

	/// Returns true if the button for the given Action has been pressed.
	bool IsKeyPressed(const std::string& action, int playerIdx);

	/// Returns true if the button for the given Action has been released.
	bool IsKeyReleased(const std::string& action, int playerIdx);

	/// Returns true if the button for the given Action is currently down.
	bool IsKeyDown(const std::string& action);

	/// Returns true if the button for the given Action is currently up.
	bool IsKeyUp(const std::string& action);

	/// Returns true if the button for the given Action has been pressed.
	bool IsKeyPressed(const std::string& action);

	/// Returns true if the button for the given Action has been released.
	bool IsKeyReleased(const std::string& action);

	/// Returns true if the key is currently down.
	bool IsKeyDown(int key);

	/// Returns true if the key is currently up.
	bool IsKeyUp(int key);

	/// Returns true if the key has been pressed.
	bool IsKeyPressed(int key);

	/// Returns true if the key has been released.
	bool IsKeyReleased(int key);

#pragma endregion

#pragma region only gamepad buttons

	/// Returns true if the button is currently down.
	bool IsButtonDown(const std::string& action, bool checkOnlyRegisteredPlayers = true);

	/// Returns true if the button is currently up.
	bool IsButtonUp(const std::string& action, bool checkOnlyRegisteredPlayers = true);

	/// Returns true if the button has been pressed.
	bool IsButtonPressed(const std::string& action, bool checkOnlyRegisteredPlayers = true);

	/// Returns true if the button has been released.
	bool IsButtonReleased(const std::string& action, bool checkOnlyRegisteredPlayers = true);
	
	/// Returns true if the button is currently down.
	bool IsButtonDown(const std::string& action, int gamepadID);

	/// Returns true if the button is currently up.
	bool IsButtonUp(const std::string& action, int gamepadID);

	/// Returns true if the button has been pressed.
	bool IsButtonPressed(const std::string& action, int gamepadID);

	/// Returns true if the button has been released.
	bool IsButtonReleased(const std::string& action, int gamepadID);

	/// Returns true if the button is currently down.
	bool IsButtonDown(GamepadButtons button, int gamepadID);

	/// Returns true if the button is currently up.
	bool IsButtonUp(GamepadButtons button, int gamepadID);

	/// Returns true if the button has been pressed.
	bool IsButtonPressed(GamepadButtons button, int gamepadID);

	/// Returns true if the button has been released.
	bool IsButtonReleased(GamepadButtons button, int gamepadID);

#pragma endregion

	/// Returns the current position of the joystick
	sf::Vector2f GetJoystickPosition(int joystickID) {		
		return sf::Vector2f(sf::Joystick::getAxisPosition(joystickID, sf::Joystick::X), sf::Joystick::getAxisPosition(joystickID, sf::Joystick::Y));
	}

#pragma endregion

private:
	InputManager() = default;
	~InputManager() = default;

	InputManager(const InputManager& rhv) = delete;
	InputManager& operator= (const InputManager& rhv) = delete;

	int getKeyForAction(const std::string& action, int playerIdx);
	GamepadButtons getButtonForAction(const std::string& action, int playerIdx);

	struct KeyboardFrameData
	{
		bool keys[sf::Keyboard::KeyCount];
	};
	KeyboardFrameData lastKeyboardFrame {};
	KeyboardFrameData currentKeyboardFrame {};
	KeyboardFrameData eventKeyboardFrame {};

	struct GamepadFrameData
	{
		std::map<int, bool[sf::Joystick::ButtonCount]> buttons;
		bool gamepadConnected[Game::PLAYER_COUNT];
	};
	GamepadFrameData lastGamepadFrame{};
	GamepadFrameData currentGamepadFrame{};
	GamepadFrameData eventGamepadFrame{};

	/// maximum allowed players. Can be increaded if needed.
	std::unordered_map<std::string, GamepadButtons> gamepadActionBinding[Game::PLAYER_COUNT];
	std::unordered_map<std::string, int> keyboardActionBinding[Game::PLAYER_COUNT];
};
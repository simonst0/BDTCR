//////////////////////////////////////////////////////
// Game Development			- BrainDamaged Engine	//
// Simon Steiner			- 1510601034, fhs38598	//
// Katrin-Anna Zibuschka	- 1510601044, fhs38708	//
//////////////////////////////////////////////////////

#include "stdafx.h"

#include "Util.h"

using namespace sf;
using namespace std;

const string StaticStrings::Title = "Brain Damaged Toy Car Rally";

const string StaticStrings::StateMenu = "MenuState";
const string StaticStrings::StateRegistration = "RegistrationState";
const string StaticStrings::StateMain = "MainState";
const string StaticStrings::StateGameOver = "GameOverState";
const string StaticStrings::StateCredits = "CreditsState";
const string StaticStrings::StatePause = "PauseState";

const string StaticStrings::Register = "Register";
const string StaticStrings::Back = "Back";
const string StaticStrings::Start = "Start";
const string StaticStrings::Pause = "Pause";
const string StaticStrings::Select = "Select";
const string StaticStrings::Exit = "Exit";
const string StaticStrings::Accelerate = "Accelerate";
const string StaticStrings::Down = "Down";
const string StaticStrings::Up = "Up";
const string StaticStrings::Break = "Break";

const string StaticStrings::ResourcePath = "../assets/";
const string StaticStrings::ResourcePathBrains = "../assets/Sprites/Brains/";
const string StaticStrings::ResourcePathFonts = "../assets/Fonts/";
const string StaticStrings::ResourcePathGui = "../assets/GUI/";

const string StaticStrings::TitleFont = "Powerweld.ttf";
const string StaticStrings::TextFontThin = "kenvector_future_thin.ttf";
const string StaticStrings::TextFont = "kenvector_future.ttf";
const string StaticStrings::GuiTheme = "Theme.txt";
const string StaticStrings::GuiThemeBlue = "Theme_blue.txt";
const string StaticStrings::GuiThemeRed = "Theme_red.txt";
const string StaticStrings::GuiThemeYellow = "Theme_yellow.txt";
const string StaticStrings::GuiThemeGreen = "Theme_green.txt";
const string StaticStrings::GuiButton = "Button";
const string StaticStrings::GuiLabel = "Label";

const string StaticStrings::MenuStartGame = "Start Game";
const string StaticStrings::MenuQuitGame = "Quit Game";
const string StaticStrings::MenuCredits = "Credits";

const sf::Color ZombieColors::ZombieColorPlayer1 = sf::Color(47, 149, 208, 100);
const sf::Color ZombieColors::ZombieColorPlayer2 = sf::Color(232, 106, 23, 100);
const sf::Color ZombieColors::ZombieColorPlayer3 = sf::Color(57, 194, 114, 100);
const sf::Color ZombieColors::ZombieColorPlayer4 = sf::Color(255, 204, 0, 100);
sf::Color ZombieColors::Colors[4] = { ZombieColors::ZombieColorPlayer1, ZombieColors::ZombieColorPlayer2 ,ZombieColors::ZombieColorPlayer3, ZombieColors::ZombieColorPlayer4 };
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
const string StaticStrings::Honk = "Honk";

const string StaticStrings::ResourcePath = "../assets/";
const string StaticStrings::ResourcePathBrains = "../assets/Sprites/Brains/";
const string StaticStrings::ResourcePathFonts = "../assets/Fonts/";
const string StaticStrings::ResourcePathGui = "../assets/GUI/";

const string StaticStrings::LogoFH = StaticStrings::ResourcePath + "Sprites/Logos/fh_logo.png";
const string StaticStrings::LogoMMT = StaticStrings::ResourcePath + "Sprites/Logos/mmt_logo.png";

//const string StaticStrings::TitleFont = "Powerweld.ttf";
const string StaticStrings::TitleFont = "good times rg.ttf";
//const string StaticStrings::TextFontThin = "kenvector_future_thin.ttf";
//const string StaticStrings::TextFont = "kenvector_future.ttf";
const string StaticStrings::TextFont = "good times rg.ttf";
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

const string StaticStrings::AudioPath = "../assets/Audio/";
const string StaticStrings::MenuMusic = "menuMusic";
const string StaticStrings::MenuTick = "menuTick";
const string StaticStrings::MainMusic = "mainMusic";
const string StaticStrings::MainCrash = "mainCrash";
const string StaticStrings::MainHorn = "mainHorn";
const string StaticStrings::MainIgnition = "mainIgnition";
const string StaticStrings::MainBarrelBump = "mainBarrelBump";
const string StaticStrings::MainTireBump = "mainTireBump";
const string StaticStrings::MainCarHit = "mainCarHit";
const string StaticStrings::MainCountdown = "mainCountdown";
const string StaticStrings::MainMetallGrind = "mainMetallGrind";


const sf::Color PlayerColors::PlayerColor1 = sf::Color(47, 149, 208, 100);
const sf::Color PlayerColors::PlayerColor2 = sf::Color(232, 106, 23, 100);
const sf::Color PlayerColors::PlayerColor3 = sf::Color(57, 194, 114, 100);
const sf::Color PlayerColors::PlayerColor4 = sf::Color(255, 204, 0, 100);
sf::Color PlayerColors::Colors[4] = { PlayerColors::PlayerColor1, PlayerColors::PlayerColor2 ,PlayerColors::PlayerColor3, PlayerColors::PlayerColor4 };

const sf::Color PlayerColors::PlayerColorOpaque1 = sf::Color(47, 149, 208, 255);
const sf::Color PlayerColors::PlayerColorOpaque2 = sf::Color(232, 106, 23, 255);
const sf::Color PlayerColors::PlayerColorOpaque3 = sf::Color(57, 194, 114, 255);
const sf::Color PlayerColors::PlayerColorOpaque4 = sf::Color(255, 204, 0, 255);
sf::Color PlayerColors::ColorsOpaque[4] = { PlayerColors::PlayerColorOpaque1, PlayerColors::PlayerColorOpaque2 ,PlayerColors::PlayerColorOpaque3, PlayerColors::PlayerColorOpaque4 };
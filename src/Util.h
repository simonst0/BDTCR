//////////////////////////////////////////////////////
// Game Development			- BrainDamaged Engine	//
// Simon Steiner			- 1510601034, fhs38598	//
// Katrin-Anna Zibuschka	- 1510601044, fhs38708	//
//////////////////////////////////////////////////////

#pragma once

#include "SFML\System.hpp"

using namespace std;

namespace Util
{
	static float dot(const sf::Vector2f &vec1, const sf::Vector2f &vec2)
	{
		return vec1.x * vec2.x + vec1.y * vec2.y;
	}

	static void normalize(sf::Vector2f &vec)
	{
		float norm = sqrt(vec.x * vec.x + vec.y * vec.y);
		vec.x = vec.x / norm;
		vec.y = vec.y / norm;
	}

	static void eliminateNoise(sf::Vector2f &vec, int quantization) {
		vec.x = ((int)vec.x / quantization)*quantization;
		vec.y = ((int)vec.y / quantization)*quantization;
	}

	static bool StringContainsString(string referenceString, string wantedString)
	{
		return referenceString.find(wantedString) != string::npos;
	}


	static bool AllIDsContainString(vector<string> ids, string wantedString)
	{
		for (auto s : ids)
		{
			if (!StringContainsString(s, wantedString))
				return false;
		}
		return true;
	}

	static bool AnyIDContainsString(vector<string> ids, string wantedString)
	{
		for (auto s : ids)
		{
			if (StringContainsString(s, wantedString))
				return true;
		}
		return false;
	}

	static bool AnyIdIsTriggerObject(vector<string> ids) {
		return AnyIDContainsString(ids, "Goal")
			|| AnyIDContainsString(ids, "Checkpoint")
			|| AnyIDContainsString(ids, "Arrow");
	}
}

enum class GamepadButtons {
	Square = 0,
	X = 1,
	Circle = 2,
	Triangle = 3,
	L1 = 4,
	R1 = 5,
	L2 = 6,
	R2 = 7,
	Share = 8,
	Options = 9,
	L3 = 10,
	R3 = 11,
	PSButton = 12,
	Default = -1
};

enum class EventIDs {
	CollisionStart = 0,
	CollisionEnd = 1,
	PlayerDeath = 2
};

static class StaticStrings {
public: 
	static const string Title;

	static const string StateMenu;
	static const string StateRegistration;
	static const string StateMain;
	static const string StateGameOver;
	static const string StateCredits;
	static const string StatePause;

	static const string Register;
	static const string Back;
	static const string Start;
	static const string Pause;
	static const string Select;
	static const string Exit;
	static const string Accelerate;
	static const string Break;
	static const string Down;
	static const string Up;
	static const string Honk;

	static const string ResourcePath;
	static const string ResourcePathBrains;
	static const string ResourcePathFonts;
	static const string ResourcePathGui;

	static const string LogoFH;
	static const string LogoMMT;

	static const string TitleFont;
	static const string TextFont;
	//static const string TextFontThin;
	static const string GuiTheme;
	static const string GuiThemeBlue;
	static const string GuiThemeRed;
	static const string GuiThemeYellow;
	static const string GuiThemeGreen;
	static const string GuiButton;
	static const string GuiLabel;

	static const string MenuStartGame;
	static const string MenuQuitGame;
	static const string MenuCredits;

	static const string AudioPath;
	static const string MenuMusic;
	static const string MainMusic;
	static const string MainCrash;
	static const string MainHorn;
	static const string MainIgnition;
	static const string MainBarrelBump;
	static const string MainConeBump;
	static const string MainTireBump;
	static const string MenuTick;
	static const string MainCarHit;
	static const string MainCountdown;
	static const string MainMetallGrind;
};

static class ZombieColors {
public:
	static const sf::Color ZombieColorPlayer1;
	static const sf::Color ZombieColorPlayer2;
	static const sf::Color ZombieColorPlayer3;
	static const sf::Color ZombieColorPlayer4;

	static sf::Color Colors[4];
};


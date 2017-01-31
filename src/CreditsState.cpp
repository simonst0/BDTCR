//////////////////////////////////////////////////////
// Game Development			- BrainDamaged Engine	//
// Simon Steiner			- 1510601034, fhs38598	//
// Katrin-Anna Zibuschka	- 1510601044, fhs38708	//
//////////////////////////////////////////////////////

#include "stdafx.h"
#include "CreditsState.h"
#include "TextComponent.h"
#include "SpriteRenderComponent.h"
#include "RenderManager.h"

void CreditsState::VInit() {

	if (m_isInit)
		return;
	
	m_isInit = false;

	auto windowSize = m_game->getWindow().getView().getSize();

	sf::Vector2f titlePosition(windowSize.x / 2, 190);
	InitText("Title", StaticStrings::Title, StaticStrings::TitleFont, titlePosition, 90);

	float padding = 70;
	sf::Vector2f progTitlePosition(windowSize.x /2, windowSize.y / 3);
	InitText("Programming", "Programming", StaticStrings::TextFont, progTitlePosition, 55, sf::Color(30, 167, 225));
	InitText("Name1", "Simon Ignaz Steiner", StaticStrings::TextFont, sf::Vector2f(progTitlePosition.x, progTitlePosition.y + padding), 35);
	InitText("Name2", "Katrin-Anna Zibuschka", StaticStrings::TextFont, sf::Vector2f(progTitlePosition.x, progTitlePosition.y + 1.7f*padding), 35);

	sf::Vector2f soundTitlePosition(windowSize.x / 2, windowSize.y * 5 / 9);
	InitText("Sound", "Sound", StaticStrings::TextFont, soundTitlePosition, 55, sf::Color(30, 167, 225));
	InitText("SoundTitles", "\"Nonstop\" & \"Exit the Premises\"", StaticStrings::TextFont, sf::Vector2f(soundTitlePosition.x, soundTitlePosition.y + padding), 35);
	InitText("SoundGuy", "Kevin MacLeod (incompetech.com)", StaticStrings::TextFont, sf::Vector2f(soundTitlePosition.x, soundTitlePosition.y + 1.7f*padding), 25);
	InitText("Description", "Licensed under Creative Commons: By Attribution 3.0", StaticStrings::TextFont, sf::Vector2f(soundTitlePosition.x, soundTitlePosition.y + 2.1f*padding), 25);

	sf::Vector2f graphicsTitlePosition(windowSize.x / 2, windowSize.y * 3 / 4 + padding/2);
	InitText("Graphics", "Graphics", StaticStrings::TextFont, graphicsTitlePosition, 55, sf::Color(30, 167, 225));
	InitText("Kenney", "Kenney TM", StaticStrings::TextFont, sf::Vector2f(graphicsTitlePosition.x, graphicsTitlePosition.y + padding), 35);

	sf::Vector2f logoFHPosition(windowSize.x / 20, windowSize.y / 2);
	InitLogo("FH", StaticStrings::LogoFH, logoFHPosition, 1.3f);
	sf::Vector2f logoMMTPosition(windowSize.x * 4 / 5, windowSize.y * 3 / 7);
	InitLogo("MMT", StaticStrings::LogoMMT, logoMMTPosition, 0.25f);

	BindInput();
}

void CreditsState::InitText(std::string id, std::string text, std::string font, sf::Vector2f position, int size, sf::Color color) {

	auto textObject = make_unique<GameObject>(id);
	auto renderComp = make_unique<TextComponent>(*textObject,
		m_game->getWindow(),
		StaticStrings::ResourcePathFonts + font,
		text,
		position,
		size,
		color);

	RenderManager::getInstance().Bind(textObject->GetId(), 0, renderComp.get());
	textObject->AddComponent(move(renderComp));
	m_isInit |= textObject->Init();

	m_items.push_back(move(textObject));
}

void CreditsState::InitLogo(std::string id, std::string path, sf::Vector2f position, float scale) 
{
	auto object = make_unique<GameObject>(id);
	auto renderComp = make_unique<SpriteRenderComponent>(*object,
		m_game->getWindow(),
		path);

	renderComp->GetSprite().setPosition(position);
	renderComp->GetSprite().setScale(scale, scale);
	RenderManager::getInstance().Bind(object->GetId(), 0, renderComp.get());
	object->AddComponent(move(renderComp));
	m_isInit |= object->Init();

	m_items.push_back(move(object));
}

void CreditsState::VUpdate(float delta) {
	if(m_inputManager.IsButtonPressed(StaticStrings::Back, false))
		m_gameStateManager->SetState(StaticStrings::StateMenu);
}

void CreditsState::VExit() {
	for (auto it = m_items.begin(); it != m_items.end(); ++it) {
		RenderManager::getInstance().Unbind((*it)->GetId());
	}
	m_items.clear();

	UnbindInput();
	m_isInit = false;
}

void CreditsState::BindInput() {
	m_inputManager.Bind(StaticStrings::Back, GamepadButtons::Circle);
}

void CreditsState::UnbindInput() {
	m_inputManager.Unbind(StaticStrings::Back);
}
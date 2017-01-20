//////////////////////////////////////////////////////
// Game Development			- BrainDamaged Engine	//
// Simon Steiner			- 1510601034, fhs38598	//
// Katrin-Anna Zibuschka	- 1510601044, fhs38708	//
//////////////////////////////////////////////////////

#include "stdafx.h"
#include "CreditsState.h"
#include "TextComponent.h"
#include "RenderManager.h"

void CreditsState::VInit() {

	if (m_isInit)
		return;
	
	m_isInit = false;

	auto windowSize = m_game->getWindow().getView().getSize();

	sf::Vector2f titlePosition(windowSize.x / 2, 150);

	InitText("Title", StaticStrings::Title, StaticStrings::TitleFont, titlePosition, 45);

	float padding = 90;
	sf::Vector2f progTitlePosition(windowSize.x /2, windowSize.y / 3);
	InitText("Programming", "Programming", StaticStrings::TextFont, progTitlePosition, 55, sf::Color(30, 167, 225));
	InitText("Name1", "Simon Ignaz Steiner", StaticStrings::TextFontThin, sf::Vector2f(progTitlePosition.x, progTitlePosition.y + padding), 40);
	InitText("Name2", "Katrin-Anna Zibuschka", StaticStrings::TextFontThin, sf::Vector2f(progTitlePosition.x, progTitlePosition.y + 1.7f*padding), 40);
	
	sf::Vector2f graphicsTitlePosition(windowSize.x / 2, windowSize.y * 2 / 3 + padding/3);
	InitText("Graphics", "Graphics", StaticStrings::TextFont, graphicsTitlePosition, 55, sf::Color(30, 167, 225));
	InitText("Kenney", "Kenney", StaticStrings::TextFontThin, sf::Vector2f(graphicsTitlePosition.x, graphicsTitlePosition.y + padding), 40);

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

	m_texts.push_back(move(textObject));
}

void CreditsState::VUpdate(float delta) {
	if(m_inputManager.IsButtonPressed(StaticStrings::Back, false))
		m_gameStateManager->SetState(StaticStrings::StateMenu);
}

void CreditsState::VExit() {
	for (auto it = m_texts.begin(); it != m_texts.end(); ++it) {
		RenderManager::getInstance().Unbind((*it)->GetId());
	}
	m_texts.clear();

	UnbindInput();
	m_isInit = false;
}

void CreditsState::BindInput() {
	m_inputManager.Bind(StaticStrings::Back, GamepadButtons::Circle);
}

void CreditsState::UnbindInput() {
	m_inputManager.Unbind(StaticStrings::Back);
}
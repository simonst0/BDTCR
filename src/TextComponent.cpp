//////////////////////////////////////////////////////
// Game Development			- BrainDamaged Engine	//
// Simon Steiner			- 1510601034, fhs38598	//
// Katrin-Anna Zibuschka	- 1510601044, fhs38708	//
//////////////////////////////////////////////////////

#include "stdafx.h"
#include "TextComponent.h"
#include "IRenderComponent.h"

using namespace sf;

bool TextComponent::VInit() {
	if (!m_font.loadFromFile(m_fontFile))
	{
		err() << "Could not load font\n";
		return false;
	}

	m_text.setPosition(m_position);
	m_text.setString(m_textString);
	m_text.setFillColor(Color::White);
	m_text.setFont(m_font);
	m_text.setCharacterSize(m_characterSize);
	m_text.setOrigin(
		m_text.getLocalBounds().width * 0.5f,
		m_text.getLocalBounds().height * 0.5f);
	m_text.setFillColor(m_color);

	return true;
}

void TextComponent::VDraw() {
	m_renderWindow.draw(m_text);
}
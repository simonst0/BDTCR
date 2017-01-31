//////////////////////////////////////////////////////
// Game Development			- BrainDamaged Engine	//
// Simon Steiner			- 1510601034, fhs38598	//
// Katrin-Anna Zibuschka	- 1510601044, fhs38708	//
//////////////////////////////////////////////////////

#pragma once
#include "IRenderComponent.h"

class TextComponent : public IRenderComponent{
public:
	typedef std::unique_ptr<TextComponent> Ptr;

	TextComponent(GameObject &gameObject,
		sf::RenderWindow &renderWindow,
		const std::string &font,
		const std::string &text,
		const sf::Vector2f position,
		const int characterSize = 30,
		sf::Color color = sf::Color::White) : IRenderComponent(gameObject, renderWindow), 
									m_fontFile(font), 
									m_textString(text), 
									m_position(position), 
									m_characterSize(characterSize),
									m_color(color)
	{}

	virtual bool VInit() override;
	virtual void VUpdate(float fDeltaTime) override {}
	virtual void VDraw() override;

	void SetText(std::string &text) { m_textString = text; }
	
private:
	sf::Text m_text;
	sf::Font m_font;
	std::string m_textString;
	std::string m_fontFile;
	sf::Vector2f m_position;
	sf::Color m_color;
	int m_characterSize;
};
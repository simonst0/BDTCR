//////////////////////////////////////////////////////
// Game Development			- BrainDamaged Engine	//
// Simon Steiner			- 1510601034, fhs38598	//
// Katrin-Anna Zibuschka	- 1510601044, fhs38708	//
//////////////////////////////////////////////////////

#include "stdafx.h"
#include "TextureFactory.h"

TextureFactory& TextureFactory::GetInstance() {
	static TextureFactory instance;
	return instance;
}

sf::Texture* TextureFactory::GetTexture(const std::string filename) 
{
	return m_textures[filename].get();
}

void TextureFactory::LoadTexture(const std::string filename) 
{
	auto texture = std::make_unique<sf::Texture>();
	if(!texture->loadFromFile(StaticStrings::ResourcePath + filename))
		sf::err() << "Could not load texture " << filename << std::endl;

	m_textures[filename] = move(texture);
}
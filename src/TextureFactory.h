//////////////////////////////////////////////////////
// Game Development			- BrainDamaged Engine	//
// Simon Steiner			- 1510601034, fhs38598	//
// Katrin-Anna Zibuschka	- 1510601044, fhs38708	//
//////////////////////////////////////////////////////

#pragma once

#include <unordered_map>
#include "SFML\Graphics.hpp"

class TextureFactory {
public:
	static TextureFactory& GetInstance();

	sf::Texture* GetTexture(const std::string path);
	void LoadTexture(const std::string path);

private:
	TextureFactory() : m_textures(){}
	~TextureFactory() = default;

	TextureFactory(const TextureFactory& rhv) = delete;
	TextureFactory& operator= (const TextureFactory& rhv) = delete;

	std::map<std::string, std::unique_ptr<sf::Texture>> m_textures;
};
//////////////////////////////////////////////////////
// Game Development			- BrainDamaged Engine	//
// Simon Steiner			- 1510601034, fhs38598	//
// Katrin-Anna Zibuschka	- 1510601044, fhs38708	//
//////////////////////////////////////////////////////

#include "stdafx.h"

#include "GameObject.h"
#include "SpriteRenderComponent.h"
#include "Box2DPhysicsManager.h"
#include <iostream>

using namespace sf;

SpriteRenderComponent::SpriteRenderComponent(
	GameObject &gameObject, 
	RenderWindow &renderWindow,
	const std::string &textureFile)
: IRenderComponent(gameObject, renderWindow)
, m_textureFile(textureFile)
{
}

bool 
SpriteRenderComponent::VInit()
{
	Image image;
	if(!image.loadFromFile(m_textureFile))	
	{
		err() << "Could not load texture from " << m_textureFile << std::endl;
		return false;
	}
	m_texture.loadFromImage(image);
	m_sprite.setTexture(m_texture);

	if (m_nRepeat > 0)
	{
		m_sprite.setTextureRect(IntRect(0, 0, m_nRepeat * m_texture.getSize().x, m_nRepeat * m_texture.getSize().y));
		m_texture.setRepeated(true);
	}

	return true;
}

void
SpriteRenderComponent::VDraw()
{
	sf::Transform transform = Box2DPhysicsManager::GetInstance().GetTransformById(m_gameObject.GetId(), m_gameObject.GetTransform());
	m_renderWindow.draw(m_sprite, transform);
	m_renderWindow.draw(m_sprite, m_gameObject.GetTransform());
	
}

void SpriteRenderComponent::notify(IEvent* e) {
	try
	{
		if (e->ID == EventIDs::PlayerDeath)
		{
			PlayerDeathEvent* c = static_cast<PlayerDeathEvent*>(e);

			std::string gameObjectID = m_gameObject.GetId();
			if (c->m_gameObjectID == gameObjectID)
			{
				int id = gameObjectID.back() - '0' - 1;
				m_sprite.setColor(PlayerColors::Colors[id]);
			}
		}
	}
	catch (const std::bad_cast&)
	{
		return;
	}
}


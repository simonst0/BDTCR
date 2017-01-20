//////////////////////////////////////////////////////
// Game Development			- BrainDamaged Engine	//
// Simon Steiner			- 1510601034, fhs38598	//
// Katrin-Anna Zibuschka	- 1510601044, fhs38708	//
//////////////////////////////////////////////////////

#include "stdafx.h"
#include "LayerComponent.h"
#include "GameObject.h"
#include "Box2DPhysicsManager.h"

using namespace sf;
using namespace std;

bool LayerComponent::VInit(){
	return true;
}

void LayerComponent::VDraw(){
	auto center = m_renderWindow.getView().getCenter();
	//auto size = m_renderWindow.getView().getSize()*0.9f; // make the drawn area a bit smaller, to check if only sprites in viewport are drawn
	auto size = m_renderWindow.getView().getSize()*1.5f; // make the drawn area a bit bigger

	Rect<float> viewport(center.x - size.x / 2, center.y - size.y / 2, size.x, size.y);

	auto it = m_tiles.begin();

	while (it != m_tiles.end()) {

		if (viewport.contains(it->get()->getPosition()))
		{
			m_renderWindow.draw(*it->get(), Box2DPhysicsManager::GetInstance().GetTransformById(m_gameObject.GetId(), m_gameObject.GetTransform()));
		}
		

		it++;
	}
}

void LayerComponent::AddTile(Texture* texture, IntRect source, Vector2f position) {
	auto sprite = make_unique<Sprite>();
	sprite->setTexture(*texture);
	sprite->setTextureRect(source);
	sprite->setPosition(position.x, position.y);
	m_tiles.push_back(move(sprite));
}
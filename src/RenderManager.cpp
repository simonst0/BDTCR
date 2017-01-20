//////////////////////////////////////////////////////
// Game Development			- BrainDamaged Engine	//
// Simon Steiner			- 1510601034, fhs38598	//
// Katrin-Anna Zibuschka	- 1510601044, fhs38708	//
//////////////////////////////////////////////////////

#include "stdafx.h"
#include "RenderManager.h"

RenderManager& RenderManager::getInstance()
{
	static RenderManager instance;
	return instance;
}

RenderManager::RenderManager() :m_renderComponents() {}


void RenderManager::Bind(const std::string gameObjectID, const int depth, IRenderComponent* renderComponent) {
	m_renderComponents[depth][gameObjectID] = renderComponent;
}

void RenderManager::Unbind(const std::string gameObjectID) {

	for (auto& renderComponent : m_renderComponents) {
		renderComponent.second.erase(gameObjectID);
	}
}

void RenderManager::Unbind(const std::string gameObjectID, const int depth)
{
	auto renderComponents = m_renderComponents[depth];
	renderComponents.erase(gameObjectID);
}

void RenderManager::Render() {
	for (auto renderComponentMap : m_renderComponents) 
	{
		for (auto renderComponent : renderComponentMap.second)
		{
			renderComponent.second->VDraw();
		}
	}
}
//////////////////////////////////////////////////////
// Game Development			- BrainDamaged Engine	//
// Simon Steiner			- 1510601034, fhs38598	//
// Katrin-Anna Zibuschka	- 1510601044, fhs38708	//
//////////////////////////////////////////////////////

#pragma once

#include "IRenderComponent.h"

class RenderManager {
public:
	static RenderManager& getInstance();

	void Bind(const std::string gameObjectID, const int depth, IRenderComponent* renderComponent);
	void Unbind(const std::string gameObjectID); 
	void Unbind(const std::string gameObjectID, const int depth);

	void Render();

private:
	RenderManager();
	~RenderManager() = default;

	RenderManager(const RenderManager& rhv) = delete;
	RenderManager& operator= (const RenderManager& rhv) = delete;

	// depth, gameObjectID, renderComponent
	std::map<int, std::map<std::string, IRenderComponent*>> m_renderComponents;
};

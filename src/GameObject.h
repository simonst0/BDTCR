//////////////////////////////////////////////////////
// Game Development			- BrainDamaged Engine	//
// Simon Steiner			- 1510601034, fhs38598	//
// Katrin-Anna Zibuschka	- 1510601044, fhs38708	//
//////////////////////////////////////////////////////

#pragma once

#pragma once

#include <list>
#include <string>

#include <SFML/Graphics/Transform.hpp>

#include "IComponent.h"

class GameObject
{
public:
	typedef std::unique_ptr<GameObject> Ptr;

	GameObject(const std::string &id)
		: m_id(id)
	{}

	/// Add a component to the game object. Internally the game object
	/// identifies if it's a drawable component to call it's draw
	/// function or a general update component to call it's update
	/// function.
	/// \param component the component
	void AddComponent(IComponent::Ptr component);

	/// Initialize all added components
	bool Init();

	/// Could also be moved out of game object in the long run.
	void Update(float fDeltaTime);

	sf::Transform &GetTransform() { return m_transform; }
	void SetTransform(sf::Transform &transform) { m_transform = transform;  }

	bool IsMarkedForDelete() const { return m_wantToDie; }
	void MarkForDelete() { m_wantToDie = true; }

	std::string GetId() const { return m_id; }
	void SetId(const std::string id) { m_id = id; }

	std::list<IComponent::Ptr> m_componentList;

protected:
	sf::Transform m_transform{}; //< transformation shared by all components
	std::string m_id = "unnamed"; //< unique name of object, e.g., player
	bool m_wantToDie = false;
};
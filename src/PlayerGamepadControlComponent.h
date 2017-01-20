//////////////////////////////////////////////////////
// Game Development			- BrainDamaged Engine	//
// Simon Steiner			- 1510601034, fhs38598	//
// Katrin-Anna Zibuschka	- 1510601044, fhs38708	//
//////////////////////////////////////////////////////

#pragma once

#include "IControlComponent.h"
#include "IObserverPattern.h"

class PlayerGamepadControlComponent : public IControlComponent
{
public:
	typedef std::unique_ptr<PlayerGamepadControlComponent> Ptr;

	PlayerGamepadControlComponent(
		GameObject &gameObject,
		int gamepadIndex, std::string id);

	virtual bool VInit() override;
	virtual void VUpdate(float fDeltaTime) override;
	float getActAngle(float aK, float gK);
	float getActForceMultiplicator();

private:
	int m_gamepadIndex;
	std::string m_id;
	float m_90deg = 1.5708f;
	float m_timeR2isDown = 0;
	float m_actAngle;
};
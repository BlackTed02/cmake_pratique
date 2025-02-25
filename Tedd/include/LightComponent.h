#pragma once
#include "Component.h"
#include "LightsManager.h"

class LightComponent : public Component
{
private:
	Lights::Light *m_light;

public:
	LightComponent();
	~LightComponent();

	void Update() override;
	nlohmann::json ToJson() override;
	void FromJson(const nlohmann::json &_json) override;

	// Inherited via Component
#ifdef USING_EDITOR
	void EditorRender() override;
#endif
};
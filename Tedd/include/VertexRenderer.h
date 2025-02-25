#pragma once
#include "Component.h"

class VertexRenderer : public Component
{
	private:
		int m_points = 3;
		sf::Color m_color = sf::Color::White;
		std::vector<sf::Vertex> m_vertices;
	public:
		sf::VertexArray m_vertexArray;

		VertexRenderer();
		~VertexRenderer() = default;

#pragma region OVERRIDES
		// void Begin() override {};
		void Update() override; 

		nlohmann::json ToJson() override;
		void FromJson(const nlohmann::json& _json) override;
#ifdef USING_EDITOR
		void EditorRender() override;
#endif
#pragma endregion
};


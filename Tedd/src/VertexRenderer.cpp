#include "pch.h"
#include "VertexRenderer.h"
#include "Entity.h"

VertexRenderer::VertexRenderer()
{
	for (int i = 0; i < m_points * 3; i++)
	{
		m_vertices.push_back(sf::Vertex(sf::Vector2f(0.f, 0.f), m_color));
	}
}

void VertexRenderer::Update()
{
    sf::FloatRect bounds = p_owner->transform->GetWorldBounds();

    m_vertexArray.setPrimitiveType(sf::PrimitiveType::Triangles);
	m_vertexArray.resize(m_points * 3);

    sf::Vector2f position(bounds.left, bounds.top);
    sf::Vector2f size(bounds.width, bounds.height);

    float stepAngle = 2 * 3.14159 / m_points;

    for (size_t i = 0; i < m_points; i++)
    {
        float angle = i * stepAngle + Deg2Rad(p_owner->transform->GetWorldAngle());
        float nextAngle = (i + 1) % m_points * stepAngle + Deg2Rad(p_owner->transform->GetWorldAngle());

        sf::Vertex vertex;
        vertex.color = m_color;

		// Center
        vertex.position = position;
		m_vertexArray[i * 3 + 0] = vertex;

		// First point
        vertex.position = sf::Vector2f(position.x + size.x * std::cos(angle), position.y + size.y * std::sin(angle));
        m_vertexArray[i * 3 + 1] = vertex;

		// Second point
        vertex.position = sf::Vector2f(position.x + size.x * std::cos(nextAngle), position.y + size.y * std::sin(nextAngle));
        m_vertexArray[i * 3 + 2] = vertex;
    }
}

nlohmann::json VertexRenderer::ToJson()
{
    nlohmann::json json;

    json["color"] = { m_color.r, m_color.g, m_color.b, m_color.a };

    return json;
}

void VertexRenderer::FromJson(const nlohmann::json& _json)
{
    if (_json.contains("color"))
    {
        m_color.r = _json["color"][0];
        m_color.g = _json["color"][1];
        m_color.b = _json["color"][2];
        m_color.a = _json["color"][3];
    }
}

#ifdef USING_EDITOR
void VertexRenderer::EditorRender()
{
    if (ImGui::CollapsingHeader("Render", ImGuiTreeNodeFlags_DefaultOpen))
    {
        sf::Color color = m_color;

        float colorImGui[4] =
        {
             color.r / 255.0f,
             color.g / 255.0f,
             color.b / 255.0f,
             color.a / 255.0f
        };

        if (ImGui::ColorPicker4("Color", colorImGui))
        {
            color.r = static_cast<sf::Uint8>(colorImGui[0] * 255);
            color.g = static_cast<sf::Uint8>(colorImGui[1] * 255);
            color.b = static_cast<sf::Uint8>(colorImGui[2] * 255);
            color.a = static_cast<sf::Uint8>(colorImGui[3] * 255);

			m_color = color;
        }

		sf::FloatRect bounds = p_owner->transform->GetBounds();
        ImGui::Text("Position :");
        ImGui::PushItemWidth(100);
        ImGui::Text("Left : ");
        ImGui::SameLine();
        ImGui::DragFloat("##left", &bounds.left, 1.f, 0, LLONG_MAX);
        ImGui::SameLine();
        ImGui::Text("Top : ");
        ImGui::SameLine();
        ImGui::DragFloat("##top", &bounds.top, 1.f, 0, LLONG_MAX);
        ImGui::Dummy(ImVec2(0.f, 1.f));
        ImGui::Text("Size :");
        ImGui::Text("Width : ");
        ImGui::SameLine();
        ImGui::DragFloat("##witdth", &bounds.width, 1.f, 0, LLONG_MAX);
        ImGui::SameLine();
        ImGui::Text("Height : ");
        ImGui::SameLine();
        ImGui::DragFloat("##height", &bounds.height, 1.f, 0, LLONG_MAX);
		ImGui::DragInt("Points", &m_points, 0.1f, 3, 10000);

		p_owner->transform->SetBounds(bounds);
    }
}
#endif
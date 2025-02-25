#include "pch.h"
#include "TransformComponent.h"
#include "Entity.h"
TransformComponent::TransformComponent(sf::Vector2f _pos, sf::Vector2f _size, float _angle) : m_position(_pos), m_scale(_size), m_angle(_angle)
{}

TransformComponent::TransformComponent(Entity * _parent, sf::Vector2f _pos, sf::Vector2f _size, float _angle) : m_position(_pos), m_scale(_size), m_angle(_angle), m_parent(_parent)
{}

void TransformComponent::Update()
{}

void TransformComponent::Move(sf::Vector2f _pos)
{
	m_position.x += _pos.x;
	m_position.y += _pos.y;
}

void TransformComponent::Move(float _x, float _y)
{
	m_position.x += _x;
	m_position.y += _y;
}

void TransformComponent::Rotation(float _angle)
{
	m_angle += _angle;
}

sf::Vector2f TransformComponent::GetLocalPosition()
{
    return m_position;
}

sf::Vector2f TransformComponent::GetLocalSize()
{
	return m_scale;
}

float TransformComponent::GetLocalAngle()
{
	return m_angle;
}

sf::Vector2f TransformComponent::GetWorldPosition()
{
    if (m_parent != nullptr)
	{
        //m_parent->GetParent()->transform
		sf::Vector2f tempPos = m_position;
        float angle = Deg2Rad(m_parent->transform->GetWorldAngle());
        float rotatedX = tempPos.x * std::cos(angle) - tempPos.y * std::sin(angle);
        float rotatedY = tempPos.x * std::sin(angle) + tempPos.y * std::cos(angle);
        sf::Vector2f worldPos = m_parent->transform->GetWorldPosition() + sf::Vector2f(rotatedX, rotatedY);
        return worldPos;
	}
	return m_position;
}

sf::Vector2f TransformComponent::GetWorldSize()
{
    if (m_parent != nullptr)
	{
		sf::Vector2f tempScale = m_scale;
		return sf::Vector2f(tempScale.x + m_parent->transform->GetWorldSize().x, tempScale.y + m_parent->transform->GetWorldSize().y);
	}
	return m_scale;
}

float TransformComponent::GetWorldAngle()
{
	if (m_parent != nullptr)
	{
		float tempAngle = m_angle;
		return tempAngle + m_parent->transform->GetWorldAngle();
	}
	return m_angle;
}

sf::FloatRect TransformComponent::GetWorldBounds()
{
    return sf::FloatRect(GetWorldPosition(), GetWorldSize());
}


#ifdef USING_EDITOR
void TransformComponent::EditorRender()
{
    if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
    {
        sf::Vector2f pos = this->GetLocalPosition();
        sf::Vector2f scale = this->GetLocalSize();
        float rotation = this->GetLocalAngle();

        sf::Vector2f savePos = pos;
        sf::Vector2f saveScale = scale;
        float saveRotation = rotation;
        /// UI
        ImGui::Text("Position :");
        ImGui::PushItemWidth(100);
        ImGui::Text("X : ");
        ImGui::SameLine();
        ImGui::DragFloat("##Xpos", &pos.x, 1.f, 0, WINDOW_WIDTH, "%.1f");
        ImGui::SameLine();
        ImGui::Text("Y : ");
        ImGui::SameLine();
        ImGui::DragFloat("##Ypos", &pos.y, 1.f, 0, WINDOW_HEIGHT, "%.1f");
        ImGui::Dummy(ImVec2(0.f, 1.f));
        ImGui::Text("Scale :");
        ImGui::Text("X : ");
        ImGui::SameLine();
        ImGui::DragFloat("##Xscale", &scale.x, 1.f, 0, WINDOW_WIDTH, "%.1f");
        ImGui::SameLine();
        ImGui::Text("Y : ");
        ImGui::SameLine();
        ImGui::DragFloat("##Yscale", &scale.y, 1.f, 0, WINDOW_HEIGHT, "%.1f");
        ImGui::Dummy(ImVec2(0.f, 1.f));
        ImGui::Text("Rotation :");
        ImGui::DragFloat("##Rotation", &rotation, 1.f, -361.f, 361.f, "%.1f");
        if (rotation > 360.f)
        {
            rotation = -360.f;
        }
		else if (rotation < -360.f)
		{
			rotation = 360.f;
		}
        this->SetPosition(pos);
        this->SetSize(scale);
        this->SetAngle(rotation);
    }
}
#endif

nlohmann::json TransformComponent::ToJson()
{
    nlohmann::json json;

    json["position"] = { m_position.x, m_position.y };
    json["scale"] = { m_scale.x, m_scale.y };
    json["angle"] = m_angle;

    return json;
}

void TransformComponent::FromJson(const nlohmann::json& _json)
{
    if (_json.contains("position"))
    {
        m_position = sf::Vector2f(_json["position"][0], _json["position"][1]);
    }
    if (_json.contains("scale"))
    {
        m_scale = sf::Vector2f(_json["scale"][0], _json["scale"][1]);
    }
    if (_json.contains("angle"))
    {
        m_angle = _json["angle"];
    }
}

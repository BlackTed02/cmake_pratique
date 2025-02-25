#include "pch.h"
#include "LightComponent.h"
#include "TransformComponent.h"
#include "Entity.h"

LightComponent::LightComponent()
{
    this->m_light = Lights::Create();
}

LightComponent::~LightComponent()
{
    Lights::Destroy(this->m_light);
}

void LightComponent::Update()
{
    this->m_light->SetPosition(this->p_owner->transform->GetWorldPosition());
}

nlohmann::json LightComponent::ToJson()
{
    nlohmann::json json;

    sf::Color clr = this->m_light->GetColor();
    json["color"] = { clr.r, clr.g, clr.b, clr.a };
    json["radius"] = this->m_light->GetRadius();
    json["opacity"] = this->m_light->GetOpacity();
    json["attenuation"] = this->m_light->GetAttenuation();

    return json;
}

void LightComponent::FromJson(const nlohmann::json &_json)
{
    sf::Color clr;
    clr.r = _json["color"][0];
    clr.g = _json["color"][1];
    clr.b = _json["color"][2];
    clr.a = _json["color"][3];

    this->m_light->SetPosition(this->p_owner->transform->GetWorldPosition());
    this->m_light->SetColor(clr);
    this->m_light->SetRadius(_json["radius"]);
    this->m_light->SetOpacity(_json["opacity"]);
    this->m_light->SetAttenuation(_json["attenuation"]);
}

#ifdef USING_EDITOR
void LightComponent::EditorRender()
{
    if (ImGui::CollapsingHeader("Light Source", ImGuiTreeNodeFlags_DefaultOpen)) 
    {
        sf::Color clr = this->m_light->GetColor();
        float rds = this->m_light->GetRadius();
        float opacity = this->m_light->GetOpacity();
        float attenuation = this->m_light->GetAttenuation();

        float colorImGui[4] =
        {
             clr.r / 255.0f,
             clr.g / 255.0f,
             clr.b / 255.0f,
             clr.a / 255.0f
        };

        if (ImGui::ColorPicker4("Color", colorImGui)) {
            clr.r = static_cast<sf::Uint8>(colorImGui[0] * 255);
            clr.g = static_cast<sf::Uint8>(colorImGui[1] * 255);
            clr.b = static_cast<sf::Uint8>(colorImGui[2] * 255);
            clr.a = static_cast<sf::Uint8>(colorImGui[3] * 255);

            this->m_light->SetColor(clr);
        }

        /// UI
        ImGui::Text("Radius :");
        ImGui::PushItemWidth(100);
        ImGui::SameLine();
        ImGui::DragFloat("##Radius", &rds, 1.f, 0.f, INFINITY, "%.1f");
        ImGui::Dummy(ImVec2(0.f, 1.f));
        ImGui::Text("Opacity :");
        ImGui::PushItemWidth(100);
        ImGui::SameLine();
        ImGui::DragFloat("##Opacity", &opacity, 0.01f, 0.f, 1.f, "%.2f");
        ImGui::Dummy(ImVec2(0.f, 1.f));
        ImGui::Text("Attenuation :");
        ImGui::PushItemWidth(100);
        ImGui::SameLine();
        ImGui::DragFloat("##Attenuation", &attenuation, 0.01f, 0.f, 1.f, "%.2f");
        ImGui::Dummy(ImVec2(0.f, 1.f));

        this->m_light->SetPosition(this->p_owner->transform->GetWorldPosition());
        this->m_light->SetRadius(rds);
        this->m_light->SetOpacity(opacity);
        this->m_light->SetAttenuation(attenuation);
    }
}
#endif
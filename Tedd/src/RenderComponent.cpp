#include "pch.h"
#include "RenderComponent.h"
#include "tinyfiledialogs.h"

#ifdef USING_EDITOR
void RenderComponent::EditorRender()
{
    if (ImGui::CollapsingHeader("Render", ImGuiTreeNodeFlags_DefaultOpen))
    {
        sf::Color color = this->GetColor();

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

            this->SetColor(color);
        }
        if (ImGui::Button("Select texture"))
        {
            char const* lFilterPatterns[2] = { "*.png", "*.jpg" };
            std::string path = ConvertToString(
                tinyfd_openFileDialog(
                    "Select a PNG file",
                    "..\\Resources\\",
                    2,
                    lFilterPatterns,
                    NULL,
                    0
                ));
            this->SetTextureName(GetLastElement(path));

            if (this->GetTextureName() != "")
            {
                this->SetTexture(this->GetTextureName());
            }
        }

        sf::IntRect rect = this->GetTextureRect();

        ImGui::Text("Position :");
        ImGui::PushItemWidth(100);
        ImGui::Text("Left : ");
        ImGui::SameLine();
        ImGui::DragInt("##left", &rect.left, 1.f, 0, LLONG_MAX);
        ImGui::SameLine();
        ImGui::Text("Top : ");
        ImGui::SameLine();
        ImGui::DragInt("##top", &rect.top, 1.f, 0, LLONG_MAX);
        ImGui::Dummy(ImVec2(0.f, 1.f));
        ImGui::Text("Size :");
        ImGui::Text("Width : ");
        ImGui::SameLine();
        ImGui::DragInt("##witdth", &rect.width, 1.f, 0, LLONG_MAX);
        ImGui::SameLine();
        ImGui::Text("Height : ");
        ImGui::SameLine();
        ImGui::DragInt("##height", &rect.height, 1.f, 0, LLONG_MAX);

        if (rect != this->GetTextureRect())
        {
            this->SetTextureRect(rect);
        }
    }
}

#endif

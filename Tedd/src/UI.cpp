#include "pch.h"
#include "UI.h"
#include "tinyfiledialogs.h"
#include "ColliderComponent.h"
#include "ComponentFactory.h"

#ifdef  USING_EDITOR
std::string UI::m_selectedWindowID = "NONE";
Entity* UI::m_selectedEntity = nullptr;
ImGuiWindowFlags UI::m_flags = ImGuiWindowFlags_None;
UI ui;

void UI::Update(Window& _window, Scene& _scene)
{
    if (0)
    {
		m_flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    }
    else
    {
        m_flags = ImGuiWindowFlags_None;
    }

	/// Tool bar
	ToolBar(_scene);
    /// Content Browser
	ContentBrowser(_scene);
    /// Viewport of the scene
	ViewPort(_window, _scene);
	/// Hierachy and Inspector
	Hierarchy(_scene);
	/// Right click menu    
	RightClickPopUp(_scene);
    /// Console
    Console(_scene);
}

void UI::RightClickPopUp(Scene& _scene)
{
    /// Right click menu
    ImVec2 popupPos;
    if (ImGui::IsMouseClicked(ImGuiMouseButton_Right) 
        && (m_selectedWindowID == "Hierarchy"
        || m_selectedWindowID == "Inspector"))
    {
        popupPos = ImGui::GetMousePos();
        ImGui::OpenPopup("RightClickPopUp");
    }
   
    if (ImGui::BeginPopup("RightClickPopUp"))
    {
        if (m_selectedWindowID == "Hierarchy")
        {
            if (ImGui::Selectable("Add Entity"))
            {
                _scene.CreateEntity();
            }
        }
        else if (m_selectedWindowID == "Inspector")
        {
            ImGui::BulletText("Components : ");
            for (auto [comp, name] : GlobalComponentFactory.GetRegisteredComponents())
            {
                if (name != "TransformComponent")
                {
                    if (ImGui::Selectable(name.c_str()))
                    {
                        m_selectedEntity->AddComponent(comp);
                    }
                }
            }
        }
        ImGui::EndPopup();
    }
}

void UI::ToolBar(Scene& _scene)
{
    /// Tool bar
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("Fichier"))
        {
            if (ImGui::MenuItem("Nouveau", "Ctrl+N"))
            {
            }
            if (ImGui::MenuItem("Ouvrir", "Ctrl+O"))
            {
				_scene.Load();
            }
            if (ImGui::MenuItem("Sauvegarder", "Ctrl+S"))
            {
				_scene.Save();
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Edition"))
        {
            if (ImGui::MenuItem("Annuler", "Ctrl+Z"))
            {
            }
            if (ImGui::MenuItem("Refaire", "Ctrl+Y"))
            {
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Affichage"))
        {
            static bool show_grid = true;
            ImGui::MenuItem("Afficher la grille", NULL, &show_grid);
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }

	/// Shortcuts
	static float timer = 0.f;
    timer += GetDeltaTime();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && timer >= 0.2f)
    {
        /// FILE
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::N))
        {
            /// New
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
        {
			/// Open
            _scene.Load();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
			/// Save
            _scene.Save();
        }
		/// EDIT
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
        {
			/// Undo
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
        {
			/// Redo
        }
        timer = 0.f;
    }
}

void UI::ViewPort(Window& _window, Scene& _scene)
{
    ImGui::Begin("ViewPort", nullptr, m_flags);
    if (ImGui::IsWindowHovered())
    {
        m_selectedWindowID = "ViewPort";
    }
    const sf::Texture& texture = _window.GetRenderTexture().getTexture();
    ImVec2 sceneSize = ImVec2((float)texture.getSize().x, (float)texture.getSize().y);
    ImGui::Image((void*)texture.getNativeHandle(),
        sceneSize, // Taille de l'image
        ImVec2(0, 1),      // UV Haut
        ImVec2(1, 0));     // UV Bas
    ImGui::End();
}

void UI::Hierarchy(Scene& _scene)
{
    /// Variables used in this function
    static int selectedEntity = -1; // -1 means no entity is selected
    int i = 0; /// This counter is used to identify the entity in the hierarchy window

    ImGui::Begin("Hierarchy", nullptr, m_flags);
    if (ImGui::IsWindowHovered())
    {
        m_selectedWindowID = "Hierarchy";
    }

    if (ImGui::BeginTable("EntityTable", 2, ImGuiTableFlags_RowBg))
    {
        ImGui::TableSetupColumn("Entity Name", ImGuiTableColumnFlags_WidthStretch);
        ImGui::TableSetupColumn("Options", ImGuiTableColumnFlags_WidthFixed, 15.0f);

        for (Entity* n : _scene.GetEntities())
        {
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            /// Use ImGui to create a tree view of the entities
            ImGui::PushID(i);
            if (ImGui::Selectable(n->GetName().c_str()))
            {
                if (selectedEntity == i)
                {
                    selectedEntity = -1;
                }
                else
                {
                    selectedEntity = i;
                }
            }

            ImGui::TableNextColumn();
            if (ImGui::Button((":##btn" + std::to_string(i)).c_str())) 
            {
                ImGui::OpenPopup(("EntityContextMenu##" + std::to_string(i)).c_str());
            }

            bool canDestroy = false;
            if (ImGui::BeginPopup(("EntityContextMenu##" + std::to_string(i)).c_str())) 
            {
                ImGui::Text("%s", n->GetName().c_str());
                if (ImGui::MenuItem("Delete"))
                {
                    canDestroy = true;
                    ImGui::CloseCurrentPopup();
                }
                if (ImGui::Selectable("ColliderComponent"))
                {
                    n->AddComponent<ColliderComponent>(n);
                }
                ImGui::EndPopup();
            }

            if (canDestroy)
            {
                _scene.DestroyEntity(n);
                selectedEntity = -1;
                ImGui::PopID();
                continue;
            }

            /// Show the inspector of the selected entity
            Inspector(_scene, n, selectedEntity, i);
            ImGui::PopID();
            i++;
        }
        ImGui::EndTable();
    }
    ImGui::End();
}

void UI::Inspector(Scene& _scene, Entity* _entity, int _selectedEntityID, int _currentIndex)
{
    ImGui::Begin("Inspector", nullptr, m_flags);
    if (ImGui::IsWindowHovered())
    {
        m_selectedWindowID = "Inspector";
    }
    if (_selectedEntityID == _currentIndex)
    {
		m_selectedEntity = _entity;
        char name[50];
        strcpy_s(name, sizeof(name), m_selectedEntity->GetName().c_str());

        ImGui::Text("Name : ");
        ImGui::SameLine();
        if (ImGui::InputText("##name", name, 50, ImGuiInputTextFlags_EnterReturnsTrue))
        {
            m_selectedEntity->SetName(name);
        }
        int j = 0;
        for (auto comp : m_selectedEntity->GetComponents<Component>())
        {
            bool isDeleted = false;
            ImGui::PushID(j);
            if (ImGui::Button(":##btn"))
            {
                ImGui::OpenPopup(("EntityContextMenu##" + std::to_string(j)).c_str());
            }

			if (ImGui::BeginPopup(("EntityContextMenu##" + std::to_string(j)).c_str()))
            {
                if (dynamic_cast<TransformComponent*>(comp) == nullptr)
                {
                    if (ImGui::MenuItem("Delete"))
                    {
                        isDeleted = true;
                        ImGui::CloseCurrentPopup();
                    }
                }
                else
                {
					ImGui::CloseCurrentPopup();
                }
                ImGui::EndPopup();
            }

            ImGui::SameLine();
            if (isDeleted)
            {
                if (m_selectedEntity->HasComponent(typeid(*comp)))
                {
                    m_selectedEntity->RemoveComponent(typeid(*comp));
                    isDeleted = true;
                }
            }
            else
            {
                comp->EditorRender();
            }
            ImGui::PopID();
            ImGui::Separator();
            ImGui::Dummy(ImVec2(0.f, 10.f));
            j++;
        }
        if (ImGui::Button("Add child Entity"))
        {
            _scene.CreateEntityWithParent(_entity, sf::Vector2f(500.f, 500.f), sf::Vector2f(300.f, 300.f), 0);
        }
    }
    ImGui::End();
}

void UI::ContentBrowser(Scene& _scene)
{
    ImGui::Begin("Content Browser", nullptr, m_flags);
    if (ImGui::IsWindowHovered())
    {
        m_selectedWindowID = "Content Browser";
    }
    ImGui::End();
}

void UI::Console(Scene& _scene)
{
    ImGui::Begin("Console", nullptr, m_flags);
    if (ImGui::IsWindowHovered())
    {
        m_selectedWindowID = "Console";
    }
    ImGui::End();
}
#endif
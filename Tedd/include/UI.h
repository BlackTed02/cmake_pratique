 #pragma once
#include "tools.h"
#include "Entity.h"
#include "Scene.h"
#include "ComponentFactory.h"
#include "Window.h"

#ifdef USING_EDITOR
class UI
{
	private:
		static std::string m_selectedWindowID;
		static Entity* m_selectedEntity;
		static ImGuiWindowFlags m_flags;
	public:
		UI() = default;
		~UI() = default;

		static void Update(Window& _window, Scene& _scene);
		static void ToolBar(Scene& _scene);
		static void ViewPort(Window& _window, Scene& _scene);
		static void Hierarchy(Scene& _scene);
		static void Inspector(Scene& _scene, Entity* _entity, int _selectedEntityID, int _currentIndex);
		static void ContentBrowser(Scene& _scene);
		static void RightClickPopUp(Scene& _scene);
		static void Console(Scene& _scene);
};
#endif
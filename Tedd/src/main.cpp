#include "pch.h"
#include "tools.h"
#include "GameScene.h"
#include "UI.h"
#include "ComponentFactory.h"
#include "LightsManager.h"
#include "Window.h"

int main()
{
    InitTools();

    Window window("T.E.DD", sf::Vector2i(WINDOW_WIDTH, WINDOW_HEIGHT));
	/// Register all components
	GlobalComponentFactory.RegisterComponents();
    /// A DEPLACER JE PENSE
    Lights::Init();

#ifdef USING_EDITOR
    ImGui::SFML::Init(window.GetWindow());
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
#endif

	/// Create a new scene
    GameScene* mainScene = new GameScene();

	/// Load the json file for the scene
    mainScene->Load(); 

	/// Main loop
    while (window.IsOpen())
    {
        RestartClock();
        window.Update();

#ifdef USING_EDITOR
        ImGui::SFML::Update(window.GetWindow(), GetTime());
		/// DockSpace using MainViewport
        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
#endif
		/// Update the scene
        mainScene->Update();
        window.BeginDraw();
        mainScene->Render(window.GetRenderTexture());

        /// Draw 
        Lights::Render(window.GetRenderTexture());

#ifdef USING_EDITOR
        /// Update the engine UI
        UI::Update(window, *mainScene);
        /// Render the scene
        ImGui::SFML::Render(window.GetWindow());
#endif
        window.Display();
        window.EndDraw();
    }
#ifdef USING_EDITOR
    ImGui::SFML::Shutdown();
#endif
    return 0;
}

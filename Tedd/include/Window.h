#pragma once
#include "tools.h"
#include "View.h"

class Window
{
	private:
		sf::RenderWindow m_renderWindow;
		sf::RenderTexture m_renderTexture;
		std::optional<View*> m_view;
		sf::Sprite m_sprite;
		std::string m_title;
		sf::Event m_event;
		sf::Vector2i m_size;
		sf::Vector2i m_mousePosition;
		bool m_isFullscreen;
		bool m_isVSync;
		bool m_isFocused;
		bool m_isAntialiasing;
	public:
		Window(std::string _title, sf::Vector2i _size, bool _isFullscreen = false, bool _isVSync = false, bool _isAntialiasing = false);
		~Window() = default;

		void Draw(sf::Drawable& _drawable);
		void Draw(sf::Drawable& _drawable, sf::RenderStates _states);
		void Draw(sf::Drawable& _drawable, sf::Shader& _shader);
		void Draw(sf::Drawable& _drawable, sf::Texture& _texture);

		void BeginDraw();
		void Update();
		void Display();
		void EndDraw();
		void Close();

		void CreateRenderWindow();
		inline bool IsOpen() { return m_renderWindow.isOpen(); }
		inline bool IsFocused() { return m_isFocused; }
		inline bool IsFullscreen() { return m_isFullscreen; }
		inline bool IsVSync() { return m_isVSync; }
		inline bool IsAntialiasing() { return m_isAntialiasing; }
		inline bool HasView() { return m_view.has_value(); }
	
		inline View* GetView() { return m_view.value(); }
		inline void SetView(View* _view) { m_view = _view; }
		inline void ResetView() { m_view.reset(); }
		
		sf::Vector2f GetMousePosRelativeToWindow();
		inline sf::Vector2i GetSize() { return m_size; }
		inline sf::Vector2i GetMousePosition() { return m_mousePosition; }
		inline sf::Vector2f GetPointWindowPos(sf::Vector2i _point);
		inline sf::RenderWindow& GetWindow() { return m_renderWindow; }
		inline sf::RenderTexture& GetRenderTexture() { return m_renderTexture; }

		void SetMousePosition(sf::Vector2i _mousePosition);
		inline void SetFullscreen(bool _isFullscreen) { m_isFullscreen = _isFullscreen; CreateRenderWindow(); }
		void SetVSync(bool _isVSync);
		inline void SetAntialiasing(bool _isAntialiasing) { m_isAntialiasing = _isAntialiasing; CreateRenderWindow(); }
		void SetSize(sf::Vector2i _size);
		void SetIcon(std::string _iconPath);
};


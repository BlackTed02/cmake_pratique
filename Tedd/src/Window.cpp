#include "pch.h"
#include "Window.h"

Window::Window(std::string _title, sf::Vector2i _size, bool _isFullscreen, bool _isVSync, bool _isAntialiasing)
{
	m_title = _title;
	m_size = _size;
	m_isFullscreen = _isFullscreen;
	m_isVSync = _isVSync;
	m_isAntialiasing = _isAntialiasing;
	m_isFocused = false;
	m_event = sf::Event();
	
	CreateRenderWindow();
	m_renderWindow.setVerticalSyncEnabled(m_isVSync);
	m_renderTexture.create(m_size.x, m_size.y);
}

void Window::Update()
{
	if (m_view.has_value())
	{
		m_renderWindow.setView(m_view.value()->GetView());
	}
	else
	{
		m_renderWindow.setView(m_renderWindow.getDefaultView());
	}

	while (m_renderWindow.pollEvent(m_event))
	{
#ifdef USING_EDITOR
		ImGui::SFML::ProcessEvent(m_event);
#endif
		if (m_event.type == sf::Event::Closed)
		{
			m_renderWindow.close();
		}

		if (m_event.type == sf::Event::Resized)
		{
			m_size = sf::Vector2i(m_event.size.width, m_event.size.height);
		}

		if (m_event.type == sf::Event::GainedFocus)
		{
			m_isFocused = true;
		}

		if (m_event.type == sf::Event::LostFocus)
		{
			m_isFocused = false;
		}

		if (m_event.type == sf::Event::KeyPressed)
		{
			if (m_event.key.code == sf::Keyboard::F11)
			{
				m_isFullscreen = !m_isFullscreen;
				// CreateRenderWindow();
			}
		}
	}

	m_mousePosition = sf::Mouse::getPosition(m_renderWindow);
}

void Window::Draw(sf::Drawable& _drawable)
{
	m_renderTexture.draw(_drawable);
}

void Window::Draw(sf::Drawable& _drawable, sf::RenderStates _states)
{
	m_renderTexture.draw(_drawable, _states);
}

void Window::Draw(sf::Drawable& _drawable, sf::Shader& _shader)
{
	m_renderTexture.draw(_drawable, sf::RenderStates(&_shader));
}

void Window::Draw(sf::Drawable& _drawable, sf::Texture& _texture)
{
	m_renderTexture.draw(_drawable, sf::RenderStates(&_texture));
}

void Window::BeginDraw()
{
	m_renderTexture.clear();
	m_renderWindow.clear();
}

void Window::Display()
{
	m_renderTexture.display();
	m_sprite.setTexture(m_renderTexture.getTexture());
	m_renderWindow.draw(m_sprite);
}

void Window::EndDraw()
{
	m_renderWindow.display();
}

void Window::Close()
{
	m_renderWindow.close();
}

void Window::CreateRenderWindow()
{
	sf::ContextSettings settings;
	if (m_isAntialiasing)
	{
		settings.antialiasingLevel = 8;
	}
	else
	{
		settings.antialiasingLevel = 0;
	}
	m_renderWindow.create(sf::VideoMode(m_size.x, m_size.y), m_title, m_isFullscreen ? sf::Style::Fullscreen : sf::Style::Default, settings);

#ifdef _WIN32

	// Get native window handle
	HWND hwnd = m_renderWindow.getSystemHandle();

	// Change title bar color (Only works on Windows 10+ with dark mode)
	BOOL darkMode = TRUE;
	DwmSetWindowAttribute(hwnd, DWMWA_USE_IMMERSIVE_DARK_MODE, &darkMode, sizeof(darkMode));

	// Change the window style to a different look
	LONG style = GetWindowLong(hwnd, GWL_STYLE);
	style |= WS_OVERLAPPED | WS_CAPTION | WS_THICKFRAME; // Keep border and title bar
	SetWindowLong(hwnd, GWL_STYLE, style);
	SetWindowPos(hwnd, NULL, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE);

	/*
	MARGINS margins = { -1 };
	DwmExtendFrameIntoClientArea(hwnd, &margins);
	*/

#endif // _WIN32

	SetIcon("../Resources/Logo/logo-sans-texte.png");
}

sf::Vector2f Window::GetMousePosRelativeToWindow()
{
	return m_renderWindow.mapPixelToCoords(m_mousePosition);
}

sf::Vector2f Window::GetPointWindowPos(sf::Vector2i _point)
{
	return m_renderWindow.mapPixelToCoords(_point);
}

void Window::SetMousePosition(sf::Vector2i _mousePosition)
{
	m_mousePosition = _mousePosition;
	sf::Mouse::setPosition(m_mousePosition, m_renderWindow);
}

void Window::SetVSync(bool _isVSync)
{
	m_isVSync = _isVSync;
	m_renderWindow.setVerticalSyncEnabled(m_isVSync);
}

void Window::SetSize(sf::Vector2i _size)
{
	m_size = _size;
	m_renderWindow.setSize(sf::Vector2u(m_size.x, m_size.y));
}

void Window::SetIcon(std::string _iconPath)
{
	sf::Image icon;
	icon.loadFromFile(_iconPath);
	m_renderWindow.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}

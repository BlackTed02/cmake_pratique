#pragma once
#include "tools.h"

class Window;

class View
{
	private:
		sf::View m_view;
		sf::Vector2f m_position;
		sf::Vector2f m_size;
		sf::Vector2f m_center;

	public:

		View();
		View(Window& _window);
		View(sf::Vector2f _size);
		View(sf::Vector2f _size, sf::Vector2f _center);

		void SetPosCenter(sf::Vector2f _center);
		void SetPosition(sf::Vector2f _position);
		inline void Setsize(sf::Vector2f _size) { m_size = _size; }
		void SetView(Window& _window);
		void CopyThisView(sf::View _view);

		inline const sf::View& GetView() { return m_view; }
		inline const sf::Vector2f& GetPosition() { return m_position; }
		inline const sf::Vector2f& GetSize() { return m_size; }
		inline const sf::Vector2f& GetCenter() { return m_center; }
};


#pragma once
#include <iostream>
#include "Component.h"

class TransformComponent : public Component
{
	using Component::Component;
	private:
		Entity* m_parent = nullptr;
		sf::Vector2f m_position = sf::Vector2f(0.f, 0.f);
		sf::Vector2f m_scale = sf::Vector2f(0.f, 0.f);
		float m_angle = 0.f;
	public:
		TransformComponent(sf::Vector2f _pos, sf::Vector2f _size, float _angle);
		TransformComponent(Entity* _parent, sf::Vector2f _pos, sf::Vector2f _size, float _angle);
		virtual void Update() override;
#ifdef USING_EDITOR
		void EditorRender() override;
#endif
		nlohmann::json ToJson() override;
		void FromJson(const nlohmann::json& _json) override;

		void Move(sf::Vector2f _pos);
		void Move(float _x, float _y);
		void Rotation(float _angle);

		inline void SetPosition(sf::Vector2f _pos) { m_position = _pos;}
		inline void SetPosition(float _x, float _y) { m_position.x = _x; m_position.y = _y; }
		inline void SetSize(sf::Vector2f _size) { m_scale = _size; }
		
		inline void SetSize(float _x, float _y)	{ m_scale.x = _x; m_scale.y = _y; }
		inline void SetAngle(float _angle) { m_angle = _angle; }
		inline void SetBounds(sf::FloatRect _bounds) { m_position = sf::Vector2f(_bounds.left, _bounds.top); m_scale = sf::Vector2f(_bounds.width, _bounds.height); }

		sf::Vector2f GetLocalPosition();
		sf::Vector2f GetLocalSize();
		float GetLocalAngle();

		inline sf::FloatRect GetBounds() { return sf::FloatRect(m_position, m_scale); }
		sf::Vector2f GetWorldPosition();
		sf::Vector2f GetWorldSize();
		float GetWorldAngle();
		sf::FloatRect GetWorldBounds();
};

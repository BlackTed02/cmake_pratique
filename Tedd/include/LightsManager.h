#pragma once
#include "tools.h"

namespace Lights
{
	class Light
	{
		private:
			sf::Vector2f m_position;
			sf::Color m_color;
			float m_radius;
			float m_attenuation;

		public:
			Light();
			Light(sf::Vector2f _pos, sf::Color _clr = sf::Color::Black, float _rds = 0.f, float _attenuation = 0.f);

			const sf::Vector2f GetPosition() const { return this->m_position; }
			const sf::Color GetColor() const { return this->m_color; }
			const float GetRadius() const { return this->m_radius; }
			const float GetOpacity() const { return this->m_color.a / 255.f; }
			const float GetAttenuation() const { return this->m_attenuation; }

			void SetPosition(sf::Vector2f _new) { this->m_position = _new; }
			void SetColor(sf::Color _new) { this->m_color = _new; }
			void SetRadius(float _new) { this->m_radius = _new; }
			void SetOpacity(float _new) { this->m_color.a = _new * 255; }
			void SetAttenuation(float _new) { this->m_attenuation = _new; }
	};

	Light* Create();
	Light* Create(sf::Vector2f _pos, sf::Color _clr = sf::Color::Black, float _rds = 0.f);
	void Destroy(Light* _light);

	void Init();
	void Render(sf::RenderTexture& _tex);
}
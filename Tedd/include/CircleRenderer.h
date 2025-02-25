#pragma once
#include "RenderComponent.h"

class CircleRenderer : public RenderComponent
{
	private:
		sf::CircleShape m_circle;
	public:
		CircleRenderer() = default;
		CircleRenderer(sf::Color _color);
		~CircleRenderer() = default;

		void Update() override;
		void Render(sf::RenderTarget& _window) override;
		nlohmann::json ToJson() override;
		void FromJson(const nlohmann::json& _json) override;

		void SetTexture(std::string _name) override;
		inline void SetTextureRect(sf::IntRect _rect) override { p_textRect = _rect; m_circle.setTextureRect(p_textRect); }
};

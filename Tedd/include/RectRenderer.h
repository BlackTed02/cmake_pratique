#pragma once
#include "RenderComponent.h"

class RectRenderer : public RenderComponent
{
	private:
		sf::RectangleShape m_rect;
	public:
		RectRenderer() = default;
		RectRenderer(sf::Color _color);
		~RectRenderer() = default;

		void Update() override;
		void Render(sf::RenderTarget& _window) override;
		nlohmann::json ToJson() override;
		void FromJson(const nlohmann::json& _json) override;

		void SetTexture(std::string _name) override;
		inline void SetTextureRect(sf::IntRect _rect) override { p_textRect = _rect; m_rect.setTextureRect(p_textRect); }
};


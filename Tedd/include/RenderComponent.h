#pragma once
#include "Component.h"

class RenderComponent : public Component
{
	protected:
		sf::Color p_color = sf::Color::White;
		sf::Vector2f p_origin = sf::Vector2f(0.f, 0.f);
		sf::Texture p_texture;
		sf::IntRect p_textRect = sf::IntRect(0, 0, 0, 0);
		std::string p_textName = "";
	public:
		RenderComponent() = default;
		virtual void Update() override = 0;
		virtual void Render(sf::RenderTarget& _window) = 0;
		nlohmann::json ToJson() override = 0;
		void FromJson(const nlohmann::json& _json) override = 0;

		inline void SetColor(sf::Color _color) { p_color = _color; }
		inline sf::Color GetColor() { return p_color; }
		inline void SetOrigin(sf::Vector2f _origin) { p_origin = _origin; }
		inline sf::Vector2f GetOrigin() { return p_origin; }
		virtual void SetTexture(std::string _name) = 0;
		virtual void SetTextureRect(sf::IntRect _rect) = 0;
		sf::IntRect GetTextureRect() { return p_textRect; }
		inline void SetTextureName(std::string _name) { p_textName = _name; }
		inline std::string GetTextureName() { return p_textName; }

#ifdef USING_EDITOR
		void EditorRender() override;
#endif
};


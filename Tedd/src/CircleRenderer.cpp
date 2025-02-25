#include "pch.h"
#include "CircleRenderer.h"
#include "Entity.h"

CircleRenderer::CircleRenderer(sf::Color _color)
{
	m_circle.setFillColor(_color);
}

void CircleRenderer::Update()
{
	m_circle.setOrigin(sf::Vector2f(p_owner->transform->GetWorldSize().x /2.f, p_owner->transform->GetWorldSize().x / 2.f));
	m_circle.setPosition(p_owner->transform->GetWorldPosition());
	m_circle.setRadius(p_owner->transform->GetWorldSize().x / 2.f);
	m_circle.setFillColor(p_color);
	m_circle.setRotation(p_owner->transform->GetWorldAngle());
}

void CircleRenderer::Render(sf::RenderTarget& _window)
{
	_window.draw(m_circle);
}

nlohmann::json CircleRenderer::ToJson()
{
	nlohmann::json json;

	json["color"] = { p_color.r, p_color.g, p_color.b, p_color.a };
	json["texture"] = p_textName.c_str();

	return json;
}

void CircleRenderer::FromJson(const nlohmann::json& _json)
{
	p_color.r = _json["color"][0];
	p_color.g = _json["color"][1];
	p_color.b = _json["color"][2];
	p_color.a = _json["color"][3];
	p_textName = _json["texture"];
	if (p_textName != "")
	{
		SetTexture(p_textName);
	}
}

void CircleRenderer::SetTexture(std::string _name)
{
	std::string destination = "../Resources/Textures/";
	destination += _name.substr(_name.find_last_of("/\\") + 1);
	//copyFile(_name, destination);
	p_texture.loadFromFile(_name);
	m_circle.setTexture(&p_texture, true);
	SetTextureRect(m_circle.getTextureRect());
}

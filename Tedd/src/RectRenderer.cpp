#include "pch.h"
#include "RectRenderer.h"
#include "Entity.h"

RectRenderer::RectRenderer(sf::Color _color)
{
	m_rect.setFillColor(_color);
}

void RectRenderer::Update()
{
	m_rect.setOrigin(p_owner->transform->GetWorldSize() / 2.f);
	m_rect.setPosition(p_owner->transform->GetWorldPosition());
	m_rect.setSize(p_owner->transform->GetWorldSize());
	m_rect.setFillColor(p_color);
	m_rect.setRotation(p_owner->transform->GetWorldAngle());
}


void RectRenderer::Render(sf::RenderTarget& _window)
{
	_window.draw(m_rect);
}

nlohmann::json RectRenderer::ToJson()
{
	nlohmann::json json;

	json["color"] = { p_color.r, p_color.g, p_color.b, p_color.a };
	json["texture"] = p_textName.c_str();

	return json;
}

void RectRenderer::FromJson(const nlohmann::json& _json)
{
	if (_json.contains("color"))
	{
		p_color.r = _json["color"][0];
		p_color.g = _json["color"][1];
		p_color.b = _json["color"][2];
		p_color.a = _json["color"][3];
	}
	if (_json.contains("texture"))
	{
		p_textName = _json["texture"];
		if (p_textName != "")
		{
			SetTexture(p_textName);
		}
	}
}

void RectRenderer::SetTexture(std::string _name)
{
	std::string destination = "../Resources/Textures/";
	destination += _name.substr(_name.find_last_of("/\\") + 1);
	//copyFile(_name, destination);
	p_texture.loadFromFile(destination);
	m_rect.setTexture(&p_texture, true);
	SetTextureRect(m_rect.getTextureRect());
}

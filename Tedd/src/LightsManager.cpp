#include "pch.h"
#include "LightsManager.h"

namespace Lights
{
	namespace
	{
		std::list<Light*> lightList;
		sf::Shader shader;
		sf::Sprite renderSprite;

		float lightsTimer = 0.f;
	}

	Light *Create()
	{
		Light *newLight = new Light();
		lightList.push_back(newLight);
		return newLight;
	}

	Light *Create(sf::Vector2f _pos, sf::Color _clr, float _rds)
	{
		Light *newLight = new Light(_pos, _clr, _rds);
		lightList.push_back(newLight);
		return newLight;
	}

	void Destroy(Light *_light)
	{
		for (auto l = lightList.begin(); l != lightList.end(); l++)
		{
			if (*l == _light)
			{
				lightList.erase(l);
				delete _light;
				return;
			}
		}
	}


	void Init()
	{
		shader.loadFromFile("../Resources/Shaders/lights.frag", sf::Shader::Fragment);
	}

	void Render(sf::RenderTexture &_tex)
	{
		lightsTimer += GetDeltaTime();
		for (auto& l : lightList)
		{
			renderSprite.setTexture(_tex.getTexture());
			/// Set uniforms based on l's values
			shader.setUniform("uTime", lightsTimer);
			shader.setUniform("uWinSize", sf::Vector2f((WINDOW_WIDTH), (WINDOW_HEIGHT)));
			shader.setUniform("uTex", _tex.getTexture());
			shader.setUniform("uPos", l->GetPosition());
			shader.setUniform("uClr", sf::Glsl::Ivec4(l->GetColor()));
			shader.setUniform("uRds", l->GetRadius());
			shader.setUniform("uAtn", l->GetAttenuation());
			_tex.draw(renderSprite, sf::RenderStates(&shader));
		}
	}


	Light::Light()
	{
		this->m_position = sf::Vector2f();
		this->m_color = sf::Color::White;
		this->m_radius = 0.f;
		this->m_attenuation = 0.f;
	}

	Light::Light(sf::Vector2f _pos, sf::Color _clr, float _rds, float _attenuation)
	{
		this->m_position = _pos;
		this->m_color = _clr;
		this->m_radius = _rds;
		this->m_attenuation = _attenuation;
	}
}
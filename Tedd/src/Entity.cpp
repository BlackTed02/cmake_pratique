#include "pch.h"
#include "Entity.h"

Entity::Entity(sf::Vector2f _position)
{
	transform = std::move(AddComponent<TransformComponent>(_position, sf::Vector2f(0.f, 0.f), 0.f));
}

Entity::Entity(sf::Vector2f _position, float _rotation)
{
	transform = std::move(AddComponent<TransformComponent>(_position, sf::Vector2f(0.f, 0.f), _rotation));
}

Entity::Entity(sf::Vector2f _position, sf::Vector2f _size)
{
	transform = std::move(AddComponent<TransformComponent>(_position, _size, 0.f));
}

Entity::Entity(sf::Vector2f _position, sf::Vector2f _size, float _rotation)
{
	transform = std::move(AddComponent<TransformComponent>(_position, _size, _rotation));
}

Entity::Entity(Entity* _parent, sf::Vector2f _position)
{
	transform = AddComponent<TransformComponent>(_parent, _position, sf::Vector2f(0.f, 0.f), 0.f);
}

Entity::Entity(Entity* _parent, sf::Vector2f _position, float _rotation)
{
	transform = AddComponent<TransformComponent>(_parent, _position, sf::Vector2f(0.f, 0.f), _rotation);
}

Entity::Entity(Entity* _parent, sf::Vector2f _position, sf::Vector2f _size)
{
	transform = AddComponent<TransformComponent>(_parent, _position, _size, 0.f);
}

Entity::Entity(Entity* _parent, sf::Vector2f _position, sf::Vector2f _size, float _rotation)
{
	transform = AddComponent<TransformComponent>(_parent, _position, _size, _rotation);
}

Entity::~Entity()
{
	RemoveComponents<Component>();
}

nlohmann::json Entity::ToJson()
{
	nlohmann::json json;

	json["name"] = GetName();

	for (const auto& comp : m_components)
	{
		json["Component"][GlobalComponentFactory.GetComponentNameByType(typeid(*comp))] = comp->ToJson();
	}
	return json;
}

void Entity::FromJson(const nlohmann::json& _json)
{
	m_name = _json["name"];

	for (auto& data : _json["Component"].items())
	{
		Component* newComp = nullptr;
	
		if (data.key() == "TransformComponent")
		{
			newComp = transform;
		}
		else if (GlobalComponentFactory.ContainsComponentByName(data.key()))
		{
			newComp = AddComponent(GlobalComponentFactory.GetComponentTypeByName(data.key()));
		}

		if (newComp)
		{
			newComp->FromJson(data.value());
		}
	}
}

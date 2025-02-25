#include "pch.h"
#include "Scene.h"
#include "ColliderComponent.h"

Scene::Scene()
{
	p_vertexArray.setPrimitiveType(sf::PrimitiveType::Triangles);
}

Scene::~Scene()
{
	while (p_entities.size() > 0)
	{
		DestroyEntity(0);
	}
}

void Scene::Update()
{
	for (Entity* entity : p_entities)
	{
		for (auto* component : entity->GetComponents<Component>())
		{
			component->Update();
		}
	}
	UpdatePhysics();

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		for (Entity* entity : p_entities)
		{
			for (auto* component : entity->GetComponents<RectRenderer>())
			{
				component->p_owner->transform->Move(sf::Vector2f(100.f * GetDeltaTime(),0.f));
			}
		}
	}
	
}

void Scene::UpdatePhysics()
{
	for (Entity* entity : p_entities)
	{
		for (auto collider : entity->GetComponents<ColliderComponent>())
		{
			for (Entity* entity2 : p_entities)
			{
				if (entity == entity2)
					continue;
				for (auto* collider2 : entity2->GetComponents<ColliderComponent>())
				{
					collider->IsCollidingWith(*collider2);
				}
			}
		}
	}
}

void Scene::Save()
{
	nlohmann::json json;

	for (Entity* entity : p_entities)
	{
		json["Entities"].push_back(entity->ToJson());
	}

	std::ofstream file("../Resources/JSON/Scene.json");

	if (file.is_open())
	{
		file << json.dump(4);
		file.close();
	}
}

void Scene::Load()
{
	std::ifstream file("../Resources/JSON/Scene.json");

	if (file.is_open())
	{
		nlohmann::json json;

		try
		{
			file >> json;
		}
		catch (nlohmann::json::parse_error& e)
		{
			std::cerr << "Erreur: Echec de l'analyse JSON a la ligne " << e.byte << ": " << e.what() << std::endl;
			file.close();
			return;
		}

		if (json.contains("Entities") && !json["Entities"].empty())
		{
			for (nlohmann::json& n : json["Entities"])
			{
				Entity* entity = CreateEntity();

				entity->FromJson(n);
			}
		}
		file.close();
	}
}

void Scene::DestroyEntity(int _index)
{
	delete p_entities[_index];
	p_entities.erase(p_entities.begin() + _index);
}

void Scene::DestroyEntity(Entity* _entity)
{
	for (int i = 0; i < p_entities.size(); i++)
	{
		if (p_entities[i] == _entity)
		{
			delete p_entities[i];
			p_entities.erase(p_entities.begin() + i);
			return;
		}
	}
}

void Scene::Render(sf::RenderTarget& _window)
{
	for (Entity* n : p_entities)
	{
		for (RenderComponent* render : n->GetComponents<RenderComponent>())
		{
			render->Render(_window);
		}

		for (VertexRenderer* vertex : n->GetComponents<VertexRenderer>())
		{
			for (size_t i = 0; i < vertex->m_vertexArray.getVertexCount(); i++)
			{
				p_vertexArray.append(vertex->m_vertexArray[i]);
			}
			vertex->m_vertexArray.clear();
		}

		if (p_vertexArray.getVertexCount() > 0)
		{
			_window.draw(p_vertexArray);
			p_vertexArray.clear();
		}
	}
}

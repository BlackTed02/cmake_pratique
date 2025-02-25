#pragma once
#include "Entity.h"

/// <summary>
/// <para>This class manage the entities in the scene (a scene is a container of entities)</para>
/// <para>You can add, remove, save and load entities</para>
/// <para>The Update function is used to update the entities</para>
/// <para>The Render function is used to draw the entities on the screen</para>
/// </summary>
class Scene
{
	protected:
		std::vector<Entity*> p_entities;
		sf::VertexArray p_vertexArray;
	public:
		Scene();
		~Scene();

		virtual void Update();
		virtual void UpdatePhysics();

		inline int GetEntityID() { return p_entities.size(); }

		void Save();
		void Load();

		/// <summary>
		/// Add an entity to the scene with a transform component by default
		/// </summary>
		/// <param name="_position">Position of the entity</param>
		/// <param name="_size">Size of the entity (scale)</param>
		/// <param name="_rotation">Rotation of the entity</param>
		/// <returns></returns>
		Entity* CreateEntity(sf::Vector2f _position = sf::Vector2f(500.f, 500.f), 
			sf::Vector2f _size = sf::Vector2f(200.f, 200.f), 
			float _rotation = 0.f)
		{
			Entity* newEntity = new Entity(_position, _size, _rotation);

			newEntity->SetName("Entity_" + std::to_string(GetEntityID()));
			p_entities.push_back(newEntity);

			return newEntity;
		}

		Entity* CreateEntityWithParent(Entity* _parent, sf::Vector2f _position, sf::Vector2f _size, float _rotation)
		{
			Entity* newEntity = new Entity(_parent, _position, _size, _rotation);
			newEntity->SetParent(_parent);

			newEntity->SetName("Entity_" + std::to_string(GetEntityID()));
			p_entities.push_back(newEntity);

			return newEntity;
		}
		
		Entity* GetEntity(int _index)
		{
			return p_entities[_index];
		}

		std::vector<Entity*> GetEntities()
		{
			return p_entities;
		}

		void DestroyEntity(int _index);
		void DestroyEntity(Entity* _entity);
		void Render(sf::RenderTarget& _window);
};


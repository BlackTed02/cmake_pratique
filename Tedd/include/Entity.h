#pragma once
#include "ComponentFactory.h"

#define COMPONENT_TEMPLATE \
template<typename T, typename ...Args, typename = std::enable_if_t<std::is_base_of_v<Component, T>>>

class Entity
{
	private:
		std::vector<Component*> m_components;
		std::string m_name;

		Entity* m_parent = nullptr;  
		std::vector<Entity*> m_children; 
	public:
		Entity(sf::Vector2f _position);
		Entity(sf::Vector2f _position, float _rotation);
		Entity(sf::Vector2f _position, sf::Vector2f _size);
		Entity(sf::Vector2f _position, sf::Vector2f _size, float _rotation);
		Entity(Entity* _parent, sf::Vector2f _position);
		Entity(Entity* _parent, sf::Vector2f _position, float _rotation);
		Entity(Entity* _parent, sf::Vector2f _position, sf::Vector2f _size);
		Entity(Entity* _parent, sf::Vector2f _position, sf::Vector2f _size, float _rotation);
		~Entity();

		inline std::string GetName() { return m_name; }
		inline void SetName(std::string _name) { m_name = _name; }

		/// <summary>
		/// Save entity to json
		/// </summary>
		/// <returns>Return json</returns>
		nlohmann::json ToJson();
		
		/// <summary>
		/// Load entity from a json
		/// </summary>
		/// <param name="_json">Json to load</param>
		void FromJson(const nlohmann::json& _json);

		TransformComponent* transform = nullptr;

		void SetParent(Entity* _parent)
		{
			if (m_parent != _parent) {
				if (m_parent) {
					auto it = std::find(m_parent->m_children.begin(), m_parent->m_children.end(), this);
					if (it != m_parent->m_children.end()) {
						m_parent->m_children.erase(it);
					}
				}
				m_parent = _parent;
				if (m_parent) {
					m_parent->m_children.push_back(this);
				}
			}
		}

		Entity* GetParent() const { return m_parent; }

		const std::vector<Entity*>& GetChildren() const { return m_children; }

		/// <summary>
		/// Template function to add a component to the entity
		/// </summary>
		/// <param name="..._args">Parameters of any type</param>
		/// <returns>A pointer to the new component</returns>
		COMPONENT_TEMPLATE T* AddComponent(Args&&... _args)
		{
			T* newComp = new T(std::forward<Args>(_args)...);
			newComp->SetOwner(this);
			m_components.push_back(newComp);
			return newComp;
		}
		
		/// <summary>
		/// Add a component to the entity by using the type of component you want to instantiate
		/// </summary>
		/// <param name="_type">Type of the component</param>
		/// <returns>A pointer to the new component</returns>
		Component* AddComponent(std::type_index _type)
		{
			Component* newComp = GlobalComponentFactory.CreateComponent(_type);
			if (newComp != nullptr)
			{
				newComp->SetOwner(this);
				m_components.push_back(newComp);
				return newComp;
			}
			return nullptr;
		}

		/// <summary>
		/// Get a component by using the type of the component
		/// </summary>
		/// <returns>A pointer to the component you are looking for</returns>
		COMPONENT_TEMPLATE T* GetComponent()
		{
			for (const auto &n : m_components)
			{
				T* castedComp = dynamic_cast<T*>(n);

				if (castedComp != nullptr)
				{
					return castedComp;
				}
			}
			return nullptr;
		}

		/// <summary>
		/// Check if the entity has a component by using the type of the component
		/// </summary>
		/// <param name="_type">Type of a component you want to check</param>
		/// <returns>Return true if the entity has a component of the desired type otherwise return false</returns>
		bool HasComponent(std::type_index _type)
		{
			for (const auto &n : m_components)
			{
				if (typeid(*n) == _type)
				{
					return true;
				}
			}
			return false;
		}

		/// <summary>
		/// Return a container with all components of the desired type
		/// </summary>
		/// <returns>Return container</returns>
		COMPONENT_TEMPLATE std::vector<T*> GetComponents()
		{
			std::vector<T*> compsOfType;

			for (const auto& n : m_components)
			{
				T* castedComp = dynamic_cast<T*>(n);

				if (castedComp != nullptr)
				{
					compsOfType.push_back(castedComp);
				}
			}
			return compsOfType;
		}


		/// <summary>
		/// Remove component from the entity by using the type of the component
		/// </summary>
		/// <returns></returns>
		COMPONENT_TEMPLATE void RemoveComponent()
		{
			for (int i = 0; i < m_components.size(); i++)
			{
				T* castedComp = dynamic_cast<T*>(m_components[i]);

				if (castedComp != nullptr)
				{
					m_components.erase(m_components.begin() + i);
					return;
				}
			}
		}

		/// <summary>
		/// Remove component from the entity by using the type of the component
		/// </summary>
		/// <param name="_type"></param>
		void RemoveComponent(std::type_index _type)
		{
			for (int i = 0; i < m_components.size(); i++)
			{
				if (typeid(*m_components[i]) == _type)
				{
					m_components.erase(m_components.begin() + i);
					return;
				}
			}
		}

		/// <summary>
		/// Remove all components of the desired type from the entity
		/// </summary>
		/// <returns></returns>
		COMPONENT_TEMPLATE void RemoveComponents()
		{
			for (int i = 0; i < m_components.size(); i++)
			{
				T* castedComp = dynamic_cast<T*>(m_components[i]);

				if (castedComp != nullptr)
				{
					m_components.erase(m_components.begin() + i);
					i--;
				}
			}
		}
};


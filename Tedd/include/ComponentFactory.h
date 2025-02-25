#pragma once

#include "tools.h"
#include "Component.h"
#include "TransformComponent.h"
#include "RenderComponent.h"
#include "RectRenderer.h"
#include "CircleRenderer.h"
#include "VertexRenderer.h"
#include "LightComponent.h"
#include "ColliderComponent.h"

/// Class ComponentFactory
/// This class is a singleton that will be used to create components
/// ALL components must be registered in this class
/// Use the RegisterComponent method to register a new component
class ComponentFactory
{
	using ComponentCreator = std::function<Component*()>;
	private:
		std::unordered_map<std::type_index, ComponentCreator> m_componentCreators;
		std::unordered_map<std::type_index, std::string> m_componentNames;
	public:
		ComponentFactory() = default;
		~ComponentFactory()
		{
			for (auto [type, creator] : m_componentCreators)
			{
				delete creator();
			}
		}

		/// <summary>
		/// Register ALL components 
		/// When you need to add a new component, add it here (include the header file)
		/// </summary>
		void RegisterComponents()
		{
			RegisterComponent<TransformComponent>("TransformComponent");
			RegisterComponent<RectRenderer>("RectRenderer");
			RegisterComponent<CircleRenderer>("CircleRenderer");
			RegisterComponent<VertexRenderer>("VertexRenderer");
			RegisterComponent<ColliderComponent>("ColliderComponent");
			// RegisterComponent<LightComponent>("LightComponent");
		}

		/// <summary>
		/// Register a component in the factory container
		/// </summary>
		/// <typeparam name="T">Object you want to register</typeparam>
		/// <param name="_name">Name of this object (this will be use to display component name)</param>
		template<typename T>
		void RegisterComponent(const std::string& _name)
		{
			std::type_index type = typeid(T);
			m_componentCreators[type] = []() -> T*{ return new T();};
			m_componentNames[type] = _name;
		}

		/// <summary>
		/// Create component by using the wanted type
		/// </summary>
		/// <param name="_type">A pointer to the new component</param>
		/// <returns></returns>
		Component* CreateComponent(std::type_index _type)
		{
			auto it = m_componentCreators.find(_type);
			if (it != m_componentCreators.end())
			{
				return it->second();
			}
			return nullptr;
		}

		/// <summary>
		/// Get all registered components
		/// </summary>
		/// <returns>Factory's container</returns>
		const std::unordered_map<std::type_index, std::string>& GetRegisteredComponents() const
		{
			return m_componentNames;
		}

		/// <summary>
		/// Get component name by using the type
		/// </summary>
		/// <param name="_type">Object you want to get name</param>
		/// <returns>Name of wanted component</returns>
		const std::string GetComponentNameByType(std::type_index _type)
		{
			auto it = m_componentNames.find(_type);
			if (it != m_componentNames.end())
			{
				return it->second;
			}
			return "";
		}

		/// <summary>
		/// This function will check if a component is registered by using the name
		/// It used to check if a component is already registered in the factory
		/// </summary>
		/// <param name="_name">Name of component</param>
		/// <returns>Return true if the component is registered otherwise it return false</returns>
		bool ContainsComponentByName(std::string _name)
		{
			for (auto [comp, name] : m_componentNames)
			{
				if (name == _name)
				{
					return true;
				}
			}
			return false;
		}

		/// <summary>
		/// Return the type of a component by using the name
		/// </summary>
		/// <param name="_name">Name of the component you want to get</param>
		/// <returns></returns>
		std::type_index GetComponentTypeByName(std::string _name)
		{
			for (auto [comp, name] : m_componentNames)
			{
				if (name == _name)
				{
					return comp;
				}
			}
			return std::type_index(typeid(Component));
		}
};

inline ComponentFactory GlobalComponentFactory{};
#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "tools.h"

class Entity;

class Component
{
	protected:
	public:
	Entity* p_owner = nullptr;
		Component() = default;
		~Component() = default;

		inline void SetOwner(Entity* _owner) { p_owner = _owner; }
		inline Entity* GetOwner() { return p_owner; }

		/// <summary>
		/// Absract function to update the component
		/// </summary>
		virtual void Update() = 0;
#ifdef USING_EDITOR
		/// <summary>
		/// Absract function to render the component editor in the engine
		/// </summary>
		virtual void EditorRender() = 0;
#endif
		/// <summary>
		/// Absract function to convert the component to a json object
		/// </summary>
		/// <returns></returns>
		virtual nlohmann::json ToJson() = 0;
		/// <summary>
		/// Absract function to convert json data into the component
		/// </summary>
		/// <param name="_json"></param>
		virtual void FromJson(const nlohmann::json& _json) = 0;
};

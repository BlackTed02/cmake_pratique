#pragma once
#include "Component.h"
#include <optional>

//Vertex collider unity
//2BitCoding

enum class ColliderType
{
	CIRCLE,
	POLYGONE
};

struct RectangleBounds
{
	sf::Vector2f p1;
	sf::Vector2f p2;
	sf::Vector2f p3;
	sf::Vector2f p4;
};

class ColliderComponent : public Component
{
public : 	

	ColliderComponent(Entity* _entity = nullptr);
	inline ColliderType GetColliderType() { return m_colliderType; }

	/// <summary>
	/// Check if a collider component is colliding with another one
	/// </summary>
	/// <param name="_colliderComponent">the other collider component</param>
	/// <returns>the collission point to add forces to it if necessary</returns>
	std::optional<sf::Vector2f> IsCollidingWith(ColliderComponent _colliderComponent);

	/// <summary>
	/// Check if they are in range with AABB
	/// </summary>
	/// <param name="_colliderComponent">the other collider component</param>
	/// <returns></returns>
	bool ShouldCheckCollission(ColliderComponent _colliderComponent);

	void Update();

#ifdef USING_EDITOR
	void EditorRender();
#endif
	nlohmann::json ToJson();
	void FromJson(const nlohmann::json& _json);
private :
	std::optional<sf::Vector2f> FindContactPoint(float const& _circleRadius, sf::Vector2f const& _circleCenter, std::vector<sf::Vector2f> const& _verticies);
	std::optional<sf::Vector2f> FindContactPoint(std::vector<sf::Vector2f> const& _verticies1, std::vector<sf::Vector2f> const& _verticies2);

	bool CheckAABBCollission(ColliderComponent _other);
	void UpdateAABB();
	ColliderType m_colliderType;
	sf::FloatRect m_AABB;
};


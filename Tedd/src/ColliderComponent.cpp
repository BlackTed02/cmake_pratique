#include "pch.h"
#include "ColliderComponent.h"
#include "Entity.h"

ColliderComponent::ColliderComponent(Entity* _entity) : Component()
{
	if (_entity != nullptr)
	{
		if (_entity->GetComponent<VertexRenderer>() != nullptr)
		{
			m_colliderType = ColliderType::POLYGONE;
		}
		else if (_entity->GetComponent<CircleRenderer>() != nullptr)
		{
			m_colliderType = ColliderType::CIRCLE;
		}
		else
		{
			m_colliderType = ColliderType::POLYGONE;
		}
	}
	
}

std::optional<sf::Vector2f> ColliderComponent::IsCollidingWith(ColliderComponent _colliderComponent)
{
	std::optional<sf::Vector2f> toSend;
	switch (_colliderComponent.GetColliderType())
	{
	case ColliderType::POLYGONE:
	{
		UpdateAABB();
		_colliderComponent.UpdateAABB();
		if (!CheckAABBCollission(_colliderComponent))
		{
			return toSend;
		}
		switch (m_colliderType)
		{
		case ColliderType::POLYGONE:
		{
			std::vector<sf::Vector2f> vertices1;

			if (auto vertex = _colliderComponent.p_owner->GetComponent<VertexRenderer>())
			{
				for (int i = 0; i < vertex->m_vertexArray.getVertexCount(); i++)
				{
					vertices1.push_back(vertex->m_vertexArray[i].position);
				}
			}
			else
			{
				sf::Vector2f const center1 = _colliderComponent.p_owner->transform->GetWorldPosition();

				sf::Vector2f const p11 = center1 - (_colliderComponent.p_owner->transform->GetWorldSize() / 2.f);

				sf::Vector2f const p21 = p11 + sf::Vector2f(_colliderComponent.p_owner->transform->GetWorldSize().x, 0.f);

				sf::Vector2f const p31 = p21 + sf::Vector2f(0.f, _colliderComponent.p_owner->transform->GetWorldSize().y);

				sf::Vector2f const p41 = p31 - sf::Vector2f(_colliderComponent.p_owner->transform->GetWorldSize().x, 0.f);


				vertices1.push_back(RotatePoint(center1, p11, _colliderComponent.p_owner->transform->GetWorldAngle()));
				vertices1.push_back(RotatePoint(center1, p21, _colliderComponent.p_owner->transform->GetWorldAngle()));
				vertices1.push_back(RotatePoint(center1, p31, _colliderComponent.p_owner->transform->GetWorldAngle()));
				vertices1.push_back(RotatePoint(center1, p41, _colliderComponent.p_owner->transform->GetWorldAngle()));
			}

			

			std::vector<sf::Vector2f> vertices2;

			if (auto vertex = p_owner->GetComponent<VertexRenderer>())
			{
				for (int i = 0; i < vertex->m_vertexArray.getVertexCount(); i++)
				{
					vertices2.push_back(vertex->m_vertexArray[i].position);
				}
			}
			else
			{
				sf::Vector2f const center2 = p_owner->transform->GetWorldPosition();

				sf::Vector2f const p12 = center2 - (p_owner->transform->GetWorldSize() / 2.f);

				sf::Vector2f const p22 = p12 + sf::Vector2f(p_owner->transform->GetWorldSize().x, 0.f);

				sf::Vector2f const p32 = p22 + sf::Vector2f(0.f, p_owner->transform->GetWorldSize().y);

				sf::Vector2f const p42 = p32 - sf::Vector2f(p_owner->transform->GetWorldSize().x, 0.f);


				vertices2.push_back(RotatePoint(center2, p12, p_owner->transform->GetWorldAngle()));
				vertices2.push_back(RotatePoint(center2, p22, p_owner->transform->GetWorldAngle()));
				vertices2.push_back(RotatePoint(center2, p32, p_owner->transform->GetWorldAngle()));
				vertices2.push_back(RotatePoint(center2, p42, p_owner->transform->GetWorldAngle()));

				toSend = FindContactPoint(vertices1, vertices2);
			}
			

			break;
		}
		case ColliderType::CIRCLE:
		{
			std::vector<sf::Vector2f> vertices;

			if (auto vertex = p_owner->GetComponent<VertexRenderer>())
			{
				for (int i = 0; i < vertex->m_vertexArray.getVertexCount(); i++)
				{
					vertices.push_back(vertex->m_vertexArray[i].position);
				}
			}
			else
			{
				sf::Vector2f const center = _colliderComponent.p_owner->transform->GetWorldPosition();

				sf::Vector2f const p1 = center - (_colliderComponent.p_owner->transform->GetWorldSize() / 2.f);

				sf::Vector2f const p2 = p1 + sf::Vector2f(_colliderComponent.p_owner->transform->GetWorldSize().x, 0.f);

				sf::Vector2f const p3 = p2 + sf::Vector2f(0.f, _colliderComponent.p_owner->transform->GetWorldSize().y);

				sf::Vector2f const p4 = p3 - sf::Vector2f(_colliderComponent.p_owner->transform->GetWorldSize().x, 0.f);

				vertices.push_back(RotatePoint(center, p1, _colliderComponent.p_owner->transform->GetWorldAngle()));
				vertices.push_back(RotatePoint(center, p2, _colliderComponent.p_owner->transform->GetWorldAngle()));
				vertices.push_back(RotatePoint(center, p3, _colliderComponent.p_owner->transform->GetWorldAngle()));
				vertices.push_back(RotatePoint(center, p4, _colliderComponent.p_owner->transform->GetWorldAngle()));
			}

			toSend = FindContactPoint(p_owner->transform->GetWorldSize().x / 2.f, p_owner->transform->GetWorldPosition(), vertices);
			break;
		}
		}
		break;
	}
	case ColliderType::CIRCLE:
	{
		if (m_colliderType == ColliderType::CIRCLE)
		{
			float sqrMag = GetSqrMagnitudeBetweenVector(_colliderComponent.GetOwner()->transform->GetWorldPosition(), p_owner->transform->GetWorldPosition());
			if (sqrMag < (_colliderComponent.GetOwner()->transform->GetWorldSize().x, _colliderComponent.GetOwner()->transform->GetWorldSize().y) *
				(_colliderComponent.GetOwner()->transform->GetWorldSize().x, _colliderComponent.GetOwner()->transform->GetWorldSize().y))
			{
				sf::Vector2f dir = Normalize(CreateVectorWithVector(p_owner->transform->GetWorldPosition(),
					_colliderComponent.GetOwner()->transform->GetWorldPosition()));
				toSend.emplace(p_owner->transform->GetWorldPosition() + dir * p_owner->transform->GetWorldSize().x);
			}
		}
		break;
	}
	default:
		break;
	}
	return toSend;
}

bool ColliderComponent::ShouldCheckCollission(ColliderComponent _colliderComponent)
{
	return false;
}

std::optional<sf::Vector2f> ColliderComponent::FindContactPoint(float const& _circleRadius,
	sf::Vector2f const& _circleCenter, std::vector<sf::Vector2f> const& _verticies)
{
	std::optional<sf::Vector2f> toSend;

	for (int i = 0; i < _verticies.size() - 1; i++)
	{
		if (!toSend.has_value())
		{
			sf::Vector2f const ab(_verticies[i + 1] - _verticies[i]);
			sf::Vector2f const ap(_circleCenter - _verticies[i]);

			float const dot = DotProduct(ab, ap);
			float const sqrMagAb = GetSqrMagnitudeBetweenVector(_verticies[i + 1], _verticies[i]);

			float const d = dot / sqrMagAb;

			sf::Vector2f contact;
			if (d < 0.f)
			{
				contact = _verticies[i];
			}
			else if (d > 1.f)
			{
				contact = _verticies[i + 1];
			}
			else {
				contact = _verticies[i] + ab * d;
			}

			if (GetSqrMagnitudeBetweenVector(contact, _circleCenter) < _circleRadius * _circleRadius)
			{
				toSend.emplace(contact);
			}
		}
	}
	return toSend;
}

std::optional<sf::Vector2f> ColliderComponent::FindContactPoint(std::vector<sf::Vector2f> const& _verticies1,
	std::vector<sf::Vector2f> const& _verticies2)
{
	std::optional<sf::Vector2f> toSend;

	float minDistSqr = LONG_MAX;
	sf::Vector2f closestPoint;

	for (int i = 0; i < _verticies1.size(); i++)
	{
		sf::Vector2f const& p = _verticies1[i];

		for (int j = 0; j < _verticies2.size(); j++)
		{
			sf::Vector2f const& va = _verticies2[j];
			sf::Vector2f const& vb = _verticies2[(j + 1) % _verticies2.size()];
			sf::Vector2f closest;
			float sqrMagCur;
			PointSegmentDistance(p, va, vb, sqrMagCur, closest);
			if (sqrMagCur - minDistSqr < 0.1f && sqrMagCur - minDistSqr > -0.1f)
			{
				if (GetSqrMagnitudeBetweenVector(closest, closestPoint) > 1.f)
				{
					sf::Vector2f cToC2 = CreateVectorWithVector(closest, closestPoint);
					float magnitude = GetMagnitude(cToC2);

					closestPoint = closest + Normalize(cToC2) * (magnitude / 2.f);
				}
			}
			else if (sqrMagCur < minDistSqr)
			{
				minDistSqr = sqrMagCur;
				closestPoint = closest;
			}
		}
	}

	for (int i = 0; i < _verticies2.size(); i++)
	{
		sf::Vector2f const& p = _verticies2[i];

		for (int j = 0; j < _verticies1.size(); j++)
		{
			sf::Vector2f const& va = _verticies1[j];
			sf::Vector2f const& vb = _verticies1[(j + 1) % _verticies1.size()];
			sf::Vector2f closest;
			float sqrMagCur;
			PointSegmentDistance(p, va, vb, sqrMagCur, closest);
			if (sqrMagCur - minDistSqr < 0.1f && sqrMagCur - minDistSqr > -0.1f)
			{
				if (GetSqrMagnitudeBetweenVector(closest, closestPoint) > 1.f)
				{
					sf::Vector2f cToC2 = CreateVectorWithVector(closest, closestPoint);
					float magnitude = GetMagnitude(cToC2);

					closestPoint = closest + Normalize(cToC2) * (magnitude / 2.f);
				}
			}
			else if (sqrMagCur < minDistSqr)
			{
				minDistSqr = sqrMagCur;
				closestPoint = closest;
			}
		}
	}
	if (minDistSqr < 1.f)
	{
		toSend.emplace(closestPoint);
	}

	return toSend;
}

void ColliderComponent::Update()
{
}

bool ColliderComponent::CheckAABBCollission(ColliderComponent _other)
{
	return _other.m_AABB.intersects(m_AABB);
}

void ColliderComponent::UpdateAABB()
{
	if (m_colliderType == ColliderType::CIRCLE)
	{
		m_AABB.left = p_owner->transform->GetWorldPosition().x - p_owner->transform->GetWorldSize().x;
		m_AABB.top = p_owner->transform->GetWorldPosition().y - p_owner->transform->GetWorldSize().x;
		m_AABB.width = p_owner->transform->GetWorldSize().x;
		m_AABB.height = p_owner->transform->GetWorldSize().x;
	}
	else
	{
		float minPosX = -LONG_MAX;
		float minPosY = -LONG_MAX;
		float maxPosX = LONG_MAX;
		float maxPosY = LONG_MAX;

		if (auto vertex = p_owner->GetComponent<VertexRenderer>())
		{
			for (int i = 0; i < vertex->m_vertexArray.getVertexCount(); i++)
			{
				if (vertex->m_vertexArray[i].position.x < minPosX)
				{
					minPosX = vertex->m_vertexArray[i].position.x;
				}
				if (vertex->m_vertexArray[i].position.x > maxPosX)
				{
					maxPosX = vertex->m_vertexArray[i].position.x;
				}

				if (vertex->m_vertexArray[i].position.y < minPosY)
				{
					minPosY = vertex->m_vertexArray[i].position.y;
				}
				if (vertex->m_vertexArray[i].position.y > maxPosY)
				{
					maxPosY = vertex->m_vertexArray[i].position.y;
				}
			}

		}
		else
		{
			sf::Vector2f const center = p_owner->transform->GetWorldPosition();
			sf::Vector2f points[4];
			points[0] = center - (p_owner->transform->GetWorldSize() / 2.f);

			points[1] = points[0] + sf::Vector2f(p_owner->transform->GetWorldSize().x, 0.f);

			points[2] = points[1] + sf::Vector2f(0.f, p_owner->transform->GetWorldSize().y);

			points[3] = points[2] - sf::Vector2f(p_owner->transform->GetWorldSize().x, 0.f);


			points[0] = RotatePoint(center, points[0], p_owner->transform->GetWorldAngle());
			points[1] = RotatePoint(center, points[1], p_owner->transform->GetWorldAngle());
			points[2] = RotatePoint(center, points[2], p_owner->transform->GetWorldAngle());
			points[3] = RotatePoint(center, points[3], p_owner->transform->GetWorldAngle());

			for (int i = 0; i < 4; i++)
			{
				if (points[i].x < minPosX)
				{
					minPosX = points[i].x;
				}
				if (points[i].x > maxPosX)
				{
					maxPosX = points[i].x;
				}

				if (points[i].y < minPosY)
				{
					minPosY = points[i].y;
				}
				if (points[i].y > maxPosY)
				{
					maxPosY = points[i].y;
				}
			}
		}
		m_AABB.left = minPosX;
		m_AABB.top = minPosY;
		m_AABB.width = maxPosX - minPosX;
		m_AABB.height = maxPosY - minPosY;
	}
}
#ifdef USING_EDITOR
void ColliderComponent::EditorRender()
{
	if (ImGui::CollapsingHeader("Collider", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ColliderType col;

		ImGui::Text("Collider Type :");
		ImGui::SameLine();
		const char* colissions[] = {
		  "CIRCLE",
		  "VERTEX"
		};
		int currentCol = static_cast<int>(m_colliderType);
		int lastCol = currentCol;
		ImGui::Combo("##Col Type", &currentCol, colissions, IM_ARRAYSIZE(colissions));	
		if (lastCol != currentCol)
		{
			m_colliderType = static_cast<ColliderType>(currentCol);
		}
	}
}
#endif

nlohmann::json ColliderComponent::ToJson()
{
	return nlohmann::json();
}

void ColliderComponent::FromJson(const nlohmann::json& _json)
{
}

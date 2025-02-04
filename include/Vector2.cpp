#include "Vector2.h"
#include <iostream>

namespace Dll
{
	Dll::Vector2::Vector2(int _x, int _y)
	{
		x = _x;
		y = _y;
	}

	Vector2 Dll::Vector2::add(Vector2 _v1, Vector2 _v2)
	{
		return Vector2(_v1.x + _v2.x, _v1.y + _v2.y);
	}

	Vector2 Dll::Vector2::substract(Vector2 _v1, Vector2 _v2)
	{
		return Vector2(_v1.x - _v2.x, _v1.y - _v2.y);
	}

	Vector2 Dll::Vector2::Multiply(Vector2 _v1, Vector2 _v2)
	{
		return Vector2(_v1.x * _v2.x, _v1.y * _v2.y);
	}

	Vector2 Dll::Vector2::Divide(Vector2 _v1, Vector2 _v2)
	{
		return Vector2(_v1.x / _v2.x, _v1.y / _v2.y);
	}

	void Dll::Vector2::print(Vector2 _v)
	{
		std::cout << "Vector : " << _v.x << " / " << _v.y << std::endl;
	}
}
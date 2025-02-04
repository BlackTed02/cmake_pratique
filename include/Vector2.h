#pragma once

namespace Dll
{
	class Vector2
	{
	public:
		int x;
		int y;

		Vector2() = default;
		Vector2(int _x, int _y);
		Vector2 add(Vector2 _v1, Vector2 _v2);
		Vector2 substract(Vector2 _v1, Vector2 _v2);
		Vector2 Multiply(Vector2 _v1, Vector2 _v2);
		Vector2 Divide(Vector2 _v1, Vector2 _v2);
		void print(Vector2 _v);
	};
}

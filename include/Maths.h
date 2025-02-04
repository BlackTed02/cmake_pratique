#pragma once
#include "Vector2.h"
#include <math.h>

namespace Dll
{
	class Maths
	{
	public:
		static int getSqrMagnitude(Dll::Vector2 const& _v);
		static float getMagnitude(Dll::Vector2 const& _v);
		static Dll::Vector2 normalize(Dll::Vector2 const& _v);
		static Dll::Vector2 polarCoord(Dll::Vector2 const& _v, int const& _r, int const& _teta);
	};
}

#include "Maths.h"

namespace Dll
{
    int Dll::Maths::getSqrMagnitude(Dll::Vector2 const& _v)
    {
        return (_v.x * _v.x) + (_v.y * _v.y);
    }
    float Maths::getMagnitude(Dll::Vector2 const& _v)
    {
        return sqrtf(getSqrMagnitude(_v));
    }
    Dll::Vector2 Maths::normalize(Dll::Vector2 const& _v)
    {
        float magnitude = getMagnitude(_v);
        if (magnitude < (float)1e-6)
        {
            return _v;
        }
        return Dll::Vector2(_v.x / magnitude, _v.y / magnitude);
    }
    Dll::Vector2 Maths::polarCoord(Dll::Vector2 const& _v, int const& _r, int const& _teta)
    {
        return Dll::Vector2(_v.x + (_r * cos(_teta)), _v.y + (_r * sin(_teta)));
    }
}
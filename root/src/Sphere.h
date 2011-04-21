#include "Color.h"

struct Sphere
{
	float _x0, _y0, _z0;
	float _r;
	float _reflectiveDistance;
	Color _color;
	bool _reflective;
	bool _currentSurface;
};
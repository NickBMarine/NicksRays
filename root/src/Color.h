#pragma once
#include <windows.h>

struct Color
{
	float _r, _g, _b;
	Color() : _r(0), _g(0), _b(0) {};
	Color(int red, int green, int blue);
	Color(float red, float green, float blue);
	Color operator+(const Color &c) const;
	Color operator-(const Color &c) const;
	Color operator*(float f) const;
	Color operator/(float f) const;
	bool operator!=(float f) const;
	bool operator==(float f) const;

	~Color(void){};
};


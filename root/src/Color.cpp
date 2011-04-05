#include "Color.h"

Color::Color(int red, int green, int blue)
{
	if ( red > 255)
		red = 255;
	if ( blue > 255)
		blue = 255;
	if ( green > 255)
		green = 255;

	_r = (float)red / 255;
	_g = (float)green / 255;
	_b = (float)blue / 255;
}

Color::Color(float red, float green, float blue)
{
	if ( red > 1.0f )
		red = 1.0f;
	if ( green > 1.0f )
		green = 1.0f;
	if ( blue > 1.0f )
		blue = 1.0f;

	_r = red;
	_g = green;
	_b = blue;

}

Color Color::operator+(const Color &c) const
{
	Color tempColor;
	
	tempColor._b = _b + c._b;
	
	tempColor._r = _r + c._r;
	
	tempColor._g = _g + c._g;

	return tempColor;

}

Color Color::operator-(const Color &c) const
{
	Color tempColor;
	
	tempColor._b = _b - c._b;
	
	tempColor._r = _r - c._r;
	
	tempColor._g = _g - c._g;

	return tempColor;
}

Color Color::operator*(float f) const
{
	Color tempColor;
	
	tempColor._b = _b * f;
	
	tempColor._r = _r * f;
	
	tempColor._g = _g * f;

	return tempColor;
}

Color operator*(const float & f, const Color & c)
{
	Color tempColor;
	tempColor._b = f * c._b;
	tempColor._g = f * c._g;
	tempColor._r = f * c._r;

	return tempColor;
}

Color Color::operator*(const Color & c) const
{
	Color tempColor;

	tempColor._b = _b * c._b;
	tempColor._r = _r * c._r;
	tempColor._g = _g * c._g;

	return tempColor;
}

Color Color::operator/(float f) const
{
	Color tempColor;
	
	tempColor._b = _b / f;
	
	tempColor._r = _r / f;
	
	tempColor._g = _g / f;

	return tempColor;
}

bool Color::operator!=(float f) const
{
	if ( _r != f && _g != f && _b != f)
	{
		return true;
	}
	return false;
}

bool Color::operator==(float f) const 
{
	if ( _r == f && _g == f && _b == f)
	{
		return true;
	}
	return false;
}
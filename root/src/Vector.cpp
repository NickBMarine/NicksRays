#include "Vector.h"
#include "math.h"


void Vector::Normalize()
{
	Vector tempVertex(_color, _x, _y, _z);
	float sqrdValues = (_x * _x) + (_y * _y) + (_z * _z);
	tempVertex._x = (tempVertex._x/sqrt(sqrdValues));
	tempVertex._y = (tempVertex._y/sqrt(sqrdValues));
	tempVertex._z = (tempVertex._z/sqrt(sqrdValues));

	*this = tempVertex;
}

Vector Vector::operator*(float & scalar)
{
	Vector tempVec;

	tempVec._color = _color * scalar;
	tempVec._x = _x * scalar;
	tempVec._y = _y * scalar;
	tempVec._z = _z * scalar;
	tempVec._w = _w * scalar;
	tempVec._u = _u * scalar;
	tempVec._v = _v * scalar;

	return tempVec;
}

void Vector::SetVec(float & X, float & Y, float & Z)
{
	_x = X;
	_y = Y;
	_z = Z;
}

Vector Vector::GetNormal(const Vector & verts)
{
	Vector normal;

	normal._x = ((_y * verts._z) - (_z * verts._y));
	normal._y = ((_z * verts._x) - (_x * verts._z));
	normal._z = ((_x * verts._y) - (_y * verts._x));

	normal.Normalize();

	return normal;
}

float Vector::GetDotProduct(const Vector * verts)
{
	float dot = ((_x * verts->_x) + (_y * verts->_y) + (_z * verts->_z));
	return dot;
}

float Vector::GetDotProduct(const Vector & verts)
{
	float dot = ((_x * verts._x) + (_y * verts._y) + (_z * verts._z));
	return dot;
}

float Vector::GetDotHom(Vector & verts)
{
	float dot = (verts._w * _w) + (verts._x * _x) + (verts._y * _y) + (verts._z * _z);
	return dot;
}

Vector Vector::SubtractHom(Vector & verts)
{
	Vector tempVert;

	tempVert._color = _color - verts._color;
	tempVert._x = _x - verts._x;
	tempVert._y = _y - verts._y;
	tempVert._z = _z - verts._z;
	tempVert._w = _w - verts._w;
	tempVert._u = _u - verts._u;
	tempVert._v = _v - verts._v;

	return tempVert;
}

Vector Vector::AddHom(Vector & verts)
{
	Vector tempVert;

	tempVert._color = _color + verts._color;
	tempVert._x = _x + verts._x;
	tempVert._y = _y + verts._y;
	tempVert._z = _z + verts._z;
	tempVert._w = _w + verts._w;

	return tempVert;
}

Vector Vector::ScaleHom(float & scale)
{
	Vector tempVert;

	tempVert._color = _color * scale;
	tempVert._x = _x * scale;
	tempVert._y = _y * scale;
	tempVert._z = _z * scale;
	tempVert._w = _w * scale;

	return tempVert;
}

void Vector::SetHomVec(Vector & vec)
{
	_x = vec._x;
	_y = vec._y;
	_z = vec._z;
	_w = vec._w;
}


float Vector::GetMagnitude()
{
	return (sqrt((_x * _x) + (_y * _y) + (_z * _z)));
}

Vector Vector::operator-(Vector & vector)
{
	Vector tempVec(_color, _x, _y, _z);
	tempVec._x = _x - vector._x;
	tempVec._y = _y - vector._y;
	tempVec._z = _z - vector._z;

	return tempVec;
}

Vector Vector::operator-=(Vector & vector)
{
	_x = _x - vector._x;
	_y = _y - vector._y;
	_z = _z - vector._z;

	return *this;
}

Vector Vector::operator+(Vector & vector)
{
	Vector tempVec(_color, _x, _y, _z);
	tempVec._color = _color + vector._color;
	tempVec._x = _x + vector._x;
	tempVec._y = _y + vector._y;
	tempVec._z = _z + vector._z;
	tempVec._w = _w + vector._w;
	tempVec._u = _u + vector._u;
	tempVec._v = _v + vector._v;

	return tempVec;
}

Vector Vector::operator+=(Vector & vector)
{
	_x = _x + vector._x;
	_y = _y + vector._y;
	_z = _z + vector._z;

	return *this;
}

bool Vector::operator!=(const Vector & vector)
{
	return ( (_x != vector._x) || (_y != vector._y) || (_z != vector._z));
}

bool Vector::operator==(const Vector & vector)
{
	return (( _x == vector._x) && (_y == vector._y) && (_z == vector._z));
}


void Vector::Negate()
{
	_x = -_x;
	_y = -_y;
	_z = -_z;
}
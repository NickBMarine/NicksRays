#pragma once
#include "Color.h"

struct Vector
{
	Color _color;
	float _x, _y, _z, _w;
	float _u, _v;
	Vector() : _x(0.0f), _y(0.0f), _z(0.0f), _u(0.0f), _v(0.0f) {};
	Vector(const float &X, const float &Y, const float &Z) : _x(X), _y(Y), _z(Z) {};
	Vector(const float &X, const float &Y, const float &Z, const float &U, const float &V) : _x(X), _y(Y), _z(Z), _w(1.0f), _u(U), _v(V) {};
	Vector(const Color &C, const float &X, const float &Y) : _color(C), _x(X), _y(Y), _z(0.0f), _w(1.0f) {};
	Vector(const Color &C, const float &X, const float &Y, const float &Z) : _color(C), _x(X), _y(Y), _z(Z), _w(1.0f){}
	Vector(const Color &C, const float &X, const float &Y, const float &Z, const float &W) : _color(C), _x(X), _y(Y), _z(Z), _w(W){}
	Vector(const float &X, const float &Y, const float &Z, const float &W) : _x(X), _y(Y), _z(Z), _w(W){};
	Vector(const float &X, const float &Y, const float &Z, const float &W, const float &U, const float &V) : _x(X), _y(Y), _z(Z), _w(W), _u(U), _v(V) {};
	Vector(const Color &C) : _color(C){};
	Vector(const float &X) : _x(X){};
	void SetHomVec(Vector & vector);
	void Negate();
	void Normalize();
	Vector GetNormal(const Vector & vect);
	float GetMagnitude();
	float GetAngleBetween(const Vector & vect);
	float GetDotProduct(const Vector * vect);
	float GetDotProduct(const Vector & vect);
	float GetDotHom(Vector & vect);
	Vector SubtractHom(Vector & vector);
	Vector AddHom(Vector & vector);
	Vector ScaleHom(float & scale);
	Vector operator-(Vector & vector);
	Vector operator-=(Vector & vector);
	Vector operator*(float & scalar);
	Vector operator+(Vector & vector);
	Vector operator+=(Vector & vector);
	bool operator!=(const Vector & vector);
	bool operator==(const Vector & vector);
	void SetVec(float & X, float & Y, float & Z);
};
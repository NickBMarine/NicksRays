#pragma once
#include "Vector.h"
#include <vector>
using namespace std;

#define PI 3.14159265358

struct Matrix4x4
{
	float _11, _12, _13, _14,
		  _21, _22, _23, _24,
		  _31, _32, _33, _34,
		  _41, _42, _43, _44;

	Matrix4x4(float _11, float _12, float _13, float _14,
			  float _21, float _22, float _23, float _24,
			  float _31, float _32, float _33, float _34,
			  float _41, float _42, float _43, float _44);
	
	Matrix4x4(float _11, float _12, float _13,
			  float _21, float _22, float _23,
			  float _31, float _32, float _33);

	Matrix4x4() { Identity();};
	Matrix4x4 operator+(Matrix4x4 matrix);
	Vector GetTranslation() { return Vector(_41, _42, _43); };
	Vector GetRowThree() { return Vector(_31, _32, _33); };
	void XAxisRotation(float degrees);
	void YAxisRotation(float degrees);
	void ZAxisRotation(int degrees);
	void ArbAxisRotation(Vector &rotVert, int degrees);
	void Scale(float kx, float ky, float kz);
	//Needs work
	//void ScaleArb(Vertex& scaleVert, float k);
	void SetRowOne(Vector & v);
	void SetRowTwo(Vector & v);
	void SetRowThree(Vector & v);
	void SetPos(float x, float y, float z);
	void SetPos(const Vector& set);
	void Translation(float x, float y, float z);
	void Translation(const Vector &trans);
	void Transformation(vector<Vector> &vertex, int index);
	void Transformation(Vector & vector);
	void Transformation(Matrix4x4 matrix);
	void Identity();
	void SetMatrix(float _11, float _12, float _13, float _14,
			       float _21, float _22, float _23, float _24,
			       float _31, float _32, float _33, float _34,
				   float _41, float _42, float _43, float _44);
	
	void SetMatrix(float _11, float _12, float _13,
			       float _21, float _22, float _23,
			       float _31, float _32, float _33);
	void SetMatrix(Matrix4x4 matrix);
	void EulerRotation(const Vector & rot);
	void Scale(const Vector& scale);
	void Transpose();
	void Negate();
};
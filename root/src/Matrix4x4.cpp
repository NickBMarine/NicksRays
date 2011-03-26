#include "Matrix4x4.h"

Matrix4x4::Matrix4x4(float t_11, float t_12, float t_13, float t_14,
					 float t_21, float t_22, float t_23, float t_24,
					 float t_31, float t_32, float t_33, float t_34,
				     float t_41, float t_42, float t_43, float t_44)
{
	_11 = t_11;
	_12 = t_12;
	_13 = t_13;
	_14 = t_14;
	_21 = t_21;
	_22 = t_22;
	_23 = t_23;
	_24 = t_24;
	_31 = t_31;
	_32 = t_32;
	_33 = t_33;
	_34 = t_34;
	_41 = t_41;
	_42 = t_42;
	_43 = t_43;
	_44 = t_44;
}

void Matrix4x4::Transformation(vector<Vector> &vertex, int index)
{
	Vector tempVertex(vertex[index]._color, vertex[index]._x, vertex[index]._y, vertex[index]._z);

	vertex[index]._x = (_11 * tempVertex._x) + (_21 * tempVertex._y) + (_31 * tempVertex._z) + _41;
	vertex[index]._y = (_12 * tempVertex._x) + (_22 * tempVertex._y) + (_32 * tempVertex._z) + _42; 
	vertex[index]._z = (_13 * tempVertex._x) + (_23 * tempVertex._y) + (_33 * tempVertex._z) + _43;
	vertex[index]._w = (_14 * tempVertex._x) + (_24 * tempVertex._y) + (_34 * tempVertex._z) + (tempVertex._w *_44);
}

void Matrix4x4::Transformation(Vector &vector)
{
	Vector tempVertex(vector._color, vector._x, vector._y, vector._z, vector._w);

	vector._x = (_11 * tempVertex._x) + (_21 * tempVertex._y) + (_31 * tempVertex._z) + _41;
	vector._y = (_12 * tempVertex._x) + (_22 * tempVertex._y) + (_32 * tempVertex._z) + _42; 
	vector._z = (_13 * tempVertex._x) + (_23 * tempVertex._y) + (_33 * tempVertex._z) + _43;
	vector._w = (_14 * tempVertex._x) + (_24 * tempVertex._y) + (_34 * tempVertex._z) + (tempVertex._w * _44);
}

void Matrix4x4::Transformation(Matrix4x4 matrix)
{
	Matrix4x4 tempMatrix(_11, _12, _13, _14,
						 _21, _22, _23, _24,
						 _31, _32, _33, _34,
						 _41, _42, _43, _44);

	_11 = (tempMatrix._11 * matrix._11) + (tempMatrix._12 * matrix._21) + (tempMatrix._13 * matrix._31) + (tempMatrix._14 * matrix._41);
    _12 = (tempMatrix._11 * matrix._12) + (tempMatrix._12 * matrix._22) + (tempMatrix._13 * matrix._32) + (tempMatrix._14 * matrix._42);
	_13 = (tempMatrix._11 * matrix._13) + (tempMatrix._12 * matrix._23) + (tempMatrix._13 * matrix._33) + (tempMatrix._14 * matrix._43);
	_14 = (tempMatrix._11 * matrix._14) + (tempMatrix._12 * matrix._24) + (tempMatrix._13 * matrix._34) + (tempMatrix._14 * matrix._44);
	_21 = (tempMatrix._21 * matrix._11) + (tempMatrix._22 * matrix._21) + (tempMatrix._23 * matrix._31) + (tempMatrix._24 * matrix._41);
	_22 = (tempMatrix._21 * matrix._12) + (tempMatrix._22 * matrix._22) + (tempMatrix._23 * matrix._32) + (tempMatrix._24 * matrix._42);
	_23 = (tempMatrix._21 * matrix._13) + (tempMatrix._22 * matrix._23) + (tempMatrix._23 * matrix._33) + (tempMatrix._24 * matrix._43);
	_24 = (tempMatrix._21 * matrix._14) + (tempMatrix._22 * matrix._24) + (tempMatrix._23 * matrix._34) + (tempMatrix._24 * matrix._44);
	_31 = (tempMatrix._31 * matrix._11) + (tempMatrix._32 * matrix._21) + (tempMatrix._33 * matrix._31) + (tempMatrix._34 * matrix._41);
	_32 = (tempMatrix._31 * matrix._12) + (tempMatrix._32 * matrix._22) + (tempMatrix._33 * matrix._32) + (tempMatrix._34 * matrix._42);
  	_33 = (tempMatrix._31 * matrix._13) + (tempMatrix._32 * matrix._23) + (tempMatrix._33 * matrix._33) + (tempMatrix._34 * matrix._43);
	_34 = (tempMatrix._31 * matrix._14) + (tempMatrix._32 * matrix._24) + (tempMatrix._33 * matrix._34) + (tempMatrix._34 * matrix._44);
	_41 = (tempMatrix._41 * matrix._11) + (tempMatrix._42 * matrix._21) + (tempMatrix._43 * matrix._31) + (tempMatrix._44 * matrix._41);
	_42 = (tempMatrix._41 * matrix._12) + (tempMatrix._42 * matrix._22) + (tempMatrix._43 * matrix._32) + (tempMatrix._44 * matrix._42);
	_43 = (tempMatrix._41 * matrix._13) + (tempMatrix._42 * matrix._23) + (tempMatrix._43 * matrix._33) + (tempMatrix._44 * matrix._43);
	_44 = (tempMatrix._41 * matrix._14) + (tempMatrix._42 * matrix._24) + (tempMatrix._43 * matrix._34) + (tempMatrix._44 * matrix._44);
}

void Matrix4x4::Translation(float x, float y, float z)
{
	_41 =  x;
    _42 =  y;
	_43 =  z;
}

void Matrix4x4::Translation(const Vector& trans)
{
	_41 +=  trans._x;
    _42 +=  trans._y;
	_43 +=  trans._z;
}

void Matrix4x4::SetPos(float x, float y, float z)
{
	_41 = x;
	_42 = y;
	_43 = z;
}

void Matrix4x4::SetPos(const Vector& set)
{
	_41 = set._x;
	_42 = set._y;
	_43 = set._z;
}

void Matrix4x4::SetMatrix(float t_11, float t_12, float t_13, float t_14,
					      float t_21, float t_22, float t_23, float t_24,
					      float t_31, float t_32, float t_33, float t_34,
						  float t_41, float t_42, float t_43, float t_44)
{
	_11 = t_11;
	_12 = t_12;
	_13 = t_13;
	_14 = t_14;
	_21 = t_21;
	_22 = t_22;
	_23 = t_23;
	_24 = t_24;
	_31 = t_31;
	_32 = t_32;
	_33 = t_33;
	_34 = t_34;
	_41 = t_41;
	_42 = t_42;
	_43 = t_43;
	_44 = t_44;
}

void Matrix4x4::SetMatrix(float t_11, float t_12, float t_13,
					      float t_21, float t_22, float t_23,
					      float t_31, float t_32, float t_33)
{
	_11 = t_11;
	_12 = t_12;
	_13 = t_13;
	_21 = t_21;
	_22 = t_22;
	_23 = t_23;
	_31 = t_31;
	_32 = t_32;
	_33 = t_33;
}


void Matrix4x4::SetMatrix(Matrix4x4 matrix)
{
	_11 = matrix._11;
	_12 = matrix._12; 
	_13 = matrix._13;
	_14 = matrix._14;
	_21 = matrix._21;
	_22 = matrix._22; 
	_23 = matrix._23;
	_24 = matrix._24; 
	_31 = matrix._31;
	_32 = matrix._32;
	_33 = matrix._33;
	_34 = matrix._34; 
	_41 = matrix._41;
	_42 = matrix._42;
	_43 = matrix._43;
	_44 = matrix._44;
}

void Matrix4x4::Identity()
{
	_11 = 1.0f;
	_12 = 0.0f; 
	_13 = 0.0f;
	_14 = 0.0f;
	_21 = 0.0f;
	_22 = 1.0f; 
	_23 = 0.0f;
	_24 = 0.0f; 
	_31 = 0.0f;
	_32 = 0.0f;
	_33 = 1.0f;
	_34 = 0.0f; 
	_41 = 0.0f;
	_42 = 0.0f;
	_43 = 0.0f;
	_44 = 1.0f;
}

Matrix4x4::Matrix4x4(float t_11, float t_12, float t_13,
					 float t_21, float t_22, float t_23,
					 float t_31, float t_32, float t_33)
{
	_11 = t_11;
	_12 = t_12;
	_13 = t_13;
	_14 = 0.0f;
	_21 = t_21;
	_22 = t_22;
	_23 = t_23;
	_24 = 0.0f;
	_31 = t_31;
	_32 = t_32;
	_33 = t_33;
	_34 = 0.0f;
	_41 = 0.0f;
	_42 = 0.0f;
	_43 = 0.0f;
	_44 = 1.0f;
}

void Matrix4x4::XAxisRotation(float degrees)
{

	float radians = degrees * (float(PI)/180);

	Matrix4x4 matRotate(1.0f, 0.0f,         0.0f,
						0.0f, cos(radians), sin(radians),
						0.0f, -sin(radians),cos(radians));
	Transformation(matRotate);
}

void Matrix4x4::YAxisRotation(float degrees)
{

	float radians = degrees * (float(PI)/180);

	Matrix4x4 matRotate;
	matRotate.Identity();
	matRotate.SetMatrix(cos(radians), 0.0f, -sin(radians),
						0.0f,         1.0f, 0.0f,
						sin(radians), 0,    cos(radians));

	Transformation(matRotate);
}

void Matrix4x4::ZAxisRotation(int degrees)
{

	float radians = degrees * (float(PI)/180);

	Matrix4x4 matRotate(cos(radians),  sin(radians), 0.0f,
						-sin(radians), cos(radians), 0.0f,
						0.0f,          0.0f,         1.0f);

	Transformation(matRotate);
}


void Matrix4x4::ArbAxisRotation(Vector &rotVert, int degrees)
{
	float radians = degrees * (float(PI)/180);
	

	rotVert.Normalize();

	float xy = rotVert._x * rotVert._y;
	float xz = rotVert._x * rotVert._z;
	float yz = rotVert._y * rotVert._z;
	float xSq = rotVert._x * rotVert._x;
	float ySq = rotVert._y * rotVert._y;
	float zSq = rotVert._z * rotVert._z;
	float oneMincos = (1-cos(radians));

	Matrix4x4 matRotate;
	matRotate.Identity();

	matRotate._11 =  xSq * oneMincos + cos(radians);
	matRotate._12 =  xy * oneMincos + rotVert._z * sin(radians);
	matRotate._13 =	 xz * oneMincos - rotVert._y * sin(radians);
	matRotate._21 =  xy * oneMincos - rotVert._z * sin(radians);
	matRotate._22 =  ySq * oneMincos + cos(radians);
	matRotate._23 =  yz * oneMincos + rotVert._x * sin(radians);
	matRotate._31 =  xz * oneMincos + rotVert._y * sin(radians);
	matRotate._32 =  yz * oneMincos - rotVert._x * sin(radians);
	matRotate._33 =  zSq * oneMincos + cos(radians);

	Transformation(matRotate);
}

void Matrix4x4::Scale(float kx, float ky, float kz)
{
	Matrix4x4 scaleMat(kx,   0.0f, 0.0f,
					   0.0f, ky,   0.0f,
					   0.0f, 0.0f, kz);
	Transformation(scaleMat);

}

//Needs work
/*void Matrix4x4::ScaleArb(Vertex &scaleVert, float k)
{
	Vertex tempVert = scaleVert.Normalize();

	float kMinOne = (k - 1);
	float xSqrd = tempVert.x * tempVert.x;
	float ySqrd = tempVert.y * tempVert.y;
	float zSqrd = tempVert.z * tempVert.z;
	float xy    = tempVert.x * tempVert.y;
	float xz    = tempVert.x * tempVert.z;
	float yz    = tempVert.y * tempVert.z;

	Matrix4x4 scaleMat;
	scaleMat.Identity();

	scaleMat._11 = 1 + kMinOne * xSqrd;
	scaleMat._12 = kMinOne * xy;
	scaleMat._13 = kMinOne * xz;
	scaleMat._21 = kMinOne * xy;
	scaleMat._22 = 1 + kMinOne * ySqrd;
	scaleMat._23 = kMinOne * yz;
	scaleMat._31 = kMinOne * xz;
	scaleMat._32 = kMinOne * yz;
	scaleMat._33 = 1 + kMinOne * zSqrd;

	Transformation(scaleMat);
}*/

void Matrix4x4::Transpose()
{
	SetMatrix(_11, _21, _31, _41,
			  _12, _22, _32, _42,
			  _13, _23, _33, _43,
			  _14, _24, _34, _44);

}

Matrix4x4 Matrix4x4::operator+(Matrix4x4 matrix)
{
	Matrix4x4 tempMatrix;

	tempMatrix._11 = _11 + matrix._11;
	tempMatrix._12 = _12 + matrix._12;
	tempMatrix._13 = _13 + matrix._13;
	tempMatrix._14 = _14 + matrix._14;
	tempMatrix._21 = _21 + matrix._21;
	tempMatrix._22 = _22 + matrix._22;
	tempMatrix._23 = _23 + matrix._23;
	tempMatrix._24 = _24 + matrix._24;
	tempMatrix._31 = _31 + matrix._31;
	tempMatrix._32 = _32 + matrix._32;
	tempMatrix._33 = _33 + matrix._33;
	tempMatrix._34 = _34 + matrix._34;
	tempMatrix._41 = _41 + matrix._41;
	tempMatrix._42 = _42 + matrix._42;
	tempMatrix._43 = _43 + matrix._43;
	tempMatrix._44 = _44 + matrix._44;

	return tempMatrix;
}

void Matrix4x4::Negate()
{
	this->SetMatrix(-_11, -_12, -_13, -_14,
					-_21, -_22, -_23, -_24,
					-_31, -_32, -_33, -_34,
					-_41, -_42, -_43, -_44);
}

void Matrix4x4::EulerRotation(const Vector &rot)
{
	float radiansX = rot._x * (float(PI)/float(180));
	float radiansY = rot._y * (float(PI)/float(180));
	float radiansZ = rot._z * (float(PI)/float(180));

	Matrix4x4 matRotateX;
	matRotateX.SetMatrix(1.0f, 0.0f,         0.0f,
						0.0f, cos(radiansX), sin(radiansX),
						0.0f, -sin(radiansX),cos(radiansX));

	Matrix4x4 matRotateY; 
	matRotateY.SetMatrix(cos(radiansY), 0.0f, -sin(radiansY),
						0.0f,         1.0f, 0.0f,
						sin(radiansY), 0,    cos(radiansY));
	
	Matrix4x4 matRotateZ; 
	matRotateZ.SetMatrix(cos(radiansZ),  sin(radiansZ), 0.0f,
						-sin(radiansZ), cos(radiansZ), 0.0f,
						0.0f,          0.0f,         1.0f);

	matRotateZ.Transformation(matRotateX);
	matRotateZ.Transformation(matRotateY);

	Transformation(matRotateZ);
}

void Matrix4x4::Scale(const Vector &scale)
{
	this->SetMatrix(scale._x, _12,     _13,     _14,
					_21,     scale._y, _23,     _24,
					_31,     _32,     scale._z, _34,
					_41,     _42,     _43,     _44);
}

void Matrix4x4::SetRowOne(Vector & v)
{
	_11 = v._x;
	_12 = v._y;
	_13 = v._z;
}

void Matrix4x4::SetRowTwo(Vector & v)
{
	_21 = v._x;
	_22 = v._y;
	_23 = v._z;
}

void Matrix4x4::SetRowThree(Vector & v)
{
	_31 = v._x;
	_32 = v._y;
	_33 = v._z;
}

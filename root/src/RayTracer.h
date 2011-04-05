#pragma once
#include "PixelToaster.h"
#include "Ray.h"
#include "Plane.h"
#include "Sphere.h"
#include "Matrix4x4.h"
#include "Quad.h"
#include "Vector.h"
#include "Camera.h"
#include "Light.h"
#include <iostream>
using namespace PixelToaster;

class RayTracer
{
	Camera _camera;
	std::vector<Pixel> _pixels;
	std::vector<float> _tBuffer;
	Ray _ray;
	Light _light;
	bool _dirty;
	int _width;
	int _height;
	float _aspect;
	Color _background;
	Pixel TraceRay(Plane & p, int index);
	Pixel TraceRay(Sphere & s, int index);
	Pixel TraceRay(Quad & q, int index);
public: 
	RayTracer(int width, int height, Color background);
	~RayTracer(){};
	
	void SetPointLight(Light l) { _light = l;};
	void SetBackground(Color background){ _background = background;};
	void SetWidth(int width) { _width;};
	void SetHeight(int height) { _height;};
	void SetCamera(Vector upVec, Vector forwardVec, Vector sideVec);
	Vector ComputeVector(float scalar);
	void RefreshTBuff();
	std::vector<Pixel> FetchPixels() { return _pixels; }
	void RayCast(Plane & p);
	void RayCast(Sphere & s);
	void RayCast(Quad & q);
	void RefreshPixels();
};
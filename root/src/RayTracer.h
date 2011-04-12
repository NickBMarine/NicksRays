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
	std::vector<Plane> _planes;
	std::vector<Sphere> _spheres;
	std::vector<Quad> _quads;
	int _numSpheres;
	int _numPlanes;
	int _numQuads;
	int _numSurfaces;
	Ray _ray;
	Light _light;
	bool _dirty;
	int _width;
	int _height;
	float _aspect;
	Color _background;
	void TraceRay(Plane & p, Ray & r, Color & c, float & t);
	void TraceRay(Sphere & s, Ray & r, Color & c, float & t);
	void TraceRay(Quad & q, Ray & r, Color & c, float & t);
	void TraceLightRay(Plane & p, Ray & r, float & t);
	void TraceLightRay(Sphere & s, Ray & r, float & t);
	void TraceLightRay(Quad & q, Ray & r, float & t);
	void FindTtoLight(Ray & r);
	void RayCast(int index);
	Vector ComputePoint(float t);
	Ray ComputeRay(Vector & orig, Vector & dir);
public: 
	RayTracer(int width, int height, Color background);
	~RayTracer(){};
	
	void AddSurface(Sphere & sphere);
	void AddSurface(Quad & quad);
	void AddSurface(Plane & plane);
	void SetPointLight(Light l) { _light = l;};
	void SetBackground(Color background){ _background = background;};
	void SetWidth(int width) { _width;};
	void SetHeight(int height) { _height;};
	void SetCamera(Vector upVec, Vector forwardVec, Vector sideVec);
	Vector ComputeVector(float scalar);
	void RefreshTBuff();
	std::vector<Pixel> FetchPixels() { return _pixels; }
	void CreateScene();
	void RefreshPixels();
};
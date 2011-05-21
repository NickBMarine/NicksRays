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
#include "ThreadContainer.h"
#include <iostream>
using namespace PixelToaster;

class RayTracer
{
	int _numThreads;
	int _yBegin, _yEnd;
	int _width, _height;
	int _yCoordIndex;
	ThreadContainer * _threads;
	HANDLE * _arrayofThreadHandles;
	//std::vector<int> _yCoords;
	Camera _camera;
	std::vector<Pixel> _pixels;
	std::vector<float> _tBuffer;
	std::vector<Plane> _planes;
	std::vector<Quad> _quads;
	int _numSpheres;
	int _numPlanes;
	int _numQuads;
	int _numSurfaces;
	Ray _ray;
	Light _light;
	bool _dirty;
	bool _createScene;
	float _aspect;
	Color _background;
	void TraceRay(Plane & p, Ray & r, Color & c, float & t);
	void TraceRay(Sphere & s, Ray & r, Color & c, float & t);
	void TraceRay(Quad & q, Ray & r, Color & c, float & t);
	void TraceLightRay(Plane & p, Ray & r, float & t);
	void TraceLightRay(Sphere & s, Ray & r, float & t);
	void TraceLightRay(Quad & q, Ray & r, float & t);
	void ReflectedRay(Plane & p, Ray & r, float & t, Color & c);
	void TraceRefToLight(Sphere & s, Ray & r, float & t);
	void ReflectedRay(Sphere & s, Ray & r, float & t, Color & c);
	void ReflectedRay(Quad & q, Ray & r, float & t, Color & c);
	void FindTtoLight(Ray & r);
	void CreateThreadHandles();
	Color RayCast(float & t, Ray & ray);
	Vector ComputePoint(Ray & ray, float t);
	Ray ComputeRay(Vector & orig, Vector & dir);
public: 
	bool _done;
	std::vector<Sphere> _spheres;
	RayTracer(){};
	~RayTracer();
	RayTracer(int width, int height, Color background);
	
	void RefreshThreadOrder();
	bool SceneReady();
	void SetThreads(int num) { _numThreads = num; CreateThreadHandles();}
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
	void Merge(RayTracer []);
	friend DWORD WINAPI Thread(LPVOID lpParam);
};
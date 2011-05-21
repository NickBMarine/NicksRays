class RayTracer;
struct ThreadContainer
{
	float _yBegin, _yEnd;
	float _width, _height;
	Ray _ray;
	RayTracer * _rayTrace;
	bool _sceneCheck;
};
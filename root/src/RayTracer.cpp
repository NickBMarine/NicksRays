#include "RayTracer.h"

RayTracer::RayTracer(int width, int height, Color background)
{
	_width = width;
	_height = height;
	_dirty = true;
	_aspect = (float(_width)/float(_height));
	_background = background;
	_camera.SetCameraForward(Vector(0,0,1));
	_camera.SetCameraRight(Vector(1, 0, 0));
	_camera.SetCameraUp(Vector(0,1,0));
	_camera.SetCameraSpeed(0.1f);
	_pixels.resize(width * height);
	_tBuffer.resize(width * height);
	RefreshTBuff();
	_ray._x0 = 0.0f;
	_ray._y0 = 0.0f;
	_ray._z0 = 0.0f;
}

void RayTracer::RayCast(Plane & p)
{
	int index;
	float Sx = 2.0f/float(_width);
	float Sy = 2.0f/-float(_height);
	float Dx = -1.0f;
	float Dy = 1.0f;
	for (int y = 0; y < _height; y++)
	{
		for (int x = 0; x < _width; x++)
		{
			float tempX = x * Sx + Dx;
			float tempY = y * Sy + Dy;
			tempX *= _aspect;
			_ray._a = tempX;
			_ray._b = tempY;
			_ray._c = 1.0f;
			index = x + (y * _width);

			_pixels[index] = TraceRay(p, index);
		}
	}
}

Pixel RayTracer::TraceRay(Plane & p, int index)
{	
	_ray._t = -(p._A * _ray._x0 + p._B * _ray._y0 + p._C * _ray._z0 + p._D)
			   /(p._A * _ray._a + p._B * _ray._b + p._C * _ray._c);
	
	if ( _ray._t < 0.0f )
		return _pixels[index];

	else if ( _ray._t < _tBuffer[index])
	{
		_tBuffer[index] = _ray._t;
		return Pixel(p._color._r, p._color._g, p._color._b);
	}
	else
		return _pixels[index];
}

void RayTracer::RayCast(Sphere & s)
{
	int index;
	float Sx = 2.0f/float(_width);
	float Sy = 2.0f/-float(_height);
	float Dx = -1.0f;
	float Dy = 1.0f;
	for (int y = 0; y < _height; y++)
	{
		for (int x = 0; x < _width; x++)
		{
			float tempX = x * Sx + Dx;
			float tempY = y * Sy + Dy;
			tempX *= _aspect;
			_ray._a = tempX;
			_ray._b = tempY;
			_ray._c = 1.0f;
			index = x + (y * _width);

			_pixels[index] = TraceRay(s, index);
		}
	}
}

Pixel RayTracer::TraceRay(Sphere & s, int index)
{
	float a = (pow(_ray._a, 2) + pow(_ray._b, 2) + (pow(_ray._c, 2)));
	float b = (2 * _ray._a * ( _ray._x0 - s._x0) + 2 * _ray._b * (_ray._y0 - s._y0) + 2 * _ray._c * (_ray._z0 - s._z0));
	float c = ( pow(_ray._x0 - s._x0, 2) + pow(_ray._y0 - s._y0, 2) + pow(_ray._z0 - s._z0, 2) - pow(s._r, 2));
	float disc = sqrt(pow(b,2) -( 4 * a * c));

	if ( disc < 0 )
		return _pixels[index];
	else
	{
		float tTemp = min((-b + sqrt(pow(b,2) - (4 * a * c)) / (2 * a)), (-b - sqrt(pow(b,2) - (4 * a * c)) / (2 * a)));
		if ( tTemp < _tBuffer[index] )
		{
			_tBuffer[index] = tTemp;
			return Pixel(s._color._r, s._color._g, s._color._b);
		}
		else
			return _pixels[index];
	}

}

void RayTracer::RefreshTBuff()
{
	int size = _tBuffer.size();
	for (int i = 0; i < size; i++)
	{
		_tBuffer[i] = 1.0f;
	}
}

void RayTracer::RefreshPixels()
{
	int size  = _tBuffer.size();
	for ( int i = 0; i < size; i++)
	{
		_pixels[i] = Pixel(_background._r, _background._g, _background._b);
	}

}


#include "RayTracer.h"

RayTracer::RayTracer(int width, int height, Color background)
{
	_width = width;
	_height = height;
	_dirty = true;
	_aspect = (float(_width)/float(_height));
	_light._color = Color(1.0f, 1.0f, 1.0f);
	_light._intensity = 1.0f;
	_light._point = Vector(0.0f, 0.75f, 2.5f);
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
	_ray._c = 2.41f;
	for (int y = 0; y < _height; y++)
	{
		for (int x = 0; x < _width; x++)
		{
			float tempX = x * Sx + Dx;
			float tempY = y * Sy + Dy;
			tempX *= _aspect;
			_ray._a = tempX;
			_ray._b = tempY;
			index = x + (y * _width);

			_pixels[index] = TraceRay(p, index);
		}
	}
}

Pixel RayTracer::TraceRay(Plane & p, int index)
{	
	_ray._t = -(p._A * _ray._x0 + p._B * _ray._y0 + p._C * _ray._z0 + p._D)
			   /(p._A * _ray._a + p._B * _ray._b + p._C * _ray._c);
	
	Vector tempVec = ComputeVector(_ray._t);
	Vector pointToLight = _light._point - tempVec;
	float pointToLightMag = pointToLight.GetMagnitude();
	float atten = (1.0f / pow(pointToLightMag, 2));
	pointToLight.Normalize();
	Vector surfaceNorm = Vector(p._A, p._B, p._C);
	surfaceNorm.Normalize();

	float dot = min(1, max(pointToLight.GetDotProduct(surfaceNorm), 0));



	Color lightColor = dot * _light._color * _light._intensity * p._color * atten;

	if ( _ray._t < 0.0f )
		return _pixels[index];

	else if ( _ray._t < _tBuffer[index])
	{
		_tBuffer[index] = _ray._t;
		//return Pixel(p._color._r, p._color._g, p._color._b);
		return Pixel(lightColor._r, lightColor._g, lightColor._b);
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
	_ray._c = 2.41f;
	for (int y = 0; y < _height; y++)
	{
		for (int x = 0; x < _width; x++)
		{
			float tempX = x * Sx + Dx;
			float tempY = y * Sy + Dy;
			tempX *= _aspect;
			_ray._a = tempX;
			_ray._b = tempY;
			index = x + (y * _width);

			_pixels[index] = TraceRay(s, index);
		}
	}
}

Pixel RayTracer::TraceRay(Sphere & s, int index)
{
	float a = (pow(_ray._a, 2) + pow(_ray._b, 2) + (pow(_ray._c, 2)));
	float b = 2 * (_ray._a * ( _ray._x0 - s._x0) + _ray._b * (_ray._y0 - s._y0) + _ray._c * (_ray._z0 - s._z0));
	float c = ( pow(_ray._x0 - s._x0, 2) + pow(_ray._y0 - s._y0, 2) + pow(_ray._z0 - s._z0, 2) - pow(s._r,2));
	float disc = pow(b,2) -( 4 * a * c);


	if ( disc < 0 )
		return _pixels[index];
	else
	{
		float tTemp = min((-b + sqrt(disc)) / (2 * a), (-b - sqrt(disc)) / (2 * a));

		Vector tempVec = ComputeVector(tTemp);
		Vector pointToLight = _light._point - tempVec;
		float pointToLightMag = pointToLight.GetMagnitude();
		float atten = (1.0f / pow(pointToLightMag, 2));
		pointToLight.Normalize();
		Vector surfaceNorm = tempVec - Vector(s._x0, s._y0, s._z0);
		surfaceNorm.Normalize();

		float dot = min(1, max(pointToLight.GetDotProduct(surfaceNorm), 0));

		Color lightColor = dot * _light._color * _light._intensity * s._color * atten;

		if ( tTemp < _tBuffer[index] )
		{
			_tBuffer[index] = tTemp;
			return Pixel(lightColor._r, lightColor._g, lightColor._b);
		}
		else
			return _pixels[index];
	}

}

void RayTracer::RayCast(Quad & q)
{
	int index;
	float Sx = 2.0f/float(_width);
	float Sy = 2.0f/-float(_height);
	float Dx = -1.0f;
	float Dy = 1.0f;
	_ray._c = 2.41f;
	for (int y = 0; y < _height; y++)
	{
		for (int x = 0; x < _width; x++)
		{
			float tempX = x * Sx + Dx;
			float tempY = y * Sy + Dy;
			tempX *= _aspect;
			_ray._a = tempX;
			_ray._b = tempY;
			index = x + (y * _width);

			_pixels[index] = TraceRay(q, index);
		}
	}
}

Pixel RayTracer::TraceRay(Quad & q, int index)
{
	Vector b1 = q._b1 - q._b0;
	Vector b2 = q._b2 - q._b0;

	b1.Normalize();
	b2.Normalize();

	Vector normal = b2.GetNormal(b1);

	Plane tempPlane;
	tempPlane._A = normal._x;
	tempPlane._B = normal._y;
	tempPlane._C = normal._z;
	tempPlane._D = -(normal.GetDotProduct(q._b0));

	_ray._t = -(tempPlane._A * _ray._x0 + tempPlane._B * _ray._y0 + tempPlane._C * _ray._z0 + tempPlane._D)
			   /(tempPlane._A * _ray._a + tempPlane._B * _ray._b + tempPlane._C * _ray._c);

	Vector tempVector = ComputeVector(_ray._t);
	Vector pointToLight = _light._point - tempVector;
	float pointToLightMag = pointToLight.GetMagnitude();
    float atten = (1.0f / pow(pointToLightMag, 2));
	pointToLight.Normalize();
	Vector surfaceNorm = Vector(tempPlane._A, tempPlane._B, tempPlane._C);
	surfaceNorm.Normalize();

	float dot = min(1, max(pointToLight.GetDotProduct(surfaceNorm), 0));

	Color lightColor = dot * _light._color * _light._intensity * Color(1.0f, 1.0f, 1.0f) * atten;



	float tempX = _ray._x0 + _ray._t * _ray._a;
	float tempY = _ray._y0 + _ray._t * _ray._b;
	float tempZ = _ray._z0 + _ray._t * _ray._c;

	Vector tempPoint(tempX, tempY, tempZ);

	Vector tempVec = tempPoint - q._b0;

	if ( _ray._t < _tBuffer[index] && _ray._t > 0.0f )
	{
		if ( !q._grid)
		{
			if (tempVec.GetDotProduct(b1) <= q._width && tempVec.GetDotProduct(b2) <= q._height
				&& tempVec.GetDotProduct(b1) > 0.0f && tempVec.GetDotProduct(b2) > 0.0f)
			{
				_tBuffer[index] = _ray._t;
				return (Pixel(lightColor._r, lightColor._g, lightColor._b));
			}
			else
				return (_pixels[index]);
		}
		else
		{
			if (tempVec.GetDotProduct(b1) <= q._width && tempVec.GetDotProduct(b2) <= q._height
				&& tempVec.GetDotProduct(b1) > 0.0f && tempVec.GetDotProduct(b2) > 0.0f)
			{
				_tBuffer[index] = _ray._t;
				float tempPercent1 = tempVec.GetDotProduct(b1);
				float tempPercent2 = tempVec.GetDotProduct(b2);
				tempPercent1 = tempPercent1/q._width;
				tempPercent2 = tempPercent2/q._height;

				int whole1 = tempPercent1 * 10;
				int whole2 = tempPercent2 * 10;

				if (whole1 == 10)
					whole1 = 9;
				if (whole2 == 10)
					whole2 = 9;

				if (whole1 == 0 && whole2 == 0)
				{
					//return Pixel(1.0f, 1.0f, 1.0f);
					return Pixel(lightColor._r, lightColor._g, lightColor._b);
				}
				else if ( (whole1 % 2) == 0)
				{
					if ( (whole2 % 2) == 0)
					{
						return Pixel(0.0f, 0.0f, 0.0f);
					}
					//return Pixel(1.0f, 1.0f, 1.0f);
					return Pixel(lightColor._r, lightColor._g, lightColor._b);
				}
				else 
				{
					if ( (whole2 % 2) == 0)
						//return Pixel(1.0f, 1.0f, 1.0f);
						return Pixel(lightColor._r, lightColor._g, lightColor._b);
					return Pixel(0.0f, 0.0f, 0.0f);
				}
			}
			return _pixels[index];
		}
	}
	else
		return (_pixels[index]);

}

void RayTracer::RefreshTBuff()
{
	int size = _tBuffer.size();
	for (int i = 0; i < size; i++)
	{
		_tBuffer[i] = 5.0f;
	}
}

void RayTracer::RefreshPixels()
{
	int size  = _tBuffer.size();
	for ( int i = 0; i < size; i++)
	{
		_pixels[i] = Pixel(_background._r, _background._g, _background._b);
		_tBuffer[i] = 5.0f;
	}

}

Vector RayTracer::ComputeVector(float scalar)
{
	float x = _ray._x0 + scalar * _ray._a;
	float y = _ray._y0 + scalar * _ray._b;
	float z = _ray._z0 + scalar * _ray._c;

	return (Vector(x, y, z));
}
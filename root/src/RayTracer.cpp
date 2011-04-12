#include "RayTracer.h"

RayTracer::RayTracer(int width, int height, Color background)
{
	_width = width;
	_height = height;
	_numSurfaces = 0;
	_numPlanes = 0;
	_numQuads = 0;
	_numSpheres = 0;
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

void RayTracer::CreateScene()
{
	int index;
	float Sx = 2.0f/float(_width);
	float Sy = 2.0f/-float(_height);
	float Dx = -1.0f;
	float Dy = 1.0f;
	_ray._c = 2.41;
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

			RayCast(index);
		}
	}	
}

void RayTracer::RayCast(int index)
{
	Color tempColor = _background;
	float tempT = _tBuffer[index];
	Ray tempRay = _ray;
	if (_numSurfaces != 0)
	{
		//First check to see if the camera rays hits anything
		for (int i = 0; i < _numSpheres; i++)
		{
			TraceRay(_spheres[i], tempRay, tempColor, tempT);
		}

		for (int i = 0; i < _numQuads; i++)
		{
			TraceRay(_quads[i], tempRay, tempColor, tempT);
		}

		for (int i = 0; i < _numPlanes; i++)
		{
			TraceRay(_planes[i], tempRay, tempColor, tempT);
		}

	    _tBuffer[index] = tempT;
	    _pixels[index] = Pixel(tempColor._r, tempColor._g, tempColor._b);

		Vector vecToLight = _light._point - ComputeVector(tempT);
		float dToLight = vecToLight.GetMagnitude();
		vecToLight.Normalize();
		Ray tempRay = ComputeRay(ComputeVector(tempT), vecToLight);
		tempRay._t = dToLight;

		//Now lets see if an object is blocking the light of another
		for (int i = 0; i < _numSpheres; i++)
		{
			TraceLightRay(_spheres[i], tempRay, dToLight);
		}

		for (int i = 0; i < _numQuads; i++)
		{
			TraceLightRay(_quads[i], tempRay, dToLight);
		}

		for (int i = 0; i < _numPlanes; i++)
		{
			TraceLightRay(_planes[i], tempRay, dToLight);
		}

		if ( tempRay._t < dToLight)
		{
			_pixels[index] = Pixel(0.0f, 0.0f, 0.0f);
		}
	}
	else
		return;


}

void RayTracer::TraceLightRay(Plane & p, Ray & r, float & t)
{
	float tempT;
	tempT = -(p._A * r._x0 + p._B * r._y0 + p._C * r._z0 + p._D)
			   /(p._A * r._a + p._B * r._b + p._C * r._c);
	if (tempT <= 0)
		return;
	if (tempT < t)
		r._t = tempT;
}

void RayTracer::TraceLightRay(Sphere & s, Ray & r, float & t)
{
	float a = (pow(r._a, 2) + pow(r._b, 2) + (pow(r._c, 2)));
	float b = 2 * (r._a * ( r._x0 - s._x0) + r._b * (r._y0 - s._y0) + r._c * (r._z0 - s._z0));
	float c = ( pow(r._x0 - s._x0, 2) + pow(r._y0 - s._y0, 2) + pow(r._z0 - s._z0, 2) - pow(s._r,2));
	float disc = pow(b,2) - ( 4 * a * c);

	if (disc < 0)
		return;

	float tTemp = min((-b + sqrt(disc)) / (2 * a), (-b - sqrt(disc)) / (2 * a));

	if (tTemp <= 0)
		return;


	if (tTemp < t)
		r._t = tTemp;
}

void RayTracer::TraceLightRay(Quad & q, Ray & r, float & t)
{
	float tempT;
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

	tempT = -(tempPlane._A * r._x0 + tempPlane._B * r._y0 + tempPlane._C * r._z0 + tempPlane._D)
			   /(tempPlane._A * r._a + tempPlane._B * r._b + tempPlane._C * r._c);

	if (tempT <= 0)
		return;

	if (tempT < t)
		r._t = t;
}

void RayTracer::TraceRay(Plane & p, Ray & r, Color & col, float & t)
{	
	r._t = -(p._A * r._x0 + p._B * r._y0 + p._C * r._z0 + p._D)
			   /(p._A * r._a + p._B * r._b + p._C * r._c);
	
	Vector tempVec = ComputeVector(r._t);
	Vector pointToLight = _light._point - tempVec;
	float pointToLightMag = pointToLight.GetMagnitude();
	float atten = (1.0f / pow(pointToLightMag, 2));
	pointToLight.Normalize();
	Vector surfaceNorm = Vector(p._A, p._B, p._C);
	surfaceNorm.Normalize();

	float dot = min(1, max(pointToLight.GetDotProduct(surfaceNorm), 0));



	Color lightColor = dot * _light._color * _light._intensity * p._color * atten;


	if ( r._t <= 0.0f )
		return;

	else if ( r._t < t)
	{
		t = r._t;
		col = lightColor;
		return;
	}
	else
		return;
}

void RayTracer::TraceRay(Sphere & s, Ray & r, Color & col, float & t)
{
	float a = (pow(r._a, 2) + pow(r._b, 2) + (pow(r._c, 2)));
	float b = 2 * (r._a * ( r._x0 - s._x0) + r._b * (r._y0 - s._y0) + r._c * (r._z0 - s._z0));
	float c = ( pow(r._x0 - s._x0, 2) + pow(r._y0 - s._y0, 2) + pow(r._z0 - s._z0, 2) - pow(s._r,2));
	float disc = pow(b,2) - ( 4 * a * c);


	if ( disc < 0 )
		return;
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

		if ( tTemp < t )
		{
			t = tTemp;
			col = lightColor;
		}
		else
			return;
	}

}

void RayTracer::TraceRay(Quad & q, Ray & r, Color & col, float & t)
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

	r._t = -(tempPlane._A * r._x0 + tempPlane._B * r._y0 + tempPlane._C * r._z0 + tempPlane._D)
			   /(tempPlane._A * r._a + tempPlane._B * r._b + tempPlane._C * r._c);

	Vector tempVector = ComputeVector(r._t);
	Vector pointToLight = _light._point - tempVector;
	float pointToLightMag = pointToLight.GetMagnitude();
    float atten = (1.0f / pow(pointToLightMag, 2));
	pointToLight.Normalize();
	Vector surfaceNorm = Vector(tempPlane._A, tempPlane._B, tempPlane._C);
	surfaceNorm.Normalize();

	float dot = min(1, max(pointToLight.GetDotProduct(surfaceNorm), 0));

	Color lightColor = dot * _light._color * _light._intensity * Color(1.0f, 1.0f, 1.0f) * atten;



	float tempX = r._x0 + r._t * r._a;
	float tempY = r._y0 + r._t * r._b;
	float tempZ = r._z0 + r._t * r._c;

	Vector tempPoint(tempX, tempY, tempZ);

	Vector tempVec = tempPoint - q._b0;

	if ( r._t < t && r._t > 0.0f )
	{
		if ( !q._grid)
		{
			if (tempVec.GetDotProduct(b1) <= q._width && tempVec.GetDotProduct(b2) <= q._height
				&& tempVec.GetDotProduct(b1) > 0.0f && tempVec.GetDotProduct(b2) > 0.0f)
			{
				t = r._t;
				col = lightColor;
				return;
			}
			else
				return;
		}
		else
		{
			if (tempVec.GetDotProduct(b1) <= q._width && tempVec.GetDotProduct(b2) <= q._height
				&& tempVec.GetDotProduct(b1) > 0.0f && tempVec.GetDotProduct(b2) > 0.0f)
			{
				t = r._t;
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
					col = lightColor;
					return;
				}
				else if ( (whole1 % 2) == 0)
				{
					if ( (whole2 % 2) == 0)
					{
						col = Color(0.0f, 0.0f, 0.0f);
						return;
					}
					col = lightColor;
					return;
				}
				else 
				{
					if ( (whole2 % 2) == 0)
					{
						col = lightColor;
						return;
					}
					col = Color(0.0f, 0.0f, 0.0f);
					return;
				}
			}
			return;
		}
	}
	else
		return;

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

Ray RayTracer::ComputeRay(Vector & orig, Vector & dir)
{
	Ray tempRay;
	tempRay._x0 = orig._x;
	tempRay._y0 = orig._y;
	tempRay._z0 = orig._z;
	tempRay._a = dir._x;
	tempRay._b = dir._y;
	tempRay._c = dir._z;
	return tempRay;
}

void RayTracer::AddSurface(Sphere & sphere)
{
	_spheres.push_back(sphere);
	_numSpheres++;
	_numSurfaces++;
}

void RayTracer::AddSurface(Quad & quad)
{
	_quads.push_back(quad);
	_numQuads++;
	_numSurfaces++;
}

void RayTracer::AddSurface(Plane & plane)
{
	_planes.push_back(plane);
	_numPlanes++;
	_numSurfaces++;
}
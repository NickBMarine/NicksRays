#include "MultiThreading.h"


DWORD WINAPI Thread(LPVOID lpParam)
{
	int index;
	RayTracer * rays = ((RayTracer*)lpParam);
	float yBegin = rays->_yBegin;
	float yEnd = rays->_yEnd;
	float Sx = 2.0f/float(rays->_width);
	float Sy = 2.0f/-float(rays->_height);
	float Dx = -1.0f;
	float Dy = 1.0f;
	rays->_ray._c = 2.41;
	Color cTemp;

	for (int y = yBegin; y < yEnd; y++)
	{
		for (int x = 0; x < rays->_width; x++)
		{
			float tempX = x * Sx + Dx;
			float tempY = y * Sy + Dy;
			tempX *= rays->_aspect;
			rays->_ray._a = tempX;
			rays->_ray._b = tempY;
			index = x + (y * rays->_width);

			cTemp = rays->RayCast(rays->_tBuffer[index], rays->_ray);
			rays->_pixels[index] = Pixel(cTemp._r, cTemp._g, cTemp._b);
		}
	}

	return 0;
}



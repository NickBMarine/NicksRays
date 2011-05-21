#include "MultiThreading.h"

DWORD WINAPI Thread(LPVOID lpParam)
{
	int index;
	ThreadContainer * container = ((ThreadContainer*)lpParam);
	int yBegin = (int)container->_yBegin;
	int yEnd = (int)container->_yEnd;
	float Sx = 2.0f/float(container->_width);
	float Sy = 2.0f/-float(container->_height);
	float Dx = -1.0f;
	float Dy = 1.0f;
	container->_ray._c = 2.41f;
	Color cTemp;

	while (!container->_rayTrace->_done)
	{
		while (container->_sceneCheck)
		{
			for (int y = yBegin; y < yEnd; y++)
			{
				for (int x = 0; x < container->_width; x++)
				{
					float tempX = (float)x * Sx + Dx;
					float tempY = (float)y * Sy + Dy;
					tempX *= container->_rayTrace->_aspect;
					container->_ray._a = tempX;
					container->_ray._b = tempY;
					index = x + (int)(y * container->_width);
					cTemp = container->_rayTrace->RayCast(container->_rayTrace->_tBuffer[index], container->_ray);
					container->_rayTrace->_pixels[index] = Pixel(cTemp._r, cTemp._g, cTemp._b);
				}
			}
			container->_sceneCheck = false;
		}
	}

	return 0;
}



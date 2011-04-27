#include "PixelToaster.h"
#include "RayTracer.h"
#include <Windows.h>

using namespace PixelToaster;

unsigned short Camera::numCameras = 0;

int main()
{
    const int width = 800;
    const int height = 600;

	Color background(1.0f, 1.0f, 1.0f);
	RayTracer rayTrace(width, height, background);
	rayTrace.SetThreads(4);

	Display display( "Floating Point Example", width, height );

	Plane plane1;
	plane1._A = 1.0f;
	plane1._B = 0.0f;
	plane1._C = 0.0f;
	plane1._D = 1.0f;
	plane1._color = Color(1.0f, 0.0f, 0.0f);
	Plane plane2;
	plane2._A = -1.0f;
	plane2._B = 0.0f;
	plane2._C = 0.0f;
	plane2._D = 1.0f;
	plane2._color = Color(0.0f, 1.0f, 0.0f);
	Plane plane3;
	plane3._A = 0.0f;
	plane3._B = 0.0f;
	plane3._C = -1.0f;
	plane3._D = 4.0f;
	plane3._color = Color(0.0f, 0.5f, 0.5f);
	Plane plane4;
	plane4._A = 0.0f;
	plane4._B = -1.0f;
	plane4._C = 0.0f;
	plane4._D = 1.0f;
	plane4._color = Color(0.0f, 0.0f, 1.0f);
	Plane plane5;
	plane5._A = 0.0f;
	plane5._B = 0.0f;
	plane5._C = 1.0f;
	plane5._D = -1.0f;
	plane5._color = Color(0.5f, 0.5f, 1.0f);
	Sphere sphere1;
	sphere1._r = 0.3f;
	sphere1._x0 = -0.4f;
	sphere1._y0 = -0.2f;
	sphere1._z0 = 3.0f;
	sphere1._color = Color(1.0f, 0.0f, 1.0f);
	sphere1._reflective = true;
	sphere1._reflectiveDistance = 5.0f;
	Sphere sphere2;
	sphere2._r = 0.3f;
	sphere2._x0 = 0.2f;
	sphere2._y0 = -0.1f;
	sphere2._z0 = 2.0f;
	sphere2._color = Color(1.0f, 1.0f, 0.0f);
	sphere2._reflective = false;
	sphere2._reflectiveDistance = 10.0f;
	Quad quad1;
	quad1._b0 = Vector(-1.0f, -0.5f, -5.0f);
	quad1._b1 = Vector(1.0f, -0.5f, -5.0f);
	quad1._b2 = Vector(-1.0f, -0.5f, 5.0f);
	quad1._height = 10.0f;
	quad1._width = 8.0f;
	quad1._color = Color(1.0f, 1.0f, 0.0f);
	quad1._grid = true;

	rayTrace.AddSurface(plane1);
	rayTrace.AddSurface(plane2);
	rayTrace.AddSurface(plane3);
	rayTrace.AddSurface(plane4);
	rayTrace.AddSurface(plane5);
	rayTrace.AddSurface(sphere1);
	rayTrace.AddSurface(sphere2);
	rayTrace.AddSurface(quad1);

    while ( display.open() )
    {
		if (GetAsyncKeyState(KEY_W) != 0)
		{
			rayTrace._spheres[0]._z0 -= .05f;
		}
		if (GetAsyncKeyState(KEY_A) != 0)
		{
			sphere1._z0 += .01f;
		}
		if (GetAsyncKeyState(KEY_S) != 0)
		{
			sphere1._z0 -= .05f;
		}

		rayTrace.CreateScene();

		display.update( rayTrace.FetchPixels() );
		rayTrace.RefreshThreadOrder();
		rayTrace.RefreshPixels();
    }

}

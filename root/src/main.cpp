#include "PixelToaster.h"
#include "RayTracer.h"

using namespace PixelToaster;

unsigned short Camera::numCameras = 0;

int main()
{
    const int width = 800;
    const int height = 600;

	Color background(1.0f, 1.0f, 1.0f);
	RayTracer rayTrace(width, height, background);

	Display display( "Floating Point Example", width, height );

	Plane plane1;
	plane1._A = 1.0f;
	plane1._B = 0.0f;
	plane1._C = 0.0f;
	plane1._D = 0.1f;
	plane1._color = Color(1.0f, 0.0f, 0.0f);
	Plane plane2;
	plane2._A = 0.0f;
	plane2._B = 1.0f;
	plane2._C = 0.0f;
	plane2._D = 0.1f;
	plane2._color = Color(0.0f, 1.0f, 0.0f);
	Plane plane3;
	plane3._A = 0.0f;
	plane3._B = 0.0f;
	plane3._C = 1.0f;
	plane3._D = -0.2f;
	plane3._color = Color(0.0f, 0.0f, 1.0f);
	Sphere sphere1;
	sphere1._r = 0.04;
	sphere1._x0 = 0.0f;
	sphere1._y0 = 0.0f;
	sphere1._z0 = 0.1f;
	sphere1._color = Color(1.0f, 0.0f, 1.0f);
	Quad quad1;
	quad1._b0 = Vector(-0.1f, 0.0f, 0.19f);
	quad1._b1 = Vector(1.0f, 0.0f, 0.19f);
	quad1._b2 = Vector(-0.1f, 1.0f, 0.19f);
	quad1._height = 0.15f;
	quad1._width = 0.2f;
	quad1._color = Color(1.0f, 1.0f, 0.0f);

    while ( display.open() )
    {
		rayTrace.RayCast(plane1);
		rayTrace.RayCast(plane2);
		rayTrace.RayCast(plane3);
		rayTrace.RayCast(sphere1);
		rayTrace.RayCast(quad1);

		display.update( rayTrace.FetchPixels() );
    }
}

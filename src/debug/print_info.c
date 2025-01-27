#include <scene.h>

void	print_camera(t_objs cam)
{
	printf("Camera\nCoordinates: (x=%f, y=%f, z=%f)\n  "
		"Direction: (%f, %f, %f)\n        "
		"Fov: %f\n"
		"realtimeFov: %f\n   "
		"zvp_dist: %f\n",
		cam.coords[0], cam.coords[1], cam.coords[2],
		cam.c.orientation[0], cam.c.orientation[1], cam.c.orientation[2],
		cam.c.fov, cam.c.realtime_fov, cam.c.zvp_dist);
}

void	print_ambient(t_objs amb)
{
	printf("Ambient\n     "
		"Ratio: %f\n    "
		"Colour: (%f, %f, %f, %f)\n",
		amb.a.ratio,
		amb.color[0], amb.color[1], amb.color[2], amb.color[3]);
}

void	print_light(t_objs amb)
{
	printf("lighting\nCoordinates: (x=%f, y=%f, z=%f)\n     "
		"Ratio:	%f)\n    "
		"Colour: (%f, %f, %f, %f)\n",
		amb.coords[0], amb.coords[1], amb.coords[2],
		amb.a.ratio,
		amb.color[0], amb.color[1], amb.color[2], amb.color[3]);
}

void	print_plane(t_objs pl)
{
	printf("Plane\nCoordinates: (x=%f, y=%f, z=%f)\n  "
		"Direction: (%f, %f, %f)\n     "
		"Colour: (%f, %f, %f, %f)\n",
		pl.coords[0], pl.coords[1], pl.coords[2],
		pl.plane.orientation[0], pl.plane.orientation[1], pl.plane.orientation[2],
		pl.color[0], pl.color[1], pl.color[2], pl.color[3]);
}

void	print_sphere(t_objs sp)
{
	printf("Sphere\nCoordinates: (x=%f, y=%f, z=%f)\n   "
		"Diameter: %f\n     Radius: %f\n     Colour: (%f, %f, %f, %f)\n",
		sp.coords[0], sp.coords[1], sp.coords[2],
		sp.sphere.diameter, sp.sphere.radius,
		sp.color[0], sp.color[1], sp.color[2], sp.color[3]);
}

void	print_cylinder(t_objs cy)
{
	const t_cylinder	c = cy.cylinder;

	printf("Cylinder\nCoordinates: (x=%f, y=%f, z=%f)\n  Direction: (%f, %f, %f)\n"
		"Diameter: %f\n     Radius: %f\n     "
		"Height: %f\n     Colour: (%f, %f, %f, %f)\n",
		cy.coords[0], cy.coords[1], cy.coords[2],
		c.orientation[0], c.orientation[1], c.orientation[2],
		c.diameter, c.radius, c.height,
		cy.color[0], cy.color[1], cy.color[2], cy.color[3]);
}

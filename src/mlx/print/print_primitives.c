#include <scene.h>

//	Static Functions
static void	print_plane(t_objs pl);
static void	print_sphere(t_objs sp);
static void	print_cylinder(t_objs cy);

void	geometric_primitives(t_objs *obj)
{
	static void	(*print_primitives[])(t_objs) = {
		print_plane,
		print_sphere,
		print_cylinder
	};

	print_primitives[obj->type](*obj);
}

static void	print_plane(t_objs pl)
{
	printf("\nPlane\nCoordinates: (x=%f, y=%f, z=%f)\n  "
		"Direction: (%f, %f, %f)\n     "
		"Colour: (%d, %d, %d)\n",
		pl.coords[0], pl.coords[1], pl.coords[2],
		pl.plane.orientation[0], pl.plane.orientation[1], pl.plane.orientation[2],
		(int)(pl.color[0] * 255), (int)(pl.color[1] * 255),
		(int)(pl.color[2] * 255));
}

static void	print_sphere(t_objs sp)
{
	printf("\nSphere\nCoordinates: (x=%f, y=%f, z=%f)\n   "
		"Diameter: %f\n     Radius: %f\n     Colour: (%d, %d, %d)\n",
		sp.coords[0], sp.coords[1], sp.coords[2],
		sp.sphere.radius * 2, sp.sphere.radius,
		(int)(sp.color[0] * 255), (int)(sp.color[1] * 255),
		(int)(sp.color[2] * 255));
}

static void	print_cylinder(t_objs cy)
{
	const t_cylinder	c = cy.cylinder;

	printf("\nCylinder\nCoordinates: (x=%f, y=%f, z=%f)\n  Direction: (%f, %f, %f)\n"
		"Diameter: %f\n     Radius: %f\n     "
		"Height: %f\n     Colour: (%d, %d, %d)\n",
		cy.coords[0], cy.coords[1], cy.coords[2],
		c.orientation[0], c.orientation[1], c.orientation[2],
		c.radius * 2, c.radius, c.height,
		(int)(cy.color[0] * 255), (int)(cy.color[1] * 255),
		(int)(cy.color[2] * 255));
}

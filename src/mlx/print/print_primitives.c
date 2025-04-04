#include <scene.h>

//	Static Functions
static void	print_plane(t_objs pl);
static void	print_sphere(t_objs sp);
static void	print_cylinder(t_objs cy);

void	geometric_primitives(t_objs *obj)
{
    static void (*print_primitives[])(t_objs) = {
        print_plane,
        print_sphere,
        print_cylinder
    };

    // Call the appropriate static function based on the object's type
    print_primitives[obj->type](*obj);
}

static void	print_plane(t_objs pl)
{
	printf("\nPlane\nCoordinates: (x=%f, y=%f, z=%f)\n  "
		"Direction: (%f, %f, %f)\n     "
		"Colour: (%f, %f, %f, %f)\n",
		pl.coords[0], pl.coords[1], pl.coords[2],
		pl.plane.orientation[0], pl.plane.orientation[1], pl.plane.orientation[2],
		pl.color[0], pl.color[1], pl.color[2], pl.color[3]);
}

static void	print_sphere(t_objs sp)
{
	printf("\nSphere\nCoordinates: (x=%f, y=%f, z=%f)\n   "
		"Diameter: %f\n     Radius: %f\n     Colour: (%f, %f, %f, %f)\n",
		sp.coords[0], sp.coords[1], sp.coords[2],
		sp.sphere.diameter, sp.sphere.radius,
		sp.color[0], sp.color[1], sp.color[2], sp.color[3]);
}

static void	print_cylinder(t_objs cy)
{
	const t_cylinder	c = cy.cylinder;

	printf("\nCylinder\nCoordinates: (x=%f, y=%f, z=%f)\n  Direction: (%f, %f, %f)\n"
		"Diameter: %f\n     Radius: %f\n     "
		"Height: %f\n     Colour: (%f, %f, %f, %f)\n",
		cy.coords[0], cy.coords[1], cy.coords[2],
		c.orientation[0], c.orientation[1], c.orientation[2],
		c.diameter, c.radius, c.height,
		cy.color[0], cy.color[1], cy.color[2], cy.color[3]);
}

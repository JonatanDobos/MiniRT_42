#include "../include/minirt_param.h"

// Debugging functions

void	_print_parsing(t_scene *sc)
{
	printf("\nAmbient Light:\n"
	   "  Ratio: %.2f\n"
	   "  Color: (r: %.2f, g: %.2f, b: %.2f, a: %.2f)\n",
	   sc->ambient.ratio,
	   sc->ambient.color[R], sc->ambient.color[G], sc->ambient.color[B], sc->ambient.color[A]);
	printf("\nCamera:\n"
	   "  Position: (x: %.2f, y: %.2f, z: %.2f)\n"
	   "  Orientation: (x: %.2f, y: %.2f, z: %.2f)\n"
	   "  FOV: %d\n",
	   sc->cam.point[X], sc->cam.point[Y], sc->cam.point[Z],
	   sc->cam.orient[X], sc->cam.orient[Y], sc->cam.orient[Z],
	   sc->cam.fov);
	printf("\nLight:\n"
	   "  Position: (x: %.2f, y: %.2f, z: %.2f)\n"
	   "  Brightness: %.2f\n"
	   "  Color: (r: %.2f, g: %.2f, b: %.2f, a: %.2f)\n",
	   sc->light.point[X], sc->light.point[Y], sc->light.point[Z],
	   sc->light.brightness,
	   sc->light.color[R], sc->light.color[G], sc->light.color[B], sc->light.color[A]);
	printf("\n\033[0;32m");
	int	i = 0;
	t_plane pl;
	while (i < sc->plane_count)
	{
		pl = sc->plane[i];
		printf("\nPlane [%d]:\n"
	   "  Point: (x: %.2f, y: %.2f, z: %.2f)\n"
	   "  Normal: (x: %.2f, y: %.2f, z: %.2f)\n"
	   "  Color: (r: %.2f, g: %.2f, b: %.2f, a: %.2f)\n",
	   i, pl.point[X], pl.point[Y], pl.point[Z],
	   pl.normal[X], pl.normal[Y], pl.normal[Z],
	   pl.color[R], pl.color[G], pl.color[B], pl.color[A]);
	   ++i;
	}
	printf("\n\033[0;34m");
	i = 0;
	t_sphere sp;
	while (i < sc->sphere_count)
	{
		sp = sc->sphere[i];
		printf("\nSphere [%d]:\n"
	   "  Center: (x: %.2f, y: %.2f, z: %.2f)\n"
	   "  Radius: %.2f\n"
	   "  Color: (r: %.2f, g: %.2f, b: %.2f, a: %.2f)\n",
	   i, sp.center[X], sp.center[Y], sp.center[Z],
	   sp.radius,
	   sp.color[R], sp.color[G], sp.color[B], sp.color[A]);
		++i;
	}
	printf("\n\033[0;35m");
	i = 0;
	t_cylinder cy;
	while (i < sc->cylinder_count)
	{
		cy = sc->cylinder[i];
		printf("\nCylinder [%d]:\n"
	   "  Center: (x: %.2f, y: %.2f, z: %.2f)\n"
	   "  Normal: (x: %.2f, y: %.2f, z: %.2f)\n"
	   "  Radius: %.2f\n"
	   "  Height: %.2f\n"
	   "  Color: (r: %.2f, g: %.2f, b: %.2f, a: %.2f)\n",
	   i, cy.center[X], cy.center[Y], cy.center[Z],
	   cy.normal[X], cy.normal[Y], cy.normal[Z],
	   cy.radius,
	   cy.height,
	   cy.color[R], cy.color[G], cy.color[B], cy.color[A]);
		++i;
	}
	printf("\n\033[0m");
}

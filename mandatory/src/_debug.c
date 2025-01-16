#include "../include/minirt_param.h"

// Debugging functions

void	_print_parsing(t_scene *sc)
{
	printf("\nAmbient Light:\n"
       "  Ratio: %.2f\n"
       "  Color: (r: %d, g: %d, b: %d, a: %d)\n",
       sc->ambient.ratio,
       sc->ambient.color.r, sc->ambient.color.g, sc->ambient.color.b, sc->ambient.color.a);
	printf("\nCamera:\n"
       "  Position: (x: %.2f, y: %.2f, z: %.2f)\n"
       "  Orientation: (x: %.2f, y: %.2f, z: %.2f)\n"
       "  FOV: %d\n",
       sc->cam.point.x, sc->cam.point.y, sc->cam.point.z,
       sc->cam.orient.x, sc->cam.orient.y, sc->cam.orient.z,
       sc->cam.fov);
	printf("\nLight:\n"
       "  Position: (x: %.2f, y: %.2f, z: %.2f)\n"
       "  Brightness: %.2f\n"
       "  Color: (r: %d, g: %d, b: %d, a: %d)\n",
       sc->light.point.x, sc->light.point.y, sc->light.point.z,
       sc->light.brightness,
       sc->light.color.r, sc->light.color.g, sc->light.color.b, sc->light.color.a);
	printf("\n\033[0;32m");
	int i = 0;
	t_plane pl;
	while (i < sc->plane_count)
	{
		pl = sc->plane[i];
		printf("\nPlane [%d]:\n"
       "  Point: (x: %.2f, y: %.2f, z: %.2f)\n"
       "  Normal: (x: %.2f, y: %.2f, z: %.2f)\n"
       "  Color: (r: %d, g: %d, b: %d, a: %d)\n",
       i, pl.point.x, pl.point.y, pl.point.z,
       pl.normal.x, pl.normal.y, pl.normal.z,
       pl.color.r, pl.color.g, pl.color.b, pl.color.a);
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
       "  Color: (r: %d, g: %d, b: %d, a: %d)\n",
       i, sp.center.x, sp.center.y, sp.center.z,
       sp.radius,
       sp.color.r, sp.color.g, sp.color.b, sp.color.a);
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
       "  Color: (r: %d, g: %d, b: %d, a: %d)\n",
       i, cy.center.x, cy.center.y, cy.center.z,
       cy.normal.x, cy.normal.y, cy.normal.z,
       cy.radius,
       cy.height,
       cy.color.r, cy.color.g, cy.color.b, cy.color.a);
		++i;
	}
	printf("\n\033[0m");
}

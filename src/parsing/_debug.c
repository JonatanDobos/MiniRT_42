#include <parsing.h>
#include <common_defs.h>
// Debugging functions

void	_print_parsing(t_scene *sc)
{
	// printf("\nAmbient Light:\n"
	// "  Ratio: %.2f\n"
	// "  Color: (r: %d, g: %d, b: %d, a: %d)\n",
	// sc->ambient.ambient.ratio,
	// sc->ambient.color.r, sc->ambient.color.g, sc->ambient.color.b, sc->ambient.color.a);
	// printf("\nCamera:\n"
	// "  Position: (x: %.2f, y: %.2f, z: %.2f)\n"
	// "  Orientation: (x: %.2f, y: %.2f, z: %.2f)\n"
	// "  FOV: %f\n",
	// sc->camera.coords[0], sc->camera.coords[1], sc->camera.coords[2],
	// sc->camera.cam.orientation[0], sc->camera.cam.orientation[1], sc->camera.cam.orientation[2],
	// sc->camera.cam.fov);
	// printf("\nLight:\n"
	// "  Position: (x: %.2f, y: %.2f, z: %.2f)\n"
	// "  Brightness: %.2f\n"
	// "  Color: (r: %d, g: %d, b: %d, a: %d)\n",
	// sc->light.coords[0], sc->light.coords[0], sc->light.coords[0],
	// sc->light.light.brightness,
	// sc->light.color.r, sc->light.color.g, sc->light.color.b, sc->light.color.a);
	// printf("\n\033[0;32m");

	// int	i = 0;
	// int	ipl = 1;
	// int	isp = 1;
	// int	icy = 1;
	// t_objs		ob;
	// printf("\t%zu\n", sc->o_arr_size);
	// while (i < sc->o_arr_size)
	// {
	// 	if (sc->objarr[i].type == PLANE)
	// 	{
	// 		ob = sc->objarr[i];
	// 		printf("\nPlane [%d]:\n"
	// 		"  Point: (x: %.2f, y: %.2f, z: %.2f)\n"
	// 		"  Normal: (x: %.2f, y: %.2f, z: %.2f)\n"
	// 		"  Color: (r: %d, g: %d, b: %d, a: %d)\n",
	// 		ipl, ob.coords[0], ob.coords[1], ob.coords[2],
	// 		ob.plane.direction[0], ob.plane.direction[1], ob.plane.direction[2],
	// 		ob.color.r, ob.color.g, ob.color.b, ob.color.a);
	// 		++ipl;
	// 	}
	// 	if (sc->objarr[i].type == SPHERE)
	// 	{
	// 		ob = sc->objarr[i];
	// 		printf("\nSphere [%d]:\n"
	// 		"  Center: (x: %.2f, y: %.2f, z: %.2f)\n"
	// 		"  Radius: %.2f\n"
	// 		"  Color: (r: %d, g: %d, b: %d, a: %d)\n",
	// 		isp, ob.coords[0], ob.coords[1], ob.coords[2],
	// 		ob.sphere.radius,
	// 		ob.color.r, ob.color.g, ob.color.b, ob.color.a);
	// 		++isp;
	// 	}
	// 	if (sc->objarr[i].type == CYLINDER)
	// 	{
	// 		ob = sc->objarr[i];
	// 		printf("\nCylinder [%d]:\n"
	// 		"  Center: (x: %.2f, y: %.2f, z: %.2f)\n"
	// 		"  Normal: (x: %.2f, y: %.2f, z: %.2f)\n"
	// 		"  Radius: %.2f\n"
	// 		"  Height: %.2f\n"
	// 		"  Color: (r: %d, g: %d, b: %d, a: %d)\n",
	// 		icy, ob.coords[0], ob.coords[1], ob.coords[2],
	// 		ob.cylinder.direction[0], ob.cylinder.direction[1], ob.cylinder.direction[2],
	// 		ob.cylinder.radius,
	// 		ob.cylinder.height,
	// 		ob.color.r, ob.color.g, ob.color.b, ob.color.a);
	// 		++icy;
	// 	}
	// 	++i;
	// }
	// printf("\n\033[0m");
}

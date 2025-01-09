#include "../include/minirt_param.h"

t_short	parse_pl(t_scene *sc, t_value_check *vc, char *line)
{
	t_plane	pl;

	pl.point.x = rt_atof(line);
	pl.point.y = rt_atof(nxtvp(&line));
	pl.point.z = rt_atof(nxtvp(&line));
	pl.normal.x = range(rt_atof(nxtvp(&line)), -1.0f, 1.0f);
	pl.normal.y = range(rt_atof(nxtvp(&line)), -1.0f, 1.0f);
	pl.normal.z = range(rt_atof(nxtvp(&line)), -1.0f, 1.0f);
	pl.color.r = rt_atoi(nxtvp(&line));
	pl.color.g = rt_atoi(nxtvp(&line));
	pl.color.b = rt_atoi(nxtvp(&line));
	pl.color.a = 255;
	if (!memappend((void **)&sc->plane, &pl, sizeof(t_plane), sc->plane_count))
		return (errset(perr("parse_pl", errno)));
	sc->plane_count++;
	vc->obj_amount++;
	uint16_t i = 0;
	// DOES NOT WORK?
	while (i < sc->plane_count)
	{
		pl = sc->plane[i];
		printf("\nPlane [%d]:\n"
       "  Point: (x: %.2f, y: %.2f, z: %.2f)\n"
       "  Normal: (x: %.2f, y: %.2f, z: %.2f)\n"
       "  Color: (r: %d, g: %d, b: %d, a: %d)\n",
       i, pl.point.x, pl.point.y, pl.point.z,
       pl.normal.x, pl.normal.y, pl.normal.z,
       pl.color.r, pl.color.g, pl.color.b, pl.color.a);//t
	   ++i;
	}
	return (SUCCESS);
}

t_short	parse_sp(t_scene *sc, t_value_check *vc, char *line)
{
	t_sphere	sp;

	sp.center.x = rt_atof(line);
	sp.center.y = rt_atof(nxtvp(&line));
	sp.center.z = rt_atof(nxtvp(&line));
	sp.radius = rt_atof(nxtvp(&line)) / 2.0f;
	sp.color.r = rt_atoi(nxtvp(&line));
	sp.color.g = rt_atoi(nxtvp(&line));
	sp.color.b = rt_atoi(nxtvp(&line));
	sp.color.a = 255;
	printf("\nSphere:\n"
       "  Center: (x: %.2f, y: %.2f, z: %.2f)\n"
       "  Radius: %.2f\n"
       "  Color: (r: %d, g: %d, b: %d, a: %d)\n",
       sp.center.x, sp.center.y, sp.center.z,
       sp.radius,
       sp.color.r, sp.color.g, sp.color.b, sp.color.a);//t
	if (!memappend((void **)&sc->sphere, &sp, sizeof(t_sphere), sc->sphere_count))
		return (errset(perr("parse_sp", errno)));
	sc->sphere_count++;
	vc->obj_amount++;
	return (SUCCESS);
}

t_short	parse_cy(t_scene *sc, t_value_check *vc, char *line)
{
	t_cylinder	cy;

	cy.center.x = rt_atof(line);
	cy.center.y = rt_atof(nxtvp(&line));
	cy.center.z = rt_atof(nxtvp(&line));
	cy.normal.x = range(rt_atof(nxtvp(&line)), -1.0f, 1.0f);
	cy.normal.y = range(rt_atof(nxtvp(&line)), -1.0f, 1.0f);
	cy.normal.z = range(rt_atof(nxtvp(&line)), -1.0f, 1.0f);
	cy.radius = rt_atof(nxtvp(&line)) / 2.0f;
	cy.height = rt_atof(nxtvp(&line));
	cy.color.r = rt_atoi(nxtvp(&line));
	cy.color.g = rt_atoi(nxtvp(&line));
	cy.color.b = rt_atoi(nxtvp(&line));
	cy.color.a = 255;
	printf("\nCylinder:\n"
       "  Center: (x: %.2f, y: %.2f, z: %.2f)\n"
       "  Normal: (x: %.2f, y: %.2f, z: %.2f)\n"
       "  Radius: %.2f\n"
       "  Height: %.2f\n"
       "  Color: (r: %d, g: %d, b: %d, a: %d)\n",
       cy.center.x, cy.center.y, cy.center.z,
       cy.normal.x, cy.normal.y, cy.normal.z,
       cy.radius,
       cy.height,
       cy.color.r, cy.color.g, cy.color.b, cy.color.a);//t
	if (!memappend((void **)&sc->cylinder, &cy, sizeof(t_cylinder), sc->cylinder_count))
		return (errset(perr("parse_cy", errno)));
	sc->cylinder_count++;
	vc->obj_amount++;
	return (SUCCESS);
}

#include "../include/minirt_param.h"

int16_t	parse_pl(t_scene *sc, t_value_check *vc, char *line)
{
	t_plane	pl;

	pl.point[X] = rt_atof(line);
	pl.point[Y] = rt_atof(nxtvp(&line));
	pl.point[Z] = rt_atof(nxtvp(&line));
	pl.point[W] = 1.0f;
	pl.normal[X] = range(rt_atof(nxtvp(&line)), -1.0f, 1.0f);
	pl.normal[Y] = range(rt_atof(nxtvp(&line)), -1.0f, 1.0f);
	pl.normal[Z] = range(rt_atof(nxtvp(&line)), -1.0f, 1.0f);
	pl.normal[W] = 0.0f;
	pl.color[R] = (float)(range(rt_atoi(nxtvp(&line)), 0, 255)) / 255.0f;
	pl.color[G] = (float)(range(rt_atoi(nxtvp(&line)), 0, 255)) / 255.0f;
	pl.color[B] = (float)(range(rt_atoi(nxtvp(&line)), 0, 255)) / 255.0f;
	pl.color[A] = 1.0f;
	if (!memappend((void **)&sc->plane, &pl, sizeof(t_plane), sc->plane_count))
		return (errset(perr("parse_pl", errno)));
	sc->plane_count++;
	vc->obj_amount++;
	return (SUCCESS);
}

int16_t	parse_sp(t_scene *sc, t_value_check *vc, char *line)
{
	t_sphere	sp;

	sp.center[X] = rt_atof(line);
	sp.center[Y] = rt_atof(nxtvp(&line));
	sp.center[Z] = rt_atof(nxtvp(&line));
	sp.center[W] = 1.0f;
	sp.radius = rt_atof(nxtvp(&line)) / 2.0f;
	sp.color[R] = (float)(range(rt_atoi(nxtvp(&line)), 0, 255)) / 255.0f;
	sp.color[G] = (float)(range(rt_atoi(nxtvp(&line)), 0, 255)) / 255.0f;
	sp.color[B] = (float)(range(rt_atoi(nxtvp(&line)), 0, 255)) / 255.0f;
	sp.color[A] = 1.0f;
	if (!memappend((void **)&sc->sphere, &sp, sizeof(t_sphere), sc->sphere_count))
		return (errset(perr("parse_sp", errno)));
	sc->sphere_count++;
	vc->obj_amount++;
	return (SUCCESS);
}

int16_t	parse_cy(t_scene *sc, t_value_check *vc, char *line)
{
	t_cylinder	cy;

	cy.center[X] = rt_atof(line);
	cy.center[Y] = rt_atof(nxtvp(&line));
	cy.center[Z] = rt_atof(nxtvp(&line));
	cy.center[W] = 1.0f;
	cy.normal[X] = range(rt_atof(nxtvp(&line)), -1.0f, 1.0f);
	cy.normal[Y] = range(rt_atof(nxtvp(&line)), -1.0f, 1.0f);
	cy.normal[Z] = range(rt_atof(nxtvp(&line)), -1.0f, 1.0f);
	cy.normal[W] = 0.0f;
	cy.radius = rt_atof(nxtvp(&line)) / 2.0f;
	cy.height = rt_atof(nxtvp(&line));
	cy.color[R] = (float)(range(rt_atoi(nxtvp(&line)), 0, 255)) / 255.0f;
	cy.color[G] = (float)(range(rt_atoi(nxtvp(&line)), 0, 255)) / 255.0f;
	cy.color[B] = (float)(range(rt_atoi(nxtvp(&line)), 0, 255)) / 255.0f;
	cy.color[A] = 1.0f;
	if (!memappend((void **)&sc->cylinder, &cy, sizeof(t_cylinder), sc->cylinder_count))
		return (errset(perr("parse_cy", errno)));
	sc->cylinder_count++;
	vc->obj_amount++;
	return (SUCCESS);
}

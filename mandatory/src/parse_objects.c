#include "../include/minirt_param.h"

t_short	parse_pl(t_scene *sc, t_value_check *vc, char *line)
{
	t_plane	pl;

	pl.point.x = rt_atof(line);
	pl.point.y = rt_atof(nxtvalue(line));
	pl.point.z = rt_atof(nxtvalue(line));
	pl.normal.x = range(rt_atof(nxtvalue(line)), -1.0f, 1.0f);
	pl.normal.y = range(rt_atof(nxtvalue(line)), -1.0f, 1.0f);
	pl.normal.z = range(rt_atof(nxtvalue(line)), -1.0f, 1.0f);
	pl.color.r = rt_atoi(nxtvalue(line));
	pl.color.g = rt_atoi(nxtvalue(line));
	pl.color.b = rt_atoi(nxtvalue(line));
	pl.color.a = 255;
	if (!memappend((void **)&sc->plane, &pl, sizeof(t_plane), sc->plane_count))
		return (errset(perr("parse_pl", errno)));
	sc->plane_count++;
	vc->obj_amount++;
	return (SUCCESS);
}

t_short	parse_sp(t_scene *sc, t_value_check *vc, char *line)
{
	t_sphere	sp;

	sp.center.x = rt_atof(line);
	sp.center.y = rt_atof(nxtvalue(line));
	sp.center.z = rt_atof(nxtvalue(line));
	sp.radius = rt_atof(nxtvalue(line)) / 2.0f;
	sp.color.r = rt_atoi(nxtvalue(line));
	sp.color.g = rt_atoi(nxtvalue(line));
	sp.color.b = rt_atoi(nxtvalue(line));
	sp.color.a = 255;
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
	cy.center.y = rt_atof(nxtvalue(line));
	cy.center.z = rt_atof(nxtvalue(line));
	cy.normal.x = range(rt_atof(nxtvalue(line)), -1.0f, 1.0f);
	cy.normal.y = range(rt_atof(nxtvalue(line)), -1.0f, 1.0f);
	cy.normal.z = range(rt_atof(nxtvalue(line)), -1.0f, 1.0f);
	cy.radius = rt_atof(nxtvalue(line)) / 2.0f;
	cy.height = rt_atof(nxtvalue(line));
	cy.color.r = rt_atoi(nxtvalue(line));
	cy.color.g = rt_atoi(nxtvalue(line));
	cy.color.b = rt_atoi(nxtvalue(line));
	cy.color.a = 255;
	if (!memappend((void **)&sc->cylinder, &cy, sizeof(t_cylinder), sc->cylinder_count))
		return (errset(perr("parse_cy", errno)));
	sc->cylinder_count++;
	vc->obj_amount++;
	return (SUCCESS);
}

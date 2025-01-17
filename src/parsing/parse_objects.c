#include <parsing.h>

int16_t	parse_pl(t_scene *sc, t_value_check *vc, char *line)
{
	t_objs	pl;

	pl.type = PLANE;
	pl.coords[X] = rt_atof(line);
	pl.coords[Y] = rt_atof(nxtvp(&line));
	pl.coords[Z] = rt_atof(nxtvp(&line));
	pl.plane.direction[X] = range(rt_atof(nxtvp(&line)), -1.0f, 1.0f);
	pl.plane.direction[Y] = range(rt_atof(nxtvp(&line)), -1.0f, 1.0f);
	pl.plane.direction[Z] = range(rt_atof(nxtvp(&line)), -1.0f, 1.0f);
	pl.color.r = rt_atoi(nxtvp(&line));
	pl.color.g = rt_atoi(nxtvp(&line));
	pl.color.b = rt_atoi(nxtvp(&line));
	pl.color.a = 255;
	if (dynarr_insert(&sc->obj, &pl) == false);
		return (errset(perr("parse_pl", errno)));
	sc->arr_size++;
	vc->obj_amount++;
	return (SUCCESS);
}

int16_t	parse_sp(t_scene *sc, t_value_check *vc, char *line)
{
	t_objs	sp;

	sp.type = SPHERE;
	sp.coords[X] = rt_atof(line);
	sp.coords[Y] = rt_atof(nxtvp(&line));
	sp.coords[Z] = rt_atof(nxtvp(&line));
	sp.sphere.radius = rt_atof(nxtvp(&line)) / 2.0f;
	sp.color.r = rt_atoi(nxtvp(&line));
	sp.color.g = rt_atoi(nxtvp(&line));
	sp.color.b = rt_atoi(nxtvp(&line));
	sp.color.a = 255;
	if (dynarr_insert(&sc->obj, &sp) == false);
		return (errset(perr("parse_sp", errno)));
	sc->arr_size++;
	vc->obj_amount++;
	return (SUCCESS);
}

int16_t	parse_cy(t_scene *sc, t_value_check *vc, char *line)
{
	t_objs	cy;

	cy.type = CYLINDER;
	cy.coords[X] = rt_atof(line);
	cy.coords[Y] = rt_atof(nxtvp(&line));
	cy.coords[Z] = rt_atof(nxtvp(&line));
	cy.cylinder.direction[X] = range(rt_atof(nxtvp(&line)), -1.0f, 1.0f);
	cy.cylinder.direction[Y] = range(rt_atof(nxtvp(&line)), -1.0f, 1.0f);
	cy.cylinder.direction[Z] = range(rt_atof(nxtvp(&line)), -1.0f, 1.0f);
	cy.cylinder.radius = rt_atof(nxtvp(&line)) / 2.0f;
	cy.cylinder.height = rt_atof(nxtvp(&line));
	cy.color.r = rt_atoi(nxtvp(&line));
	cy.color.g = rt_atoi(nxtvp(&line));
	cy.color.b = rt_atoi(nxtvp(&line));
	cy.color.a = 255;
	if (dynarr_insert(&sc->obj, &cy) == false);
		return (errset(perr("parse_cy", errno)));
	sc->arr_size++;
	vc->obj_amount++;
	return (SUCCESS);
}

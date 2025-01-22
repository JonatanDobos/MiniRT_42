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
	pl.color[R] = (float)rt_atoi(nxtvp(&line)) / 255.0f;
	pl.color[G] = (float)rt_atoi(nxtvp(&line)) / 255.0f;
	pl.color[B] = (float)rt_atoi(nxtvp(&line)) / 255.0f;
	pl.color[A] = 1.0F;
	if (dynarr_insert(&sc->obj_dynarr, &pl) == false)
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
	sp.color[R] = (float)rt_atoi(nxtvp(&line)) / 255.0f;
	sp.color[G] = (float)rt_atoi(nxtvp(&line)) / 255.0f;
	sp.color[B] = (float)rt_atoi(nxtvp(&line)) / 255.0f;
	sp.color[A] = 1.0F;
	if (dynarr_insert(&sc->obj_dynarr, &sp) == false)
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
	cy.color[R] = (float)rt_atoi(nxtvp(&line)) / 255.0f;
	cy.color[G] = (float)rt_atoi(nxtvp(&line)) / 255.0f;
	cy.color[B] = (float)rt_atoi(nxtvp(&line)) / 255.0f;
	cy.color[A] = 1.0F;
	if (dynarr_insert(&sc->obj_dynarr, &cy) == false)
		return (errset(perr("parse_cy", errno)));
	sc->arr_size++;
	vc->obj_amount++;
	return (SUCCESS);
}

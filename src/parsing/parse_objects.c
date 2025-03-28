#include <parsing.h>
#include <debug.h>


int16_t	parse_pl(t_scene *sc, t_value_check *vc, char *line)
{
	t_objs	pl;

	pl.type = PLANE;
	pl.coords[X] = rt_atof(line);
	pl.coords[Y] = rt_atof(nxtvp(&line));
	pl.coords[Z] = rt_atof(nxtvp(&line));
	pl.coords[3] = 1.0F;
	pl.plane.orientation[X] = range(rt_atof(nxtvp(&line)), -1.0F, 1.0F);
	pl.plane.orientation[Y] = range(rt_atof(nxtvp(&line)), -1.0F, 1.0F);
	pl.plane.orientation[Z] = range(rt_atof(nxtvp(&line)), -1.0F, 1.0F);
	pl.plane.orientation[3] = 0.0F;
	pl.color[R] = (float)rt_atoi(nxtvp(&line)) / 255.0F;
	pl.color[G] = (float)rt_atoi(nxtvp(&line)) / 255.0F;
	pl.color[B] = (float)rt_atoi(nxtvp(&line)) / 255.0F;
	pl.color[A] = 1.0F;
	if (dynarr_insert(&sc->obj_dynarr, &pl) == false)
		return (errset(perr("parse_pl", errno)));
	++sc->o_arr_size;
	++vc->obj_amount;
	return (EXIT_SUCCESS);
}

int16_t	parse_sp(t_scene *sc, t_value_check *vc, char *line)
{
	t_objs	sp;

	sp.type = SPHERE;
	sp.coords[X] = rt_atof(line);
	sp.coords[Y] = rt_atof(nxtvp(&line));
	sp.coords[Z] = rt_atof(nxtvp(&line));
	sp.coords[3] = 1.0F;
	sp.sphere.diameter = rt_atof(nxtvp(&line));
	sp.sphere.radius = sp.sphere.diameter / 2.0F;
	sp.color[R] = (float)rt_atoi(nxtvp(&line)) / 255.0F;
	sp.color[G] = (float)rt_atoi(nxtvp(&line)) / 255.0F;
	sp.color[B] = (float)rt_atoi(nxtvp(&line)) / 255.0F;
	sp.color[A] = 1.0F;
	if (dynarr_insert(&sc->obj_dynarr, &sp) == false)
		return (errset(perr("parse_sp", errno)));
	++sc->o_arr_size;
	++vc->obj_amount;
	return (EXIT_SUCCESS);
}

int16_t	parse_cy(t_scene *sc, t_value_check *vc, char *line)
{
	t_objs	cy;

	cy.type = CYLINDER;
	cy.coords[X] = rt_atof(line);
	cy.coords[Y] = rt_atof(nxtvp(&line));
	cy.coords[Z] = rt_atof(nxtvp(&line));
	cy.coords[3] = 1.0F;
	cy.cylinder.orientation[X] = range(rt_atof(nxtvp(&line)), -1.0f, 1.0f);
	cy.cylinder.orientation[Y] = range(rt_atof(nxtvp(&line)), -1.0f, 1.0f);
	cy.cylinder.orientation[Z] = range(rt_atof(nxtvp(&line)), -1.0f, 1.0f);
	cy.cylinder.orientation[3] = 0.0F;
	cy.cylinder.diameter = rt_atof(nxtvp(&line));
	cy.cylinder.radius = cy.cylinder.diameter / 2.0F;
	cy.cylinder.height = rt_atof(nxtvp(&line));
	cy.color[R] = (float)rt_atoi(nxtvp(&line)) / 255.0F;
	cy.color[G] = (float)rt_atoi(nxtvp(&line)) / 255.0F;
	cy.color[B] = (float)rt_atoi(nxtvp(&line)) / 255.0F;
	cy.color[A] = 1.0F;
	if (dynarr_insert(&sc->obj_dynarr, &cy) == false)
		return (errset(perr("parse_cy", errno)));
	++sc->o_arr_size;
	++vc->obj_amount;
	return (EXIT_SUCCESS);
}

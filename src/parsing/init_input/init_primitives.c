#include <parsing.h>
#include <mathRT.h>

//	Static Functions
static int16_t		parse_pl(t_scene *sc, t_value_check *vc, char *line);
static int16_t		parse_sp(t_scene *sc, t_value_check *vc, char *line);
static int16_t		parse_cy(t_scene *sc, t_value_check *vc, char *line);

int16_t	init_primitives(t_scene *sc, t_value_check *vc, char *line)
{
	if (ft_strncmp(line, "pl", 2) == 0)
		return (parse_pl(sc, vc, nxtv(line)));
	else if (ft_strncmp(line, "sp", 2) == 0)
		return (parse_sp(sc, vc, nxtv(line)));
	return (parse_cy(sc, vc, nxtv(line)));
}

static int16_t	parse_pl(t_scene *sc, t_value_check *vc, char *line)
{
	t_objs	pl;

	pl.type = PLANE;
	pl.coords[X] = rt_atof(line);
	pl.coords[Y] = rt_atof(nxtvp(&line));
	pl.coords[Z] = rt_atof(nxtvp(&line));
	pl.coords[W] = 1.0F;
	pl.plane.orientation[X] = clamp(rt_atof(nxtvp(&line)), -1.0F, 1.0F);
	pl.plane.orientation[Y] = clamp(rt_atof(nxtvp(&line)), -1.0F, 1.0F);
	pl.plane.orientation[Z] = clamp(rt_atof(nxtvp(&line)), -1.0F, 1.0F);
	pl.plane.orientation[3] = 0.0F;
	pl.plane.orientation = vnorm(pl.plane.orientation);
	pl.color[R] = (float)atoi32(nxtvp(&line)) / 255.0F;
	pl.color[G] = (float)atoi32(nxtvp(&line)) / 255.0F;
	pl.color[B] = (float)atoi32(nxtvp(&line)) / 255.0F;
	pl.color[A] = 1.0F;
	if (dynarr_insert(&vc->obj_dynarr, &pl) == false)
		return (errset(perr("parse_pl", ENOMEM)));
	++sc->o_arr_size;
	++vc->obj_amount;
	return (EXIT_SUCCESS);
}

static int16_t	parse_sp(t_scene *sc, t_value_check *vc, char *line)
{
	t_objs	sp;

	sp.type = SPHERE;
	sp.coords[X] = rt_atof(line);
	sp.coords[Y] = rt_atof(nxtvp(&line));
	sp.coords[Z] = rt_atof(nxtvp(&line));
	sp.coords[W] = 1.0F;
	sp.sphere.diameter = rt_atof(nxtvp(&line));
	sp.sphere.radius = sp.sphere.diameter / 2.0F;
	sp.color[R] = (float)atoi32(nxtvp(&line)) / 255.0F;
	sp.color[G] = (float)atoi32(nxtvp(&line)) / 255.0F;
	sp.color[B] = (float)atoi32(nxtvp(&line)) / 255.0F;
	sp.color[A] = 1.0F;
	if (dynarr_insert(&vc->obj_dynarr, &sp) == false)
		return (errset(perr("parse_sp", ENOMEM)));
	++sc->o_arr_size;
	++vc->obj_amount;
	return (EXIT_SUCCESS);
}

static int16_t	parse_cy(t_scene *sc, t_value_check *vc, char *line)
{
	t_objs	cy;

	cy.type = CYLINDER;
	cy.coords[X] = rt_atof(line);
	cy.coords[Y] = rt_atof(nxtvp(&line));
	cy.coords[Z] = rt_atof(nxtvp(&line));
	cy.coords[W] = 1.0F;
	cy.cylinder.orientation[X] = clamp(rt_atof(nxtvp(&line)), -1.0F, 1.0F);
	cy.cylinder.orientation[Y] = clamp(rt_atof(nxtvp(&line)), -1.0F, 1.0F);
	cy.cylinder.orientation[Z] = clamp(rt_atof(nxtvp(&line)), -1.0F, 1.0F);
	cy.cylinder.orientation[W] = 0.0F;
	cy.cylinder.orientation = vnorm(cy.cylinder.orientation);
	cy.cylinder.diameter = rt_atof(nxtvp(&line));
	cy.cylinder.radius = cy.cylinder.diameter / 2.0F;
	cy.cylinder.height = rt_atof(nxtvp(&line));
	cy.color[R] = (float)atoi32(nxtvp(&line)) / 255.0F;
	cy.color[G] = (float)atoi32(nxtvp(&line)) / 255.0F;
	cy.color[B] = (float)atoi32(nxtvp(&line)) / 255.0F;
	cy.color[A] = 1.0F;
	if (dynarr_insert(&vc->obj_dynarr, &cy) == false)
		return (errset(perr("parse_cy", ENOMEM)));
	++sc->o_arr_size;
	++vc->obj_amount;
	return (EXIT_SUCCESS);
}

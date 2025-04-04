#include <parsing.h>
#include <mathRT.h>

//	Static Functions
static int16_t	parse_amb(t_scene *sc, t_value_check *vc, char *line);
static int16_t	parse_cam(t_scene *sc, t_value_check *vc, char *line);
static int16_t	parse_light(t_scene *sc, t_value_check *vc, char *line);

int16_t	input_type_parse(t_scene *sc, t_value_check *vc, char *line)
{
	if (ft_strncmp(line, "A", 1) == 0)
		return (parse_amb(sc, vc, nxtv(line)));
	else if (ft_strncmp(line, "C", 1) == 0)
		return (parse_cam(sc, vc, nxtv(line)));
	else if (ft_strncmp(line, "L", 1) == 0)
		return (parse_light(sc, vc, nxtv(line)));
	return (init_primitives(sc, vc, line));
}

static int16_t	parse_amb(t_scene *sc, t_value_check *vc, char *line)
{
	sc->ambient.type = AMBIENT;
	sc->ambient.a.ratio = clamp(rt_atof(line), 0.0F, 1.0F);
	sc->ambient.color[R] = (float)rt_atoi(nxtvp(&line)) / 255.0F;
	sc->ambient.color[G] = (float)rt_atoi(nxtvp(&line)) / 255.0F;
	sc->ambient.color[B] = (float)rt_atoi(nxtvp(&line)) / 255.0F;
	sc->ambient.color[A] = 1.0F;
	++vc->amb_amount;
	return (EXIT_SUCCESS);
}

static int16_t	parse_cam(t_scene *sc, t_value_check *vc, char *line)
{
	sc->camera.coords[X] = rt_atof(line);
	sc->camera.coords[Y] = rt_atof(nxtvp(&line));
	sc->camera.coords[Z] = rt_atof(nxtvp(&line));
	sc->camera.c.orientation[X] = clamp(rt_atof(nxtvp(&line)), -1.0F, 1.0F);
	sc->camera.c.orientation[Y] = clamp(rt_atof(nxtvp(&line)), -1.0F, 1.0F);
	sc->camera.c.orientation[Z] = clamp(rt_atof(nxtvp(&line)), -1.0F, 1.0F);
	sc->camera.c.fov = clamp(rt_atoi(nxtvp(&line)), 0.0F, 180.0F);
	sc->camera.c.zvp_dist = 1.0F / tanf((sc->camera.c.fov * M_PI / 180.0F) / 2.0F);
	sc->camera.c.fov = sc->camera.c.fov;
	++vc->cam_amount;
	return (EXIT_SUCCESS);
}

static int16_t	parse_light(t_scene *sc, t_value_check *vc, char *line)
{
	t_objs	l;

	l.type = LIGHT;
	l.coords[X] = rt_atof(line);
	l.coords[Y] = rt_atof(nxtvp(&line));
	l.coords[Z] = rt_atof(nxtvp(&line));
	l.coords[3] = 1.0F;
	l.l.brightness = clamp(rt_atof(nxtvp(&line)), 0.0F, 1.0F);
	l.color[R] = (float)rt_atoi(nxtvp(&line)) / 255.0F;
	l.color[G] = (float)rt_atoi(nxtvp(&line)) / 255.0F;
	l.color[B] = (float)rt_atoi(nxtvp(&line)) / 255.0F;
	l.color[A] = 1.0F;
	l.l.radius = 1.0F;
	if (dynarr_insert(&sc->light_dynarr, &l) == false)
		return (errset(perr("parse_light", ENOMEM)));
	++sc->l_arr_size;
	++vc->light_amount;
	return (EXIT_SUCCESS);
}

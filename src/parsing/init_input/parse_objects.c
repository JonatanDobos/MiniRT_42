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
	sc->ambient.color[R] = (float)atoi32(nxtvp(&line)) / 255.0F;
	sc->ambient.color[G] = (float)atoi32(nxtvp(&line)) / 255.0F;
	sc->ambient.color[B] = (float)atoi32(nxtvp(&line)) / 255.0F;
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
	sc->camera.c.orientation[W] = 0.0F;
	sc->camera.c.orientation = vnorm(sc->camera.c.orientation);
	sc->camera.c.fov = clamp(atoi32(nxtvp(&line)), 0.0F, 180.0F);
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
	l.coords[W] = 1.0F;
	l.l.brightness = clamp(rt_atof(nxtvp(&line)), 0.0F, 1.0F);
	l.color[R] = (float)atoi32(nxtvp(&line)) / 255.0F;
	l.color[G] = (float)atoi32(nxtvp(&line)) / 255.0F;
	l.color[B] = (float)atoi32(nxtvp(&line)) / 255.0F;
	l.color[A] = 1.0F;
	l.l.radius = 1.5F;
	l.l.intersect_lights = false;
	l.l.visible = false;
	// printf("line >%s<\n", line);
	while (ft_isnum(line) == true)
		++line;
	// printf("line >%s<\n", line);
	while (ft_isspace(*line) == true)
		++line;
	// printf("line >%s<\n", line);
	if (ft_isnum(line) == true)
	{
		puts("zero");
		l.l.radius = (float)atoi32(line);
		l.l.visible = true;
		// printf(">>%f\n", l.l.radius);
	}
	if (dynarr_insert(&vc->light_dynarr, &l) == false)
		return (errset(perr("parse_light", ENOMEM)));
	++sc->l_arr_size;
	return (EXIT_SUCCESS);
}

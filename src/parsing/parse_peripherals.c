#include <parsing.h>
#include <math.h>
#include <utils.h>
#include <debug.h>
#include <mathRT.h>

int16_t	parse_amb(t_scene *sc, t_value_check *vc, char *line)
{
	sc->ambient.a.ratio = range(rt_atof(line), 0.0F, 1.0F);
	sc->ambient.color[R] = (float)rt_atoi(nxtvp(&line)) / 255.0F;
	sc->ambient.color[G] = (float)rt_atoi(nxtvp(&line)) / 255.0F;
	sc->ambient.color[B] = (float)rt_atoi(nxtvp(&line)) / 255.0F;
	sc->ambient.color[A] = 1.0F;
	++vc->amb_amount;
	return (SUCCESS);
}

int16_t	parse_cam(t_scene *sc, t_value_check *vc, char *line)
{
	sc->camera.coords[X] = rt_atof(line);
	sc->camera.coords[Y] = rt_atof(nxtvp(&line));
	sc->camera.coords[Z] = rt_atof(nxtvp(&line));
	sc->camera.c.orientation[X] = range(rt_atof(nxtvp(&line)), -1.0F, 1.0F);
	sc->camera.c.orientation[Y] = range(rt_atof(nxtvp(&line)), -1.0F, 1.0F);
	sc->camera.c.orientation[Z] = range(rt_atof(nxtvp(&line)), -1.0F, 1.0F);
	sc->camera.c.fov = range(rt_atoi(nxtvp(&line)), 0.0F, 180.0F);
	sc->camera.c.zvp_dist = 1.0F / tanf((sc->camera.c.fov * M_PI / 180.0F) / 2.0F);
	sc->camera.c.realtime_fov = sc->camera.c.fov;
	++vc->cam_amount;
	return (SUCCESS);
}

int16_t	parse_light(t_scene *sc, t_value_check *vc, char *line)
{
	t_objs	l;

	l.type = LIGHT;
	l.coords[X] = rt_atof(line);
	l.coords[Y] = rt_atof(nxtvp(&line));
	l.coords[Z] = rt_atof(nxtvp(&line));
	l.coords[3] = 1.0F;
	l.l.brightness = range(rt_atof(nxtvp(&line)), 0.0F, 1.0F);
	l.color[R] = (float)rt_atoi(nxtvp(&line)) / 255.0F;
	l.color[G] = (float)rt_atoi(nxtvp(&line)) / 255.0F;
	l.color[B] = (float)rt_atoi(nxtvp(&line)) / 255.0F;
	l.color[A] = 1.0F;
	// Hardcoded raduis, implement parsing later.
	l.l.radius = 1.0F;
	if (dynarr_insert(&sc->light_dynarr, &l) == false)
		return (errset(perr("parse_light", errno)));
	++sc->l_arr_size;
	++vc->light_amount;
	return (SUCCESS);
}

// int16_t	parse_light(t_scene *sc, t_value_check *vc, char *line)
// {
// 	sc->light.coords[X] = rt_atof(line);
// 	sc->light.coords[Y] = rt_atof(nxtvp(&line));
// 	sc->light.coords[Z] = rt_atof(nxtvp(&line));
// 	sc->light.l.brightness = range(rt_atof(nxtvp(&line)), 0.0F, 1.0F);
// 	sc->light.color[R] = (float)rt_atoi(nxtvp(&line)) / 255.0F;
// 	sc->light.color[G] = (float)rt_atoi(nxtvp(&line)) / 255.0F;
// 	sc->light.color[B] = (float)rt_atoi(nxtvp(&line)) / 255.0F;
// 	sc->light.color[A] = 1.0F;
// 	++vc->light_amount;
// 	return (SUCCESS);
// }

#include "../include/minirt_param.h"

t_short	parse_amb(t_scene *sc, t_value_check *vc, char *line)
{
	sc->ambient.ratio = range(rt_atof(line), 0.0f, 1.0f);
	sc->ambient.color[R] = rt_atoi(nxtvp(&line));
	sc->ambient.color[G] = rt_atoi(nxtvp(&line));
	sc->ambient.color[B] = rt_atoi(nxtvp(&line));
	sc->ambient.color[A] = 255;
	vc->amb_amount++;
	return (SUCCESS);
}

t_short	parse_cam(t_scene *sc, t_value_check *vc, char *line)
{
	sc->cam.point[X] = rt_atof(line);
	sc->cam.point[Y] = rt_atof(nxtvp(&line));
	sc->cam.point[Z] = rt_atof(nxtvp(&line));
	sc->cam.orient[X] = range(rt_atof(nxtvp(&line)), -1.0f, 1.0f);
	sc->cam.orient[Y] = range(rt_atof(nxtvp(&line)), -1.0f, 1.0f);
	sc->cam.orient[Z] = range(rt_atof(nxtvp(&line)), -1.0f, 1.0f);
	sc->cam.fov = range(rt_atoi(nxtvp(&line)), 0.0f, 180.0f);
	sc->z_dist = 1.0f / tanf((sc->cam.fov * M_PI / 180.0f) / 2.0f);
	sc->realtime_fov = (float)sc->cam.fov;
	vc->cam_amount++;
	return (SUCCESS);
}

t_short	parse_light(t_scene *sc, t_value_check *vc, char *line)
{
	sc->light.point[X] = rt_atof(line);
	sc->light.point[Y] = rt_atof(nxtvp(&line));
	sc->light.point[Z] = rt_atof(nxtvp(&line));
	sc->light.brightness = range(rt_atof(nxtvp(&line)), 0.0f, 1.0f);
	sc->light.color[R] = rt_atoi(nxtvp(&line));
	sc->light.color[G] = rt_atoi(nxtvp(&line));
	sc->light.color[B] = rt_atoi(nxtvp(&line));
	sc->light.color[A] = 255;
	vc->light_amount++;
	return (SUCCESS);
}

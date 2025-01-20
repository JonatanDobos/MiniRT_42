#include <parsing.h>
#include <math.h>
#include <utils.h>

int16_t	parse_amb(t_scene *sc, t_value_check *vc, char *line)
{
	sc->ambient.ambient.ratio = range(rt_atof(line), 0.0f, 1.0f);
	sc->ambient.color.r = rt_atoi(nxtvp(&line));
	sc->ambient.color.g = rt_atoi(nxtvp(&line));
	sc->ambient.color.b = rt_atoi(nxtvp(&line));
	sc->ambient.color.a = 255;
	vc->amb_amount++;
	return (SUCCESS);
}

int16_t	parse_cam(t_scene *sc, t_value_check *vc, char *line)
{
	sc->camera.coords[X] = rt_atof(line);
	sc->camera.coords[Y] = rt_atof(nxtvp(&line));
	sc->camera.coords[Z] = rt_atof(nxtvp(&line));
	sc->camera.camera.orientation[X] = range(rt_atof(nxtvp(&line)), -1.0f, 1.0f);
	sc->camera.camera.orientation[Y] = range(rt_atof(nxtvp(&line)), -1.0f, 1.0f);
	sc->camera.camera.orientation[Z] = range(rt_atof(nxtvp(&line)), -1.0f, 1.0f);
	sc->camera.camera.fov = range(rt_atoi(nxtvp(&line)), 0.0f, 180.0f);
	sc->camera.camera.zvp_dist = 1.0f / tanf((sc->camera.camera.fov * M_PI / 180.0f) / 2.0f);
	sc->camera.camera.realtime_fov = sc->camera.camera.fov;
	vc->cam_amount++;
	return (SUCCESS);
}

int16_t	parse_light(t_scene *sc, t_value_check *vc, char *line)
{
	sc->light.coords[X] = rt_atof(line);
	sc->light.coords[Y] = rt_atof(nxtvp(&line));
	sc->light.coords[Z] = rt_atof(nxtvp(&line));
	sc->light.light.brightness = range(rt_atof(nxtvp(&line)), 0.0f, 1.0f);
	sc->light.color.r = rt_atoi(nxtvp(&line));
	sc->light.color.g = rt_atoi(nxtvp(&line));
	sc->light.color.b = rt_atoi(nxtvp(&line));
	sc->light.color.a = 255;
	vc->light_amount++;
	return (SUCCESS);
}

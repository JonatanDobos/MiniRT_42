#include "../include/minirt_param.h"

t_short	parse_amb(t_scene *sc, t_value_check *vc, char *line)
{
	sc->ambient.ratio = range(rt_atof(line), 0.0f, 1.0f);
	sc->ambient.color.r = rt_atoi(nxtvalue(line));
	sc->ambient.color.g = rt_atoi(nxtvalue(line));
	sc->ambient.color.b = rt_atoi(nxtvalue(line));
	sc->ambient.color.a = 255;
	vc->amb_amount++;
	return (SUCCESS);
}

t_short	parse_cam(t_scene *sc, t_value_check *vc, char *line)
{
	sc->cam.point.x = rt_atof(line);
	sc->cam.point.y = rt_atof(nxtvalue(line));
	sc->cam.point.z = rt_atof(nxtvalue(line));
	sc->cam.orient.x = range(rt_atof(nxtvalue(line)), -1.0f, 1.0f);
	sc->cam.orient.y = range(rt_atof(nxtvalue(line)), -1.0f, 1.0f);
	sc->cam.orient.z = range(rt_atof(nxtvalue(line)), -1.0f, 1.0f);
	sc->cam.fov = range(rt_atoi(nxtvalue(line)), 0.0f, 180.0f);
	vc->cam_amount++;
	return (SUCCESS);
}

t_short	parse_light(t_scene *sc, t_value_check *vc, char *line)
{
	sc->light.point.x = rt_atof(line);
	sc->light.point.y = rt_atof(nxtvalue(line));
	sc->light.point.z = rt_atof(nxtvalue(line));
	sc->light.brightness = range(rt_atof(nxtvalue(line)), 0.0f, 1.0f);
	sc->light.color.r = rt_atoi(nxtvalue(line));
	sc->light.color.g = rt_atoi(nxtvalue(line));
	sc->light.color.b = rt_atoi(nxtvalue(line));
	sc->light.color.a = 255;
	vc->light_amount++;
	return (SUCCESS);
}

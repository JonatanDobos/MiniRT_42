#include "../include/minirt_param.h"

t_short	parse_amb(t_scene *sc, t_value_check *vc, char *line)
{
	sc->ambient.ratio = rt_atof(line);
	if (sc->ambient.ratio < 0.0f || sc->ambient.ratio > 1.0f)
		sc->ambient.ratio = 1.0f;
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
	sc->cam.orient.x = rt_atof(nxtvalue(line));
	sc->cam.orient.y = rt_atof(nxtvalue(line));
	sc->cam.orient.z = rt_atof(nxtvalue(line));
	sc->cam.fov = rt_atoi(nxtvalue(line));
	if (sc->cam.fov > 180)
		sc->cam.fov = 180;
	vc->cam_amount++;
	return (SUCCESS);
}

t_short	parse_light(t_scene *sc, t_value_check *vc, char *line)
{
	sc->light.point.x = rt_atof(line);
	sc->light.point.y = rt_atof(nxtvalue(line));
	sc->light.point.z = rt_atof(nxtvalue(line));
	sc->light.brightness = rt_atof(nxtvalue(line));
	if (sc->light.brightness < 0.0f || sc->light.brightness > 1.0f)
		sc->light.brightness = 1.0f;
	sc->light.color.r = rt_atoi(nxtvalue(line));
	sc->light.color.g = rt_atoi(nxtvalue(line));
	sc->light.color.b = rt_atoi(nxtvalue(line));
	sc->light.color.a = 255;
	vc->light_amount++;
	return (SUCCESS);
}

t_short	parse_pl(t_scene *sc, t_value_check *vc, char *line)
{
	(void)sc;
	(void)vc;
	(void)line;
	return (SUCCESS);
}

t_short	parse_sp(t_scene *sc, t_value_check *vc, char *line)
{
	(void)sc;
	(void)vc;
	(void)line;
	return (SUCCESS);
}

t_short	parse_cy(t_scene *sc, t_value_check *vc, char *line)
{
	(void)sc;
	(void)vc;
	(void)line;
	return (SUCCESS);
}

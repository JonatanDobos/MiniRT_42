#include "../include/minirt_param.h"

t_short	parse_amb(t_scene *sc, t_value_check *vc, char *line)
{
	sc->ambient.ratio = range(rt_atof(line), 0.0f, 1.0f);
	sc->ambient.color.r = rt_atoi(nxtvp(&line));
	sc->ambient.color.g = rt_atoi(nxtvp(&line));
	sc->ambient.color.b = rt_atoi(nxtvp(&line));
	sc->ambient.color.a = 255;
	vc->amb_amount++;
	printf("\nAmbient Light:\n"
       "  Ratio: %.2f\n"
       "  Color: (r: %d, g: %d, b: %d, a: %d)\n",
       sc->ambient.ratio,
       sc->ambient.color.r, sc->ambient.color.g, sc->ambient.color.b, sc->ambient.color.a);//t
	return (SUCCESS);
}

t_short	parse_cam(t_scene *sc, t_value_check *vc, char *line)
{
	sc->cam.point.x = rt_atof(line);
	sc->cam.point.y = rt_atof(nxtvp(&line));
	sc->cam.point.z = rt_atof(nxtvp(&line));
	sc->cam.orient.x = range(rt_atof(nxtvp(&line)), -1.0f, 1.0f);
	sc->cam.orient.y = range(rt_atof(nxtvp(&line)), -1.0f, 1.0f);
	sc->cam.orient.z = range(rt_atof(nxtvp(&line)), -1.0f, 1.0f);
	sc->cam.fov = range(rt_atoi(nxtvp(&line)), 0.0f, 180.0f);
	vc->cam_amount++;
	printf("\nCamera:\n"
       "  Position: (x: %.2f, y: %.2f, z: %.2f)\n"
       "  Orientation: (x: %.2f, y: %.2f, z: %.2f)\n"
       "  FOV: %d\n",
       sc->cam.point.x, sc->cam.point.y, sc->cam.point.z,
       sc->cam.orient.x, sc->cam.orient.y, sc->cam.orient.z,
       sc->cam.fov);//t
	return (SUCCESS);
}

t_short	parse_light(t_scene *sc, t_value_check *vc, char *line)
{
	sc->light.point.x = rt_atof(line);
	sc->light.point.y = rt_atof(nxtvp(&line));
	sc->light.point.z = rt_atof(nxtvp(&line));
	sc->light.brightness = range(rt_atof(nxtvp(&line)), 0.0f, 1.0f);
	sc->light.color.r = rt_atoi(nxtvp(&line));
	sc->light.color.g = rt_atoi(nxtvp(&line));
	sc->light.color.b = rt_atoi(nxtvp(&line));
	sc->light.color.a = 255;
	vc->light_amount++;
	printf("\nLight:\n"
       "  Position: (x: %.2f, y: %.2f, z: %.2f)\n"
       "  Brightness: %.2f\n"
       "  Color: (r: %d, g: %d, b: %d, a: %d)\n",
       sc->light.point.x, sc->light.point.y, sc->light.point.z,
       sc->light.brightness,
       sc->light.color.r, sc->light.color.g, sc->light.color.b, sc->light.color.a);//t
	return (SUCCESS);
}

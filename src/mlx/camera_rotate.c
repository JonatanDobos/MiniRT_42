#include <RTmlx.h>
#include <scene.h>
#include <utils.h>
#include <mathRT.h>

void	cam_rotate_up(t_scene *sc)
{
	t_vec4 right = vcross(sc->camera.c.orientation, (t_vec4){0, 1, 0});
	sc->camera.c.orientation = vnorm(vrotate(sc->camera.c.orientation, right, sc->cam_r_speed));
	sc->render = true;
}

void	cam_rotate_down(t_scene *sc)
{
	t_vec4 right = vcross(sc->camera.c.orientation, (t_vec4){0, 1, 0});
	sc->camera.c.orientation = vnorm(vrotate(sc->camera.c.orientation, right, -sc->cam_r_speed));
	sc->render = true;
}

void	cam_rotate_left(t_scene *sc)
{
	sc->camera.c.orientation = vnorm(vrotate(sc->camera.c.orientation, (t_vec4){0, 1, 0}, -sc->cam_r_speed));
	sc->render = true;
}

void	cam_rotate_right(t_scene *sc)
{
	sc->camera.c.orientation = vnorm(vrotate(sc->camera.c.orientation, (t_vec4){0, 1, 0}, sc->cam_r_speed));
	sc->render = true;
}

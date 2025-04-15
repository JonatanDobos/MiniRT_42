#include <scene.h>
#include <mathRT.h>

void	cam_move_forw(t_scene *sc)
{
	sc->camera.coords += sc->camera.c.orientation * bcast3(sc->camera.c.cam_m_speed);
	sc->render = true;
}

void	cam_move_backw(t_scene *sc)
{
	sc->camera.coords -= sc->camera.c.orientation * bcast3(sc->camera.c.cam_m_speed);
	sc->render = true;
}

void	cam_move_right(t_scene *sc)
{
	const t_vec4	right = vnorm(vcross(sc->camera.c.orientation, (t_vec4){0.0F, 1.0F, 0.0F}));

	sc->camera.coords -= right * bcast3(sc->camera.c.cam_m_speed);
	sc->render = true;
}

void	cam_move_left(t_scene *sc)
{
	const t_vec4	left = vnorm(vcross(sc->camera.c.orientation, (t_vec4){0.0F, 1.0F, 0.0F}));

	sc->camera.coords += left * bcast3(sc->camera.c.cam_m_speed);
	sc->render = true;
}

void	cam_move_up(t_scene *sc)
{
	sc->camera.coords[Y] += sc->camera.c.cam_m_speed;
	sc->render = true;
}

void	cam_move_down(t_scene *sc)
{
	sc->camera.coords[Y] -= sc->camera.c.cam_m_speed;
	sc->render = true;
}

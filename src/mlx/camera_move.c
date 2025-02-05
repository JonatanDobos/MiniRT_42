#include <scene.h>
#include <utils.h>
#include <mathRT.h>

void	cam_move_forw(t_scene *sc)
{
	const t_vec4	speed = bcast3(sc->cam_m_speed);

	sc->camera.coords += sc->camera.c.orientation * speed;
	sc->render = true;
}

void	cam_move_backw(t_scene *sc)
{
	const t_vec4	speed = bcast3(sc->cam_m_speed);

	sc->camera.coords -= sc->camera.c.orientation * speed;
	sc->render = true;
}

void	cam_move_right(t_scene *sc)
{
	const t_vec4	speed = bcast3(sc->cam_m_speed);
	const t_vec4	right = vnorm(vcross(sc->camera.c.orientation, (t_vec4){0.0F, 1.0F, 0.0F}));

	sc->camera.coords -= right * speed;
	sc->render = true;
}

void	cam_move_left(t_scene *sc)
{
	const t_vec4	speed = bcast3(sc->cam_m_speed);
	const t_vec4	left = vnorm(vcross(sc->camera.c.orientation, (t_vec4){0.0F, 1.0F, 0.0F}));

	sc->camera.coords += left * speed;
	sc->render = true;
}

void	cam_move_up(t_scene *sc)
{
	sc->camera.coords[Y] += sc->cam_m_speed;
	sc->render = true;
}

void	cam_move_down(t_scene *sc)
{
	sc->camera.coords[Y] -= sc->cam_m_speed;
	sc->render = true;
}

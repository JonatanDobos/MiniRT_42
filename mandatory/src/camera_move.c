#include "../include/minirt_param.h"

void	cam_move_forw(t_scene *sc)
{
	sc->cam.point += sc->cam.orient * CAM_MOVE_SPEED;
	printf("\033[0;36m W\033[0m\n");
	sc->render = true;
}

void	cam_move_backw(t_scene *sc)
{
	sc->cam.point -= sc->cam.orient * CAM_MOVE_SPEED;
	printf("\033[0;36m S\033[0m\n");
	sc->render = true;
}

void	cam_move_right(t_scene *sc)
{
	const t_vec4	right = vec_normalize(vec_cross(sc->cam.orient, (t_vec4){0, 1, 0}));

	sc->cam.point -= right * CAM_MOVE_SPEED;
	printf("\033[0;36m D\033[0m\n");
	sc->render = true;
}

void	cam_move_left(t_scene *sc)
{
	const t_vec4	left = vec_normalize(vec_cross(sc->cam.orient, (t_vec4){0, 1, 0}));

	sc->cam.point += left * CAM_MOVE_SPEED;
	printf("\033[0;36m A\033[0m\n");
	sc->render = true;
}

void	cam_move_up(t_scene *sc)
{
	sc->cam.point[Y] += CMS;
	printf("\033[0;36m SPACE\033[0m\n");
	sc->render = true;
}

void	cam_move_down(t_scene *sc)
{
	sc->cam.point[Y] -= CMS;
	printf("\033[0;36m SHIFT\033[0m\n");
	sc->render = true;
}

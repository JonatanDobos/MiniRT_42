#include "../include/minirt_param.h"

void	cam_move_forw(t_scene *sc)
{
	sc->cam.point += sc->cam.orient * CAM_MOVE_SPEED;
	printf("KEY: W\n");
	sc->render = true;
}

void	cam_move_backw(t_scene *sc)
{
	sc->cam.point -= sc->cam.orient * CAM_MOVE_SPEED;
	printf("KEY: S\n");
	sc->render = true;
}

void	cam_move_right(t_scene *sc)
{
	const t_vec4	right = vec_normalize(vec_cross(sc->cam.orient, (t_vec4){0, 1, 0}));

	sc->cam.point += right * CAM_MOVE_SPEED;
	printf("KEY: D\n");
	sc->render = true;
}

void	cam_move_left(t_scene *sc)
{
	const t_vec4	right = vec_normalize(vec_cross(sc->cam.orient, (t_vec4){0, 1, 0}));

	sc->cam.point -= right * CAM_MOVE_SPEED;
	printf("KEY: A\n");
	sc->render = true;
}

void	cam_move_up(t_scene *sc)
{
	sc->cam.point[Y] += CMS;
	printf("KEY: SPACE\n");
	sc->render = true;
}

void	cam_move_down(t_scene *sc)
{
	sc->cam.point[Y] -= CMS;
	printf("KEY: SHIFT\n");
	sc->render = true;
}

#include <RTmlx.h>
#include <scene.h>
#include <utils.h>

void	cam_move_forw(t_scene *sc)
{
	sc->camera.coords += sc->camera.c.orientation * CAM_MOVE_SPEED;
	printf("\033[0;36m move W (forward)\033[0m\n");
	sc->render = true;
}

void	cam_move_backw(t_scene *sc)
{
	sc->camera.coords -= sc->camera.c.orientation * CAM_MOVE_SPEED;
	printf("\033[0;36m move S (backward)\033[0m\n");
	sc->render = true;
}

void	cam_move_right(t_scene *sc)
{
	const t_vec4	right = normalize(cross(sc->camera.c.orientation, (t_vec4){0, 1, 0}));

	sc->camera.coords += right * CAM_MOVE_SPEED;
	printf("\033[0;36m move D (right)\033[0m\n");
	sc->render = true;
}

void	cam_move_left(t_scene *sc)
{
	const t_vec4	right = normalize(cross(sc->camera.c.orientation, (t_vec4){0, 1, 0}));

	sc->camera.coords -= right * CAM_MOVE_SPEED;
	printf("\033[0;36m move A (left)\033[0m\n");
	sc->render = true;
}

void	cam_move_up(t_scene *sc)
{
	sc->camera.coords[Y] += CMS;
	printf("\033[0;36m move SPACE (up)\033[0m\n");
	sc->render = true;
}

void	cam_move_down(t_scene *sc)
{
	sc->camera.coords[Y] -= CMS;
	printf("\033[0;36m move LSHIFT (down)\033[0m\n");
	sc->render = true;
}

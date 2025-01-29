#include <RTmlx.h>
#include <scene.h>
#include <utils.h>

void	cam_move_forw(t_scene *sc)
{
	const t_vec4	speed = bcast4(CAM_MOVE_SPEED);

	sc->camera.coords += sc->camera.c.orientation * speed;
	// printf("KEY: W\n");
	sc->render = true;
}

void	cam_move_backw(t_scene *sc)
{
	const t_vec4	speed = bcast4(CAM_MOVE_SPEED);

	sc->camera.coords -= sc->camera.c.orientation * speed;
	// printf("KEY: S\n");
	sc->render = true;
}

void	cam_move_right(t_scene *sc)
{
	const t_vec4	speed = bcast4(CAM_MOVE_SPEED);
	const t_vec4	right = normalize(cross(sc->camera.c.orientation, (t_vec4){0, 1, 0}));

	sc->camera.coords -= right * speed;
	// printf("KEY: D\n");
	sc->render = true;
}

void	cam_move_left(t_scene *sc)
{
	const t_vec4	speed = bcast4(CAM_MOVE_SPEED);
	const t_vec4	left = normalize(cross(sc->camera.c.orientation, (t_vec4){0, 1, 0}));

	sc->camera.coords += left * speed;
	// printf("KEY: A\n");
	sc->render = true;
}

void	cam_move_up(t_scene *sc)
{
	sc->camera.coords[Y] += CAM_MOVE_SPEED;
	// printf("KEY: SPACE\n");
	sc->render = true;
}

void	cam_move_down(t_scene *sc)
{
	sc->camera.coords[Y] -= CAM_MOVE_SPEED;
	// printf("KEY: SHIFT\n");
	sc->render = true;
}

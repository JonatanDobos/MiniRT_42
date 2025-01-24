#include "../include/minirt_param.h"

// Rotate the camera orientation up
void	cam_rotate_up(t_scene *sc)
{
	printf("\033[0;36m UP\033[0m\n");
	t_vec4 right = vec_cross(sc->cam.orient, (t_vec4){0, 1, 0});
	sc->cam.orient = vec_normalize(vec_rotate(sc->cam.orient, right, sc->cam_r_speed));
	sc->render = true;
}

// Rotate the camera orientation down
void	cam_rotate_down(t_scene *sc)
{
	printf("\033[0;36m DOWN\033[0m\n");
	t_vec4 right = vec_cross(sc->cam.orient, (t_vec4){0, 1, 0});
	sc->cam.orient = vec_normalize(vec_rotate(sc->cam.orient, right, -sc->cam_r_speed));
	sc->render = true;
}

// Rotate the camera orientation left
void	cam_rotate_left(t_scene *sc)
{
	printf("\033[0;36m LEFT\033[0m\n");
	sc->cam.orient = vec_normalize(vec_rotate(sc->cam.orient, (t_vec4){0, 1, 0}, -sc->cam_r_speed));
	sc->render = true;
}

// Rotate the camera orientation right
void	cam_rotate_right(t_scene *sc)
{
	printf("\033[0;36m RIGHT\033[0m\n");
	sc->cam.orient = vec_normalize(vec_rotate(sc->cam.orient, (t_vec4){0, 1, 0}, sc->cam_r_speed));
	sc->render = true;
}

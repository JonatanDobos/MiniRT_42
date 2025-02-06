#include <scene.h>
#include <utils.h>
#include <mathRT.h>
#include <RTmlx.h>

void	obj_move_forw(t_scene *sc)
{
	double	time;

	time = mlx_get_time();
	sc->selected_obj->coords[Z] += 0.3F * time;
}

void	obj_move_backw(t_scene *sc)
{
	sc->selected_obj->coords[Z] -= 0.3F;
}

void	obj_move_left(t_scene *sc)
{
	sc->selected_obj->coords[X] -= 0.3F;
}

void	obj_move_right(t_scene *sc)
{
	sc->selected_obj->coords[X] += 0.3F;
}

void	obj_move_up(t_scene *sc)
{
	sc->selected_obj->coords[Y] += 0.3F;
}

void	obj_move_down(t_scene *sc)
{
	sc->selected_obj->coords[Y] -= 0.3F;
}
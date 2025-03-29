#include <scene.h>
#include <utils.h>
#include <mathRT.h>
#include <RTmlx.h>

void	obj_rotate_up(t_scene *sc)
{
	t_vec4 right = vcross(sc->camera.c.orientation, (t_vec4){0.0F, 1.0F, 0.0F});
	if (sc->selected_obj->type == PLANE)
	{
		sc->selected_obj->plane.orientation = vnorm(vrotate(sc->selected_obj->plane.orientation, right, sc->cam_r_speed));
	}
	else if (sc->selected_obj->type == CYLINDER)
	{
		sc->selected_obj->cylinder.orientation = vnorm(vrotate(sc->selected_obj->cylinder.orientation, right, sc->cam_r_speed));
	}
	sc->render = true;
}

void	obj_rotate_down(t_scene *sc)
{
	t_vec4 right = vcross(sc->camera.c.orientation, (t_vec4){0.0F, 1.0F, 0.0F});
	if (sc->selected_obj->type == PLANE)
	{
		sc->selected_obj->plane.orientation = vnorm(vrotate(sc->selected_obj->plane.orientation, right, -sc->cam_r_speed));
	}
	else if (sc->selected_obj->type == CYLINDER)
	{
		sc->selected_obj->cylinder.orientation = vnorm(vrotate(sc->selected_obj->cylinder.orientation, right, -sc->cam_r_speed));
	}
	sc->render = true;
}

void	obj_rotate_left(t_scene *sc)
{
	if (sc->selected_obj->type == PLANE)
	{
		sc->selected_obj->plane.orientation = vnorm(vrotate(sc->selected_obj->plane.orientation, (t_vec4){0.0F, 1.0F, 0.0F}, -sc->cam_r_speed));
	}
	else if (sc->selected_obj->type == CYLINDER)
	{
		sc->selected_obj->cylinder.orientation = vnorm(vrotate(sc->selected_obj->cylinder.orientation, (t_vec4){0.0F, 1.0F, 0.0F}, -sc->cam_r_speed));
	}
	sc->render = true;
}

void	obj_rotate_right(t_scene *sc)
{
	if (sc->selected_obj->type == PLANE)
	{
		sc->selected_obj->plane.orientation = vnorm(vrotate(sc->selected_obj->plane.orientation, (t_vec4){0.0F, 1.0F, 0.0F}, sc->cam_r_speed));
	}
	else if (sc->selected_obj->type == CYLINDER)
	{
		sc->selected_obj->cylinder.orientation = vnorm(vrotate(sc->selected_obj->cylinder.orientation, (t_vec4){0.0F, 1.0F, 0.0F}, sc->cam_r_speed));
	}
	sc->render = true;
}
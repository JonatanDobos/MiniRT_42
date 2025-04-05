#include <scene.h>
#include <mathRT.h>
#include <RTmlx.h>

void	obj_rotate_up(t_scene *sc)
{
	const t_vec4	right = vcross(sc->camera.c.orientation, (t_vec4){0.0F, 1.0F, 0.0F});
	t_objs			*picked;

	picked = sc->selected_obj;
	if (picked->type == PLANE)
	{
		picked->plane.orientation = vnorm( \
		vrotate(picked->plane.orientation, right, sc->cam_r_speed));
	}
	else if (picked->type == CYLINDER)
	{
		picked->cylinder.orientation = vnorm( \
		vrotate(picked->cylinder.orientation, right, sc->cam_r_speed));
	}
	sc->render = true;
}

void	obj_rotate_down(t_scene *sc)
{
	const t_vec4	right = vcross(sc->camera.c.orientation, (t_vec4){0.0F, 1.0F, 0.0F});
	t_objs			*picked;

	picked = sc->selected_obj;
	if (picked->type == PLANE)
	{
		picked->plane.orientation = vnorm( \
		vrotate(picked->plane.orientation, right, -sc->cam_r_speed));
	}
	else if (picked->type == CYLINDER)
	{
		picked->cylinder.orientation = vnorm( \
		vrotate(picked->cylinder.orientation, right, -sc->cam_r_speed));
	}
	sc->render = true;
}

void	obj_rotate_left(t_scene *sc)
{
	const t_vec4	rotation_axis = {0.0F, 1.0F, 0.0F};
	t_objs			*picked;

	picked = sc->selected_obj;
	if (picked->type == PLANE)
	{
		picked->plane.orientation = vnorm( \
		vrotate(picked->plane.orientation, rotation_axis, -sc->cam_r_speed));
	}
	else if (picked->type == CYLINDER)
	{
		picked->cylinder.orientation = vnorm( \
		vrotate(picked->cylinder.orientation, rotation_axis, -sc->cam_r_speed));
	}
	sc->render = true;
}

void	obj_rotate_right(t_scene *sc)
{
	const t_vec4	rotation_axis = {0.0F, 1.0F, 0.0F};
	t_objs			*picked;

	picked = sc->selected_obj;
	if (picked->type == PLANE)
	{
		picked->plane.orientation = vnorm( \
		vrotate(picked->plane.orientation, rotation_axis, sc->cam_r_speed));
	}
	else if (picked->type == CYLINDER)
	{
		picked->cylinder.orientation = vnorm( \
		vrotate(picked->cylinder.orientation, rotation_axis, sc->cam_r_speed));
	}
	sc->render = true;
}

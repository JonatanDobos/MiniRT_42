#include <RTmlx.h>
#include <scene.h>

#define RADIUS true
#define HEIGHT false

//	Static Functions
static void	select_obj_left(t_scene *sc);
static void	select_obj_right(t_scene *sc);
static void	increase_obj(t_objs *selected_obj, bool radius_or_height);
static void	decrease_obj(t_objs *selected_obj, bool radius_or_height);

bool	handle_object_modification(const keys_t key, t_scene *sc)
{
	if (key == MLX_KEY_V)
		select_obj_left(sc);
	else if (key == MLX_KEY_N)
		select_obj_right(sc);
	else if (key == MLX_KEY_B)
		sc->selected_obj = NULL;
	else if (key == MLX_KEY_M)
		decrease_obj(sc->selected_obj, HEIGHT);
	else if (key == MLX_KEY_COMMA)
		decrease_obj(sc->selected_obj, RADIUS);
	else if (key == MLX_KEY_PERIOD)
		increase_obj(sc->selected_obj, RADIUS);
	else if (key == MLX_KEY_SLASH)
		increase_obj(sc->selected_obj, HEIGHT);
	else
		return (false);
	return (true);
}

static void	select_obj_left(t_scene *sc)
{
	sc->sel_obj_index -= 1;
	if (sc->sel_obj_index == -1)
		sc->sel_obj_index = sc->o_arr_size - 1;
	sc->selected_obj = sc->objs + sc->sel_obj_index;
}

static void	select_obj_right(t_scene *sc)
{
	sc->sel_obj_index += 1;
	if (sc->sel_obj_index == sc->o_arr_size)
		sc->sel_obj_index = 0;
	sc->selected_obj = sc->objs + sc->sel_obj_index;
}

static void	increase_obj(t_objs *selected_obj, bool radius_or_height)
{
	if (selected_obj != NULL)
	{
		if (selected_obj->type == SPHERE)
		{
			selected_obj->sphere.radius *= 1.1F;
		}
		else if (radius_or_height == RADIUS)
		{
			selected_obj->cylinder.radius *= 1.1F;
		}
		else if (radius_or_height == HEIGHT)
		{
			selected_obj->cylinder.height *= 1.1F;
		}
	}
}

static void	decrease_obj(t_objs *selected_obj, bool radius_or_height)
{
	if (selected_obj != NULL)
	{
		if (selected_obj->type == SPHERE && selected_obj->sphere.radius > 0.01F)
		{
			selected_obj->sphere.radius /= 1.1F;
		}
		else if (radius_or_height == RADIUS && selected_obj->cylinder.radius > 0.01F)
		{
			selected_obj->cylinder.radius /= 1.1F;
		}
		else if (radius_or_height == HEIGHT && selected_obj->cylinder.height > 0.01F)
		{
			selected_obj->cylinder.height /= 1.1F;
		}
	}
}

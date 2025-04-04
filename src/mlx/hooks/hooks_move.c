#include <RTmlx.h>
#include <scene.h>
#include <mathRT.h>
#include <render.h>

//	Static Functions
static void	cam_hook(t_rt *rt);
static void	obj_hook(t_rt *rt);
static void	mouse_clicks_on_obj(t_scene *scene, t_ray ray);

void	movement(t_rt *rt)
{
	if (rt->win->file_creation == false)
	{
		if (rt->scene->selected_obj == NULL)
		{
			cam_hook(rt);
		}
		else
		{
			obj_hook(rt);
		}
	}
}

static void	cam_hook(t_rt *rt)
{
	if (mlx_is_key_down(rt->win->mlx, MLX_KEY_W))
		cam_move_forw(rt->scene);
	if (mlx_is_key_down(rt->win->mlx, MLX_KEY_S))
		cam_move_backw(rt->scene);
	if (mlx_is_key_down(rt->win->mlx, MLX_KEY_D))
		cam_move_right(rt->scene);
	if (mlx_is_key_down(rt->win->mlx, MLX_KEY_A))
		cam_move_left(rt->scene);
	if (mlx_is_key_down(rt->win->mlx, MLX_KEY_SPACE))
		cam_move_up(rt->scene);
	if (mlx_is_key_down(rt->win->mlx, MLX_KEY_LEFT_SHIFT))
		cam_move_down(rt->scene);
	if (mlx_is_key_down(rt->win->mlx, MLX_KEY_LEFT))
		cam_rotate_left(rt->scene);
	if (mlx_is_key_down(rt->win->mlx, MLX_KEY_RIGHT))
		cam_rotate_right(rt->scene);
	if (mlx_is_key_down(rt->win->mlx, MLX_KEY_UP))
		cam_rotate_up(rt->scene);
	if (mlx_is_key_down(rt->win->mlx, MLX_KEY_DOWN))
		cam_rotate_down(rt->scene);
}

static void	obj_hook(t_rt *rt)
{
	if (mlx_is_key_down(rt->win->mlx, MLX_KEY_W))
		rt->scene->render = obj_move_forw(rt->scene);
	if (mlx_is_key_down(rt->win->mlx, MLX_KEY_S))
		rt->scene->render = obj_move_backw(rt->scene);
	if (mlx_is_key_down(rt->win->mlx, MLX_KEY_A))
		rt->scene->render = obj_move_left(rt->scene);
	if (mlx_is_key_down(rt->win->mlx, MLX_KEY_D))
		rt->scene->render = obj_move_right(rt->scene);
	if (mlx_is_key_down(rt->win->mlx, MLX_KEY_SPACE))
		rt->scene->render = obj_move_up(rt->scene);
	if (mlx_is_key_down(rt->win->mlx, MLX_KEY_LEFT_SHIFT))
		rt->scene->render = obj_move_down(rt->scene);
	if (rt->scene->selected_obj->type != SPHERE)
	{
		if (mlx_is_key_down(rt->win->mlx, MLX_KEY_LEFT))
			obj_rotate_left(rt->scene);
		if (mlx_is_key_down(rt->win->mlx, MLX_KEY_RIGHT))
			obj_rotate_right(rt->scene);
		if (mlx_is_key_down(rt->win->mlx, MLX_KEY_UP))
			obj_rotate_up(rt->scene);
		if (mlx_is_key_down(rt->win->mlx, MLX_KEY_DOWN))
			obj_rotate_down(rt->scene);
	}
}


void	mouse_hook(mouse_key_t button, action_t action, modifier_key_t mods, t_rt *rt)
{
	int32_t	x;
	int32_t	y;
	float	ndc_x;
	float	ndc_y;
	t_ray	ray;
	
	(void)mods;
	if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS)
	{
		mlx_get_mouse_pos(rt->win->mlx, &x, &y);
		y = (float)y / rt->win->res_ratio;
		x = (float)x / rt->win->res_ratio;
		ndc_x = (2.0F * ((x + 0.5F) / (float)rt->win->rndr_wdth) - 1.0F) * rt->win->aspectrat;
		ndc_y = 1.0F - 2.0F * ((y + 0.5F) / (float)rt->win->rndr_hght);
		ray.origin = rt->scene->camera.coords;
		ray.vec = transform_ray_dir((t_vec4){ndc_x, ndc_y, rt->scene->camera.c.zvp_dist, 0.0F}, rt->scene->camera.c.orientation);
		mouse_clicks_on_obj(rt->scene, ray);
	}
}

static void	mouse_clicks_on_obj(t_scene *sc, t_ray ray)
{
	float		closest_t;
	uint8_t		closest_intersect_type;
	t_objs		*closest_obj;
	uint32_t	closest_obj_index;

	closest_obj_index = find_closest_object(sc, ray, &closest_t, &closest_intersect_type);
	closest_obj = sc->objs + closest_obj_index;
	if (sc->intersect_lights == true)
		closest_obj = render_light(sc, ray, &closest_t, closest_obj);
	if (closest_t < INFINITY && closest_t > 0.0F)
	{
		sc->render = true;
		if (sc->selected_obj == NULL || closest_obj != sc->selected_obj)
		{
			if (closest_obj->type != LIGHT)
				sc->sel_obj_index = closest_obj_index;
			sc->selected_obj = closest_obj;
		}
		else
		{
			sc->selected_obj = NULL;
		}
	}
}

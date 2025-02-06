/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   keyhooks.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-brui <rde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/05 15:12:14 by rde-brui      #+#    #+#                 */
/*   Updated: 2025/02/06 11:47:03 by joni          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>
#include <RTmlx.h>
#include <scene.h>
#include <debug.h>
#include <render.h>

#include <mathRT.h>
#include <stdio.h>
# include <MLX42/MLX42.h>

// t_vec4 trace_ray(t_scene *scene, t_ray ray)
// {
// 	float	closest_t;
// 	uint8_t	closest_intersect_type;
// 	t_vec4	pixel_color;
// 	t_vec4	normal;
// 	t_objs	*closest_obj;
// 	t_vec4	hit_point;

// 	pixel_color = (t_vec4){0.0F, 0.0F, 0.0F, 1.0F};
// 	closest_obj = find_closest_object(scene, ray, &closest_t, &closest_intersect_type);
// 	if (closest_t < INFINITY)
// 	{
// 		pixel_color = closest_obj->color;
// 		normal = calculate_normal(closest_obj, &ray, closest_t, closest_intersect_type);
// 		hit_point = vadd(ray.origin, vscale(ray.vec, closest_t));
// 		return (calc_lighting(scene, hit_point, normal, pixel_color));
// 	}
// 	return (pixel_color);
// }

void	 mouse_clicks_on_obj(t_scene *scene, t_ray ray)
{
	float		closest_t;
	uint8_t		closest_intersect_type;
	t_vec4		pixel_color;
	t_vec4		normal;
	uint32_t	closest_obj;
	t_vec4		hit_point;

	pixel_color = (t_vec4){0.0F, 0.0F, 0.0F, 1.0F};
	closest_obj = find_closest_object(scene, ray, &closest_t, &closest_intersect_type);
	if (closest_obj != 0)
	{
		if (scene->selected_obj == NULL || closest_obj != scene->sel_obj_index)
		{
			scene->sel_obj_index = closest_obj;
			scene->selected_obj = scene->objs + closest_obj;
		}
		else
		{
			scene->selected_obj = NULL;
		}
	}
}

void	mouse_hook(mouse_key_t button, action_t action, modifier_key_t mods, t_rt *rt)
{
	static bool iets = false;
	int32_t	x;
	int32_t	y;
	float	ndc_x;
	float	ndc_y;
	t_ray	ray;

	if (iets == false)
	{
		mlx_get_mouse_pos(rt->win->mlx, &x, &y);
		y = (float)y / rt->win->res_ratio;
		x = (float)x / rt->win->res_ratio;
		ndc_x = (2.0F * ((x + 0.5F) / (float)rt->win->rndr_wdth) - 1.0F) * rt->win->aspectrat;
		ndc_y = 1.0F - 2.0F * ((y + 0.5F) / (float)rt->win->rndr_hght);
		ray.origin = rt->scene->camera.coords;
		ray.vec = transform_ray_dir((t_vec4){ndc_x, ndc_y, rt->scene->camera.c.zvp_dist, 0.0F}, rt->scene->camera.c.orientation);
		mouse_clicks_on_obj(rt->scene, ray);
		iets = true;
	}
	else
	{
		iets = false;
	}
}

void	my_keyhook(mlx_key_data_t keydata, t_rt *rt)
{
	bool	pressed_key = (keydata.action == MLX_PRESS);

	if (pressed_key == true)
	{
		if (handle_object_modification(keydata.key, rt->scene) == true)
			return ;
		if (keydata.key == MLX_KEY_1)
			print_camera(rt->scene->camera);
		if (keydata.key == MLX_KEY_EQUAL)
			rt->scene->render = res_upscale(rt->win);
		else if (keydata.key == MLX_KEY_MINUS)
			rt->scene->render = res_downscale(rt->win);
		else if (keydata.key == MLX_KEY_ESCAPE)
			mlx_close_window(rt->win->mlx);
	}
}

void	init_hooks(t_rt *rt)
{
	mlx_key_hook(rt->win->mlx, (mlx_keyfunc)my_keyhook, rt);
	mlx_loop_hook(rt->win->mlx, (mlx_closefunc)loop_hook, rt);
	mlx_mouse_hook(rt->win->mlx, (mlx_mousefunc)mouse_hook, rt);
	mlx_scroll_hook(rt->win->mlx, (mlx_cursorfunc)fov_hook, rt->scene);
}

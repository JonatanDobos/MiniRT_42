/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   keyhooks.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-brui <rde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/05 15:12:14 by rde-brui      #+#    #+#                 */
/*   Updated: 2025/02/05 16:54:14 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>
#include <RTmlx.h>
#include <scene.h>
#include <debug.h>

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


void	mouse_hook(mouse_key_t button, action_t action, modifier_key_t mods, t_rt *rt)
{
	if (button == MLX_MOUSE_BUTTON_LEFT)
		printf("check\n");
	
	int32_t	x;
	int32_t	y;
	
	mlx_get_mouse_pos(rt->win->mlx, &x, &y);

	printf("x = %d\ty = %d\n", x, y);
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

#include <RTmlx.h>
#include <mathRT.h>
#include <render.h>

//	Static Functions
static void	mouse_clicks_on_obj(t_scene *sc, t_ray ray);

void	scroll_fov_hook(double xdelta, double ydelta, t_scene *sc)
{
	(void)(xdelta);
	if (ydelta > 0 && sc->camera.c.fov > 0.1f)
	{
		sc->camera.c.fov = clamp(sc->camera.c.fov - sc->cam_fov_speed, 0.0f, 180.0f);
		sc->camera.c.zvp_dist = 1.0f / tanf((sc->camera.c.fov * M_PI / 180.0f) / 2.0f);
		sc->render = true;
	}
	else if (ydelta < 0 && sc->camera.c.fov < FOV_MAX)
	{
		sc->camera.c.fov = clamp(sc->camera.c.fov + sc->cam_fov_speed, 0.0f, 180.0f);
		sc->camera.c.zvp_dist = 1.0f / tanf((sc->camera.c.fov * M_PI / 180.0f) / 2.0f);
		sc->render = true;
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
#include <math.h>
#include <utils.h>
#include <MLX42/MLX42.h>
#include <scene.h>
#include <RTmlx.h>
#include <sys/param.h>
#include <mathRT.h>
#include <render.h>

// Lighting calculation (ambient + diffuse)
t_vec4	calculate_lighting(
	t_scene *scene, t_vec4 point, t_vec4 normal, t_vec4 obj_color)
{
	const t_vec4	scalar_amb = bcast3(scene->ambient.a.ratio);
	t_vec4			scalar_light;
	t_vec4			result;
	t_vec4			light_dir;
	float			diff;

	// Ambient lighting
	result = obj_color * scene->ambient.color * scalar_amb;

	// Diffuse lighting
	light_dir = vnorm(vsub(scene->light.coords, point));
	diff = clamp(vdot(normal, light_dir), 0.0f, 1.0f) * scene->light.l.brightness;

	scalar_light = bcast3(diff);
	result += (obj_color * scene->light.color * scalar_light);
	return (vec_clamp(result, 0.0f, 1.0f));
}

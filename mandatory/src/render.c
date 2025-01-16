#include "../include/minirt_param.h"

#define MAX_DEPTH 5

// Clamp a value between min and max
float	clamp(float value, float min, float max)
{
	return value < min ? min : (value > max ? max : value);
}

// Ray-plane intersection
bool	ray_intersect_plane(t_ray ray, t_plane *plane, float *t)
{
	float denom = vec_dot(ray.vec, plane->normal);

	if (fabs(denom) > EPSILON) {
		t_eucl diff = vec_sub(plane->point, ray.origin);
		*t = vec_dot(diff, plane->normal) / denom;
		return (*t >= 0);
	}
	return false;
}

// Ray-sphere intersection
bool	ray_intersect_sphere(t_ray ray, t_sphere *sphere, float *t)
{
	t_eucl oc = vec_sub(ray.origin, sphere->center);
	float a = vec_dot(ray.vec, ray.vec);
	float b = 2.0f * vec_dot(oc, ray.vec);
	float c = vec_dot(oc, oc) - sphere->radius * sphere->radius;
	float discriminant = b * b - 4 * a * c;

	if (discriminant < 0) return false;
	float sqrt_d = sqrtf(discriminant);
	*t = (-b - sqrt_d) / (2.0f * a);
	if (*t < 0) *t = (-b + sqrt_d) / (2.0f * a);
	return (*t >= 0);
}

// Lighting calculation (ambient + diffuse)
t_rgba	calculate_lighting(
	t_scene *scene, t_eucl point, t_eucl normal, t_rgba obj_color)
{
	t_rgba result = {0, 0, 0, 255};

	// Ambient lighting
	result.r = obj_color.r * scene->ambient.ratio * scene->ambient.color.r / 255.0f;
	result.g = obj_color.g * scene->ambient.ratio * scene->ambient.color.g / 255.0f;
	result.b = obj_color.b * scene->ambient.ratio * scene->ambient.color.b / 255.0f;

	// Diffuse lighting
	t_eucl light_dir = vec_normalize(vec_sub(scene->light.point, point));
	float diff = clamp(vec_dot(normal, light_dir), 0.0f, 1.0f) * scene->light.brightness;

	result.r += obj_color.r * diff * scene->light.color.r / 255.0f;
	result.g += obj_color.g * diff * scene->light.color.g / 255.0f;
	result.b += obj_color.b * diff * scene->light.color.b / 255.0f;

	return result;
}

// Trace a ray through the scene
t_rgba	trace_ray(t_scene *scene, t_ray ray)
{
	float t, closest_t = INFINITY;
	t_rgba pixel_color = {0, 0, 0, 255};
	t_eucl normal;

	// Check plane intersections
	for (t_uin16 i = 0; i < scene->plane_count; i++) {
		if (ray_intersect_plane(ray, &scene->plane[i], &t) && t < closest_t) {
			closest_t = t;
			normal = scene->plane[i].normal;
			pixel_color = scene->plane[i].color;
		}
	}

	// Check sphere intersections
	for (t_uin16 i = 0; i < scene->sphere_count; i++) {
		if (ray_intersect_sphere(ray, &scene->sphere[i], &t) && t < closest_t) {
			closest_t = t;
			normal = vec_normalize(vec_sub(vec_add(ray.origin, vec_mul(ray.vec, t)), scene->sphere[i].center));
			pixel_color = scene->sphere[i].color;
		}
	}

	// Apply lighting if an object was hit
	if (closest_t < INFINITY) {
		t_eucl hit_point = vec_add(ray.origin, vec_mul(ray.vec, closest_t));
		return calculate_lighting(scene, hit_point, normal, pixel_color);
	}

	return pixel_color; // Background color
}

t_eucl	transform_ray_dir(t_eucl ndc_dir, t_eucl cam_orient)
{
	// Normalize the camera orientation vector (forward direction)
	t_eucl	z_axis = vec_normalize(cam_orient);

	// Create an "up" vector (default is Y-axis in world space)
	t_eucl	up = {0, 1, 0};
	if (fabsf(z_axis.x) == 0.0f && fabsf(z_axis.z) == 0.0f) // Handle edge case where cam_orient is vertical
		up = (z_axis.y > 0) ? (t_eucl){0, 0, -1} : (t_eucl){0, 0, 1};

	// Calculate the right vector (x-axis of the camera)
	t_eucl	x_axis = vec_normalize(vec_cross(up, z_axis));

	// Calculate the up vector (y-axis of the camera, perpendicular to both)
	t_eucl	y_axis = vec_cross(z_axis, x_axis);

	// Apply the rotation matrix to the direction vector
	t_eucl world_dir = {
		x_axis.x * ndc_dir.x + y_axis.x * ndc_dir.y + z_axis.x * ndc_dir.z,
		x_axis.y * ndc_dir.x + y_axis.y * ndc_dir.y + z_axis.y * ndc_dir.z,
		x_axis.z * ndc_dir.x + y_axis.z * ndc_dir.y + z_axis.z * ndc_dir.z
	};

	return vec_normalize(world_dir);
}

// Render the scene
void	render(t_minirt *m)
{
	t_uin16	y;
	t_uin16	x;
	t_ray	ray;
	float	ndc_x;
	float	ndc_y;

	y = 0;
	while (y < m->win.rndr_hght)
	{
		x = 0;
		while (x < m->win.rndr_wdth)
		{
			ndc_x = (2 * ((x + 0.5f) / (float)m->win.rndr_wdth) - 1) * m->win.ratio_w;
			ndc_y = 1 - 2 * ((y + 0.5f) / (float)m->win.rndr_hght);
			ray.origin = m->scene.cam.point;
			ray.vec = transform_ray_dir((t_eucl){ndc_x, ndc_y, m->scene.z_dist}, m->scene.cam.orient);
			set_pixel(m, x, y, trace_ray(&m->scene, ray));
			++x;
		}
		++y;
	}
}

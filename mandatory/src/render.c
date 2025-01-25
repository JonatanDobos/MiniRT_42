#include "../include/minirt_param.h"

#define MAX_DEPTH 5

// Clamp a value between min and max
float	clamp(float value, float min, float max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}

// Clamp a vector between min and max
t_vec4	vec_clamp(t_vec4 value, float min, float max)
{
	return (t_vec4){
		clamp(value[0], min, max),
		clamp(value[1], min, max),
		clamp(value[2], min, max),
		clamp(value[3], min, max)
	};
}

// Ray-plane intersection
bool	ray_intersect_plane(t_ray ray, t_plane *plane, float *t)
{
	float denom = vec_dot(ray.vec, plane->normal);

	if (fabs(denom) > EPSILON) {
		t_vec4 diff = vec_sub(plane->point, ray.origin);
		*t = vec_dot(diff, plane->normal) / denom;
		return (*t >= 0);
	}
	return false;
}

// Ray-sphere intersection
bool	ray_intersect_sphere(t_ray ray, t_sphere *sphere, float *t)
{
	t_vec4 oc = vec_sub(ray.origin, sphere->center);
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

bool	ray_intersect_cylinder(t_ray ray, t_cylinder *cylinder, float *t)
{
	// Step 1: Compute vectors for the cylinder's axis
	t_vec4 ca = vec_normalize(cylinder->normal); // Cylinder axis (normalized)
	t_vec4 oc = vec_sub(ray.origin, cylinder->center); // Vector from ray origin to cylinder center
	// Step 2: Project ray direction and oc onto plane perpendicular to the cylinder axis
	t_vec4 rd = vec_sub(ray.vec, vec_mul(ca, vec_dot(ray.vec, ca))); // Projected ray direction
	t_vec4 oc_proj = vec_sub(oc, vec_mul(ca, vec_dot(oc, ca)));     // Projected oc
	// Step 3: Solve quadratic equation for the intersection
	float a = vec_dot(rd, rd);
	float b = 2.0f * vec_dot(rd, oc_proj);
	float c = vec_dot(oc_proj, oc_proj) - (cylinder->radius * cylinder->radius);
	float discriminant = b * b - 4 * a * c;
	if (discriminant < 0.0f)
		return false; // No intersection
	// Compute the roots of the quadratic
	float sqrt_d = sqrtf(discriminant);
	float t0 = (-b - sqrt_d) / (2.0f * a);
	float t1 = (-b + sqrt_d) / (2.0f * a);
	// Step 4: Determine the valid intersection point
	if (t0 > t1) // Ensure t0 is the smaller value
	{
		float temp = t0;
		t0 = t1;
		t1 = temp;
	}
	// Check if the intersection is within the finite height of the cylinder
	float y0 = vec_dot(ca, vec_add(oc, vec_mul(ray.vec, t0)));
	float y1 = vec_dot(ca, vec_add(oc, vec_mul(ray.vec, t1)));
	if (y0 < 0.0f || y0 > cylinder->height) // t0 is outside the height limits
	{
		if (y1 < 0.0f || y1 > cylinder->height) // t1 is also outside height limits
			return false;
		t0 = t1; // Use t1 instead
	}
	// Return the closest valid intersection
	if (t0 < 0.0f) // Intersection is behind the ray origin
		return false;
	*t = t0;
	return true;
}

// Lighting calculation (ambient + diffuse)
t_vec4	calculate_lighting(
	t_scene *scene, t_vec4 point, t_vec4 normal, t_vec4 obj_color)
{
	const t_vec4	scalar_amb = bcast3(scene->ambient.ratio);
	t_vec4			scalar_light;
	t_vec4 			result;

	// Ambient lighting
	result = obj_color * scene->ambient.color * scalar_amb;

	// Diffuse lighting
	t_vec4 light_dir = vec_normalize(vec_sub(scene->light.point, point));
	float diff = clamp(vec_dot(normal, light_dir), 0.0f, 1.0f) * scene->light.brightness;

	scalar_light = bcast3(diff);
	result += (obj_color * scene->light.color * scalar_light);
	return (vec_clamp(result, 0.0f, 1.0f));
}

// Trace a ray through the scene
t_vec4	trace_ray(t_scene *scene, t_ray ray)
{
	float t, closest_t = INFINITY;
	t_vec4 pixel_color = {0, 0, 0, 1.0};
	t_vec4 normal;

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
	// Check cylinder intersections
	for (t_uin16 i = 0; i < scene->cylinder_count; i++) {
		if (ray_intersect_cylinder(ray, &scene->cylinder[i], &t) && t < closest_t) {
			closest_t = t;
			t_vec4 hit_point = vec_add(ray.origin, vec_mul(ray.vec, t));
			normal = vec_normalize(vec_sub(hit_point, vec_add(scene->cylinder[i].center, vec_mul(scene->cylinder[i].normal, vec_dot(vec_sub(hit_point, scene->cylinder[i].center), scene->cylinder[i].normal)))));
			pixel_color = scene->cylinder[i].color;
		}
	}
	// Apply lighting if an object was hit
	if (closest_t < INFINITY) {
		t_vec4 hit_point = vec_add(ray.origin, vec_mul(ray.vec, closest_t));
		return calculate_lighting(scene, hit_point, normal, pixel_color);
	}
	return pixel_color; // Background color
}

t_vec4	transform_ray_dir(t_vec4 ndc_dir, t_vec4 cam_orient)
{
	// Normalize the camera orientation vector (forward direction)
	t_vec4	z_axis = vec_normalize(cam_orient);

	// Create an "up" vector (default is Y-axis in world space)
	t_vec4	up = {0, 1, 0};
	if (fabsf(z_axis[X]) == 0.0f && fabsf(z_axis[Z]) == 0.0f) // Handle edge case where cam_orient is vertical
		up = (z_axis[Y] > 0) ? (t_vec4){0, 0, -1} : (t_vec4){0, 0, 1};

	// Calculate the right vector (x-axis of the camera)
	t_vec4	x_axis = vec_normalize(vec_cross(up, z_axis));

	// Calculate the up vector (y-axis of the camera, perpendicular to both)
	t_vec4	y_axis = vec_cross(z_axis, x_axis);

	// Apply the rotation matrix to the direction vector
	t_vec4 world_dir = {
		x_axis[X] * ndc_dir[X] + y_axis[X] * ndc_dir[Y] + z_axis[X] * ndc_dir[Z],
		x_axis[Y] * ndc_dir[X] + y_axis[Y] * ndc_dir[Y] + z_axis[Y] * ndc_dir[Z],
		x_axis[Z] * ndc_dir[X] + y_axis[Z] * ndc_dir[Y] + z_axis[Z] * ndc_dir[Z]
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
			ndc_x = (2 * ((x + 0.5f) / (float)m->win.rndr_wdth) - 1) * m->win.aspectratio_w;
			ndc_y = 1 - 2 * ((y + 0.5f) / (float)m->win.rndr_hght);
			ray.origin = m->scene.cam.point;
			ray.vec = transform_ray_dir((t_vec4){ndc_x, ndc_y, m->scene.z_dist, 0}, m->scene.cam.orient);
			scaled_res_set_pixel(&m->win, x, y, trace_ray(&m->scene, ray));
			++x;
		}
		++y;
	}
}

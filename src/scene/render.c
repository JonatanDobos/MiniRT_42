#include <math.h>
#include <utils.h>
#include <MLX42/MLX42.h>
#include <scene.h>
#include <RTmlx.h>

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
	return (t_vec4)
	{
		clamp(value[0], min, max),
		clamp(value[1], min, max),
		clamp(value[2], min, max),
		clamp(value[3], min, max)
	};
}

// Lighting calculation (ambient + diffuse)
t_vec4	calculate_lighting(
	t_scene *scene, t_vec4 point, t_vec4 normal, t_vec4 obj_color)
{
	const t_vec4	scalar_amb = bcast3(scene->ambient.a.ratio);
	t_vec4			scalar_light;
	t_vec4 			result;

	// Ambient lighting
	result = obj_color * scene->ambient.color * scalar_amb;

	// Diffuse lighting
	t_vec4 light_dir = vec_normalize(vec_sub(scene->light.coords, point));
	float diff = clamp(vec_dot(normal, light_dir), 0.0f, 1.0f) * scene->light.l.brightness;

	scalar_light = bcast3(diff);
	result += (obj_color * scene->light.color * scalar_light);
	return (vec_clamp(result, 0.0f, 1.0f));
}

// Ray-plane intersection
bool	ray_intersect_plane(t_ray ray, t_objs *obj, float *t)
{
	float denom = vec_dot(ray.vec, obj->plane.orientation);

	if (fabs(denom) > EPSILON)
	{
		t_vec4 diff = vec_sub(obj->coords, ray.origin);
		*t = vec_dot(diff, obj->plane.orientation) / denom;
		return (*t >= 0);
	}
	return false;
}

// Ray-sphere intersection
bool	ray_intersect_sphere(t_ray ray, t_objs *obj, float *t)
{
	t_vec4 oc = vec_sub(ray.origin, obj->coords);
	float a = vec_dot(ray.vec, ray.vec);
	float b = 2.0f * vec_dot(oc, ray.vec);
	float c = vec_dot(oc, oc) - obj->sphere.diameter;
	float discriminant = b * b - 4 * a * c;

	if (discriminant < 0) return false;
	float sqrt_d = sqrtf(discriminant);
	*t = (-b - sqrt_d) / (2.0f * a);
	if (*t < 0) *t = (-b + sqrt_d) / (2.0f * a);			//	joni pony, dit doet letterlijk niks met een ; erachter
	return (*t >= 0);
}

bool	ray_intersect_cylinder(t_ray ray, t_objs *obj, float *t)
{
	// Step 1: Compute vectors for the cylinder's axis
	t_vec4 ca = vec_normalize(obj->cylinder.orientation); // Cylinder axis (normalized)
	t_vec4 oc = vec_sub(ray.origin, obj->coords); // Vector from ray origin to obj->cylinder center
	// Step 2: Project ray direction and oc onto plane perpendicular to the obj->cylinder axis
	t_vec4 rd = vec_sub(ray.vec, vec_mul(ca, vec_dot(ray.vec, ca))); // Projected ray direction
	t_vec4 oc_proj = vec_sub(oc, vec_mul(ca, vec_dot(oc, ca)));     // Projected oc
	// Step 3: Solve quadratic equation for the intersection
	float a = vec_dot(rd, rd);
	float b = 2.0f * vec_dot(rd, oc_proj);
	float c = vec_dot(oc_proj, oc_proj) - (obj->cylinder.diameter);
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
	// Check if the intersection is within the finite height of the obj->cylinder
	float y0 = vec_dot(ca, vec_add(oc, vec_mul(ray.vec, t0)));
	float y1 = vec_dot(ca, vec_add(oc, vec_mul(ray.vec, t1)));
	if (y0 < 0.0f || y0 > obj->cylinder.height) // t0 is outside the height limits
	{
		if (y1 < 0.0f || y1 > obj->cylinder.height) // t1 is also outside height limits
			return false;
		t0 = t1; // Use t1 instead
	}
	// Return the closest valid intersection
	if (t0 < 0.0f) // Intersection is behind the ray origin
		return false;
	*t = t0;
	return true;
}


// DIT MOET VERANDERD WORDEN OM MET t_objs TE WERKEN (de intersect functies callen uit de struct zelf!
// Or jumptable...

bool ray_intersect_table(t_ray ray, t_objs *obj, float *t)
{
	static bool	(*intersect_obj[NUM_OBJ_TYPES])(t_ray, t_objs *, float *) = {
		ray_intersect_plane,
		ray_intersect_sphere,
		ray_intersect_cylinder
	};

	return (intersect_obj[obj->type](ray, obj, t));
}

t_vec4	trace_ray(t_scene *scene, t_ray ray)
{
	float t, closest_t = INFINITY;
	t_vec4 pixel_color = {0, 0, 0, 1.0};
	t_vec4 coords;
	t_objs	*obj_closest_vp;

	obj_closest_vp = NULL;
	for (uint32_t i = 0; i < scene->arr_size; ++i)
	{
		if (ray_intersect_table(ray, scene->objs + i, &t) && t < closest_t)
		{
			obj_closest_vp = scene->objs + i;
			closest_t = t;
			pixel_color = scene->objs[i].color;
			if (scene->objs->type == PLANE) {
				coords = scene->objs[i].coords;
			} else if (scene->objs->type == SPHERE) {
				coords = vec_normalize(vec_sub(vec_add(ray.origin, vec_mul(ray.vec, t)), scene->objs[i].coords));
			} else if (scene->objs->type == CYLINDER) {
				t_vec4 hit_point = vec_add(ray.origin, vec_mul(ray.vec, t));
				coords = vec_normalize(vec_sub(hit_point, vec_add(scene->objs[i].coords, vec_mul(scene->objs[i].coords, vec_dot(vec_sub(hit_point, scene->objs[i].coords), scene->objs[i].coords)))));
			}
		}
	}

	// Apply lighting if an object was hit
	if (closest_t < INFINITY) {
		t_vec4 hit_point = vec_add(ray.origin, vec_mul(ray.vec, closest_t));
		return (calculate_lighting(scene, hit_point, coords, pixel_color));
	}
	return (pixel_color); // Background color
}

void	scaled_res_set_pixel(t_window *w, uint16_t x, uint16_t y, t_vec4 color)
{
	const t_vec4	to_rgba = {255.0f, 255.0f, 255.0f, 255.0f};
	uint8_t			*pixels;
	t_axis2			i;
	t_axis2			pixel;

printf("w %d\n", (uint16_t)w->ratio_w);
exit(0);
	color *= to_rgba;
	i.y = 0;
	while (i.y < (uint16_t)w->ratio_w)
	{
		i.x = 0;
		pixel.y = y * (uint16_t)w->ratio_w + i.y;
		while (i.x < (uint16_t)w->ratio_w)
		{
			pixel.x = x * (uint16_t)w->ratio_w + i.x;
			if (pixel.x > w->mlx->width || pixel.y > w->mlx->height)
				continue ;
			pixels = w->pixels + (pixel.y * w->mlx->width + pixel.x) * 4;
			*(pixels++) = (uint8_t)color[R];
			*(pixels++) = (uint8_t)color[G];
			*(pixels++) = (uint8_t)color[B];
			*(pixels++) = (uint8_t)color[A];
			++i.x;
		}
		++i.y;
	}
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
void	render(t_rt *rt)
{
	uint16_t	y;
	uint16_t	x;
	t_ray		ray;
	float		ndc_x;
	float		ndc_y;

	y = 0;
	while (y < rt->win->rndr_hght)
	{
		x = 0;
		while (x < rt->win->rndr_wdth)
		{
			ndc_x = (2 * ((x + 0.5f) / (float)rt->win->rndr_wdth) - 1) * rt->win->ratio_w;
			ndc_y = 1 - 2 * ((y + 0.5f) / (float)rt->win->rndr_hght);
			ray.origin = rt->scene->camera.coords;
			ray.vec = transform_ray_dir((t_vec4){ndc_x, ndc_y, rt->scene->camera.c.zvp_dist, 0}, rt->scene->camera.c.orientation);
			scaled_res_set_pixel(rt->win, x, y, trace_ray(rt->scene, ray));
			++x;
		}
		++y;
	}
}

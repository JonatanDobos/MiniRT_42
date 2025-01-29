#include <math.h>
#include <utils.h>
#include <MLX42/MLX42.h>
#include <scene.h>
#include <RTmlx.h>
#include <sys/param.h>


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
	t_vec4			result;
	t_vec4			light_dir;
	float			diff;

	// Ambient lighting
	result = obj_color * scene->ambient.color * scalar_amb;

	// Diffuse lighting
	light_dir = vec_normalize(vec_sub(scene->light.coords, point));
	diff = clamp(vec_dot(normal, light_dir), 0.0f, 1.0f) * scene->light.l.brightness;

	scalar_light = bcast3(diff);
	result += (obj_color * scene->light.color * scalar_light);
	return (vec_clamp(result, 0.0f, 1.0f));
}

// Ray-plane intersection
bool	ray_intersect_plane(t_ray ray, t_objs *obj, float *t)
{
	const float	denom = vec_dot(ray.vec, obj->plane.orientation);
	t_vec4		diff;

	if (fabs(denom) > EPSILON)
	{
		diff = vec_sub(obj->coords, ray.origin);
		*t = vec_dot(diff, obj->plane.orientation) / denom;
		return (*t >= 0);
	}
	return false;
}

// Ray-sphere intersection
bool	ray_intersect_sphere(t_ray ray, t_objs *obj, float *t)
{
	t_vec4	oc = vec_sub(ray.origin, obj->coords);
	float	a = vec_dot(ray.vec, ray.vec);
	float	b = 2.0f * vec_dot(oc, ray.vec);
	float	c = vec_dot(oc, oc) - obj->sphere.radius * obj->sphere.radius;
	float	discriminant = b * b - 4 * a * c;
	float	sqrt_d;

	if (discriminant < 0)
		return (false);
	sqrt_d = sqrtf(discriminant);
	*t = (-b - sqrt_d) / (2.0f * a);
	if (*t < 0)
		*t = (-b + sqrt_d) / (2.0f * a);
	return (*t >= 0);
}

// GPT START

bool intersect_cylinder_caps(t_vec4 coords, t_vec4 orientation, t_vec4 plane_point, t_vec4 plane_normal, float *t)
{
	float denom = dot_product(plane_normal, orientation);
	if (fabs(denom) > 1e-6) {
		t_vec4 p0l0 = plane_point - coords;
		*t = dot_product(p0l0, plane_normal) / denom;
		return (*t >= 0);
	}
	return false;
}

bool ray_intersect_cylinder(t_ray ray, t_objs *obj, float *t)
{
	// Step 1: Compute vectors for the cylinder's axis
	t_vec4 ca = vec_normalize(obj->cylinder.orientation); // Cylinder axis (normalized)
	t_vec4 oc = vec_sub(ray.origin, obj->coords); // Vector from ray origin to obj->cylinder center
	
	// Step 2: Project ray direction and oc onto plane perpendicular to the cylinder axis
	t_vec4 rd = vec_sub(ray.vec, vec_mul(ca, vec_dot(ray.vec, ca))); // Projected ray direction
	t_vec4 oc_proj = vec_sub(oc, vec_mul(ca, vec_dot(oc, ca)));     // Projected oc

	// Step 3: Solve quadratic equation for the intersection
	float a = vec_dot(rd, rd);
	float b = 2.0f * vec_dot(rd, oc_proj);
	float c = vec_dot(oc_proj, oc_proj) - (obj->cylinder.radius * obj->cylinder.radius);
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

	float valid_t = -1;

	if (y0 >= 0.0f && y0 <= obj->cylinder.height) // t0 is inside the height limits
		valid_t = t0;
	else if (y1 >= 0.0f && y1 <= obj->cylinder.height) // t1 is inside the height limits
		valid_t = t1;

	// Step 5: Check caps if the body intersections are invalid
	t_vec4 top_cap = vec_add(obj->coords, vec_mul(ca, obj->cylinder.height));
	t_vec4 bottom_cap = obj->coords;

	float t_top, t_bottom;
	bool hit_top = intersect_cylinder_caps(ray.origin, ray.vec, top_cap, ca, &t_top);
	bool hit_bottom = intersect_cylinder_caps(ray.origin, ray.vec, bottom_cap, ca, &t_bottom);

	// Validate cap intersections
	if (hit_top)
	{
		t_vec4 p = vec_add(ray.origin, vec_mul(ray.vec, t_top));
		if (vec_len(vec_sub(p, top_cap)) <= obj->cylinder.radius)
			valid_t = (valid_t < 0 || t_top < valid_t) ? t_top : valid_t;
	}

	if (hit_bottom)
	{
		t_vec4 p = vec_add(ray.origin, vec_mul(ray.vec, t_bottom));
		if (vec_len(vec_sub(p, bottom_cap)) <= obj->cylinder.radius)
			valid_t = (valid_t < 0 || t_bottom < valid_t) ? t_bottom : valid_t;
	}

	if (valid_t < 0)
		return false;

	*t = valid_t;
	return true;
}

// GPT END

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
	t_vec4 normal;
	t_objs	*obj_closest_vp;
	uint32_t i;

	obj_closest_vp = NULL;
	i = 0;
	while (i < scene->arr_size)
	{
		if (ray_intersect_table(ray, scene->objs + i, &t) && t < closest_t)
		{
			obj_closest_vp = scene->objs + i;
			closest_t = t;
			pixel_color = scene->objs[i].color;
			if (scene->objs[i].type == PLANE)
			{
				normal = scene->objs[i].plane.orientation;
			}
			else if (scene->objs[i].type == SPHERE)
			{
				normal = vec_normalize(vec_sub(vec_add(ray.origin, vec_mul(ray.vec, t)), scene->objs[i].coords));
			}
			else if (scene->objs[i].type == CYLINDER)
			{
				// printf("[x:%.1f, y:%.1f, z:%.1f]\n"
				// 		"[x:%.1f, y:%.1f, z:%.1f]\n"
				// 		"hallo\n\n",
				// 		ray.origin[X], ray.origin[Y], ray.origin[Z], ray.vec[X], ray.vec[Y], ray.vec[Z]);
				// exit(0);
				t_vec4 hit_point = vec_add(ray.origin, vec_mul(ray.vec, t));
				normal = vec_normalize(vec_sub(hit_point, vec_add(scene->objs[i].cylinder.orientation, vec_mul(scene->objs[i].cylinder.orientation, \
					vec_dot(vec_sub(hit_point, scene->objs[i].cylinder.orientation), scene->objs[i].cylinder.orientation)))));
			}
		}
		++i;
	}

	// Apply lighting if an object was hit
	if (closest_t < INFINITY)
	{
		static int i = 0;
		t_vec4 hit_point = vec_add(ray.origin, vec_mul(ray.vec, closest_t));
		if (obj_closest_vp->type == CYLINDER && i % 300 == 0)
			printf("CalcLight(hit_pt: [x:%.1f, y:%.1f, z:%.1f]\n"
				   "          normal: [x:%.1f, y:%.1f, z:%.1f]\n"
			       "       pixel_col: [r:%.1f, g:%.1f, b:%.1f, a:%.1f])\n\n", \
		hit_point[X], hit_point[Y], hit_point[Z], normal[X], normal[Y], normal[Z], pixel_color[R], pixel_color[G], pixel_color[B], pixel_color[A]);
		++i;
		return (calculate_lighting(scene, hit_point, normal, pixel_color));
	}
	return (pixel_color); // Background color
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

void	set_pixel(t_window *win, uint16_t x, uint16_t y, t_vec4 color)
{
	uint8_t			*pixels;
	const t_vec4	multiply = {255.0, 255.0, 255.0, 255.0};

	color *= multiply;
	pixels = win->img->pixels + (y * WINDOW_WIDTH + x) * 4;
	*(pixels++) = (uint8_t)color[R];
	*(pixels++) = (uint8_t)color[G];
	*(pixels++) = (uint8_t)color[B];
	*(pixels++) = (uint8_t)color[A];
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
			// scaled_res_set_pixel(rt->win, x, y, trace_ray(rt->scene, ray));
			set_pixel(rt->win, x, y, trace_ray(rt->scene, ray));
			++x;
		}
		++y;
	}
}

// void	scaled_res_set_pixel(t_window *w, uint16_t x, uint16_t y, t_vec4 color)
// {
// 	const t_vec4	to_rgba = {255.0f, 255.0f, 255.0f, 255.0f};
// 	uint8_t			*pixels;
// 	t_axis2			i;
// 	t_axis2			pixel;

// 	color *= to_rgba;
// 	i.y = 0;
// 	while (i.y < (uint16_t)w->ratio_w)
// 	{
// 		i.x = 0;
// 		pixel.y = y * (uint16_t)w->ratio_w + i.y;
// 		while (i.x < (uint16_t)w->ratio_w)
// 		{
// 			pixel.x = x * (uint16_t)w->ratio_w + i.x;
// 			if (pixel.x > w->mlx->width || pixel.y > w->mlx->height)
// 				continue ;
// 			pixels = w->pixels + (pixel.y * w->mlx->width + pixel.x) * 4;
// 			*(pixels++) = (uint8_t)color[R];
// 			*(pixels++) = (uint8_t)color[G];
// 			*(pixels++) = (uint8_t)color[B];
// 			*(pixels++) = (uint8_t)color[A];
// 			++i.x;
// 		}
// 		++i.y;
// 	}
// }

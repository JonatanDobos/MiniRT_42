// #include <math.h>
// #include <utils.h>
// #include <MLX42/MLX42.h>
// #include <scene.h>
// #include <RTmlx.h>

// float	intersect_plane(t_objs *obj, t_cvec4 coords, t_cvec4 orientation)
// {
// 	t_cfloat	denom = vdot(obj->plane.orientation, orientation);
// 	t_cvec4		ray_to_plane_vector = obj->coords - coords;
// 	float		intersection_distance;

// 	if (fabsf(denom) > 1e-6F) {
// 		intersection_distance = vdot(ray_to_plane_vector, obj->plane.orientation) / denom;
// 		if (intersection_distance >= 0.0F) {
// 			return (intersection_distance);
// 		}
// 	}
// 	return (-1.0F);
// }

// float	intersect_sphere(t_objs *obj, t_cvec4 coords, t_cvec4 orientation)
// {
// 	t_cvec4		oc = coords - obj->coords;
// 	t_cfloat	a = vdot(orientation, orientation);
// 	t_cfloat	b = 2.0F * vdot(oc, orientation);
// 	t_cfloat	c = vdot(oc, oc) - obj->sphere.diameter;
// 	t_cfloat	discriminant = b * b - 4.0F * a * c;

// 	if (discriminant > 0.0F)
// 	{
// 		float t0 = (-b - sqrt(discriminant)) / (2.0F * a);
// 		float t1 = (-b + sqrt(discriminant)) / (2.0F * a);
// 		if (t0 > 0.0F && t1 > 0.0F)
// 		{
// 			return ((t0 < t1) ? t0 : t1); // Choose the closest positive t value
// 		}
// 	}
// 	return (-1.0F);
// }

// // Function to check if the intersection point is within the height of the cylinder
// bool	check_height(const t_objs *obj, const t_cylinder *cyl, t_cvec4 coords, t_cvec4 orientation, float t)
// {
// 	t_cvec4		intersection_point = coords + orientation * t;
// 	t_cvec4		base_to_intersection = intersection_point - obj->coords;
// 	t_cfloat	height = vdot(base_to_intersection, vnorm(cyl->orientation));

// 	return (height >= 0.0F && height <= cyl->height);
// }

// // float	intersect_cylinder(t_objs *obj, t_cvec4 coords, t_cvec4 orientation)
// // {
// // 	t_cylinder	*cylinder = &obj->cylinder;
// // 	t_cvec4		oc = coords - obj->coords; // Use obj->coords as the base center
// // 	t_cvec4		d = vnorm(cylinder->orientation); // Ensure the direction is normalized
// // 	t_cvec4		rd = orientation - d * vdot(orientation, d);
// // 	t_cvec4		oc_d = oc - d * vdot(oc, d);

// // 	t_cfloat	a = vdot(rd, rd);
// // 	t_cfloat	b = 2.0F * vdot(rd, oc_d);
// // 	t_cfloat	c = vdot(oc_d, oc_d) - cylinder->diameter;

// // 	t_cfloat	discriminant = b * b - 4.0F * a * c;

// // 	// Debugging information
// // 	// printf("oc: (%f, %f, %f)\n", oc[0], oc[1], oc[2]);
// // 	// printf("d: (%f, %f, %f)\n", d[0], d[1], d[2]);
// // 	// printf("rd: (%f, %f, %f)\n", rd[0], rd[1], rd[2]);
// // 	// printf("oc_d: (%f, %f, %f)\n", oc_d[0], oc_d[1], oc_d[2]);
// // 	// printf("a: %f, b: %f, c: %f\n", a, b, c);
// // 	// printf("discriminant: %f\n", discriminant);

// // 	if (discriminant < 0) {
// // 		return (-1.0F);
// // 	}

// // 	t_cfloat	fast_sqrt_discriminant = sqrt(discriminant);
// // 	t_cfloat	t1 = (-b - fast_sqrt_discriminant) / (2.0F * a);
// // 	t_cfloat	t2 = (-b + fast_sqrt_discriminant) / (2.0F * a);

// // 	// More debugging information
// // 	// printf("t1: %f, t2: %f\n", t1, t2);

// // 	if (t1 >= 0.0F && check_height(obj, cylinder, coords, orientation, t1)) {
// // 		return (t1);
// // 	} else if (t2 >= 0.0F && check_height(obj, cylinder, coords, orientation, t2)) {
// // 		return (t2);
// // 	}
// // 	return (-1.0F);
// // }

// bool intersect_cylinder_caps(t_vec4 coords, t_vec4 orientation, t_vec4 plane_point, t_vec4 plane_normal, float *t)
// {
// 	float denom = vdot(plane_normal, orientation);
// 	if (fabs(denom) > 1e-6) {
// 		t_vec4 p0l0 = plane_point - coords;
// 		*t = vdot(p0l0, plane_normal) / denom;
// 		return (*t >= 0);
// 	}
// 	return false;
// }
// float length(t_vec4 v)
// {
// 	return sqrt(vdot(v, v));
// }
// float intersect_cylinder(t_objs *obj, t_cvec4 coords, t_cvec4 orientation)
// {
// 	t_cylinder *cylinder = &obj->cylinder;
// 	t_cvec4 oc = coords - obj->coords; // Use obj->coords as the base center
// 	t_cvec4 d = vnorm(cylinder->orientation); // Ensure the direction is normalized
// 	t_cvec4 rd = orientation - d * vdot(orientation, d);
// 	t_cvec4 oc_d = oc - d * vdot(oc, d);

// 	t_cfloat a = vdot(rd, rd);
// 	t_cfloat b = 2.0F * vdot(rd, oc_d);
// 	t_cfloat c = vdot(oc_d, oc_d) - cylinder->diameter;

// 	t_cfloat discriminant = b * b - 4.0F * a * c;

// 	if (discriminant < 0) {
// 		return (-1.0F);
// 	}

// 	t_cfloat fast_sqrt_discriminant = sqrt(discriminant);
// 	t_cfloat t1 = (-b - fast_sqrt_discriminant) / (2.0F * a);
// 	t_cfloat t2 = (-b + fast_sqrt_discriminant) / (2.0F * a);

// 	// Check if the intersection points are within the height of the cylinder
// 	if (check_height(obj, cylinder, coords, orientation, t1)) {
// 		return t1;
// 	}
// 	if (check_height(obj, cylinder, coords, orientation, t2)) {
// 		return t2;
// 	}

// 	// Calculate top and bottom cap centers
// 	t_vec4 top_cap = obj->coords + d * cylinder->height;
// 	t_vec4 bottom_cap = obj->coords;

// 	// Check intersection with top cap
// 	float t_top;
// 	if (intersect_cylinder_caps(coords, orientation, top_cap, d, &t_top)) {
// 		t_vec4 p = coords + t_top * orientation;
// 		if (length(p - top_cap) <= cylinder->radius) {
// 			return t_top;
// 		}
// 	}

// 	// Check intersection with bottom cap
// 	float t_bottom;
// 	if (intersect_cylinder_caps(coords, orientation, bottom_cap, d, &t_bottom)) {
// 		t_vec4 p = coords + t_bottom * orientation;
// 		if (length(p - bottom_cap) <= cylinder->radius) {
// 			return t_bottom;
// 		}
// 	}

// 	return (-1.0F);
// }

// void intersect_table(t_objs *obj, t_cvec4 coords, t_cvec4 orientation)
// {
// 	static float	(*intersect_obj[NUM_OBJ_TYPES])(t_objs *, t_cvec4, t_cvec4) = {
// 		intersect_plane,
// 		intersect_sphere,
// 		intersect_cylinder
// 	};

// 	obj->hit = intersect_obj[obj->type](obj, coords, orientation);
// }

// t_vec4	obj_nearest_vp(t_rt *rt, t_objs *objarr, t_cvec4 coords, t_cvec4 orientation)
// {
// 	uint32_t	i;
// 	t_objs		*obj_closest_vp;
// 	t_vec4		color;

// 	obj_closest_vp = NULL;
// 	for (i = 0; i < rt->scene->arr_size; ++i)
// 	{
// 		intersect_table(&objarr[i], coords, orientation);
// 		if (objarr[i].hit > 0 && (obj_closest_vp == NULL || objarr[i].hit < obj_closest_vp->hit))
// 		{
// 			obj_closest_vp = &objarr[i];
// 			color = obj_closest_vp->color;
// 		}
// 	}
// 	if (obj_closest_vp != NULL)
// 	{

// 		return (color);
// 	}
// 	return ((t_vec4){-1.0F, -1.0F, -1.0F, -1.0F});
// }

// void	set_pixel(t_window *win, uint16_t x, uint16_t y, t_vec4 color)
// {
// 	uint8_t			*pixels;
// 	const t_vec4	multiply = {255.0, 255.0, 255.0, 255.0};

// 	color *= multiply;
// 	pixels = win->img->pixels + (y * WINDOW_WIDTH + x) * 4;
// 	*(pixels++) = (uint8_t)color[R];
// 	*(pixels++) = (uint8_t)color[G];
// 	*(pixels++) = (uint8_t)color[B];
// 	*(pixels++) = (uint8_t)color[A];
// }

// // typedef struct {
// //     float fov; // Field of view in degrees
// //     float aspect_ratio; // Aspect ratio of the screen (width / height)
// //     float near_plane; // Near clipping plane
// //     float far_plane; // Far clipping plane
// // } t_camera_params;

// // void set_perspective_projection_matrix(t_camera_params *camera, float matrix[4][4]) {
// //     float fov_rad = camera->fov * (M_PI / 180.0f); // Convert FOV to radians
// //     float tan_half_fov = tan(fov_rad / 2.0f);

// //     matrix[0][0] = 1.0f / (camera->aspect_ratio * tan_half_fov);
// //     matrix[1][1] = 1.0f / tan_half_fov;
// //     matrix[2][2] = -(camera->far_plane + camera->near_plane) / (camera->far_plane - camera->near_plane);
// //     matrix[2][3] = -1.0f;
// //     matrix[3][2] = -(2.0f * camera->far_plane * camera->near_plane) / (camera->far_plane - camera->near_plane);
// //     matrix[3][3] = 0.0f;
// // }

// #include <math.h>

// void render_scene(t_rt *rt, t_scene *scn)
// {
// 	t_cvec4 coords = scn->camera.coords;
// 	t_cuint32 bg_color = 0xFF0000;
// 	float aspect_ratio = ASPECT_RATIO;
// 	float x;
// 	float y;
	
// 	t_vec4 ambient_color = scn->ambient.color * scn->ambient.a.ratio;
// 	for (uint32_t j = 0; j < WINDOW_HEIGHT; j++)
// 	{
// 		for (uint32_t i = 0; i < WINDOW_WIDTH; i++)
// 		{
// 			x = (2.0F * (i + 0.5F) / (float)WINDOW_WIDTH - 1) * aspect_ratio;
// 			y = 1.0F - 2.0F * (j + 0.5F) / (float)WINDOW_HEIGHT;
// 			t_vec4 direction = vnorm((t_vec4){x, y, -scn->camera.c.zvp_dist} + scn->camera.c.orientation);

// 			t_vec4 color = obj_nearest_vp(rt, scn->objs, coords, direction);
// 			if (color[X] == -1.0F)
// 			{
// 				continue ;
// 			}
// 			color *= ambient_color * scn->ambient.a.ratio;
// 			set_pixel(rt->win, i, j, color);
// 		}
// 	}
// }

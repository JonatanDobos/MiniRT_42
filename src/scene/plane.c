// #include <miniRT.h>

// t_plane create_plane(t_vec point, t_vec normal, t_vec color)
// {
// 	t_plane plane;
// 	plane.point = point;
// 	plane.direction = normal;
// 	plane.color = color;
// 	return (plane);
// }

// // t_vec subtract(t_vec a, t_vec b)
// // {
// //     t_vec result = {
// //         .x = a.x - b.x,
// //         .y = a.y - b.y,
// //         .z = a.z - b.z
// //     };
// //     return result;
// // }

// // double dot_product(t_vec a, t_vec b)
// // {
// //     return a.x * b.x + a.y * b.y + a.z * b.z;
// // }

// // bool intersect_plane(const t_plane *plane, const t_vec *ray_dir, const t_vec *ray_pos, double *t)
// // {
// //     double denom = dot_product(plane->direction, *ray_dir);
// //     if (fabs(denom) > 1e-6) {
// //         t_vec p0l0 = subtract(plane->point, *ray_pos);
// //         *t = dot_product(p0l0, plane->direction) / denom;
// //         return (*t >= 0);
// //     }
// //     return false;
// // }

// // bool intersect_plane(const t_plane *plane, const t_vec *coords, const t_vec *ray_pos, double *t)
// // {
// // 	t_vec p0l0 = {
// // 		.x = plane->point.x - ray_pos->x,
// // 		.y = plane->point.y - ray_pos->y,
// // 		.z = plane->point.z - ray_pos->z
// // 	};
// // 	double denom = plane->direction.x * coords->x + plane->direction.y * coords->y + plane->direction.z * coords->z;
// // 	if (fabs(denom) > 1e-6)
// // 	{
// // 		*t = (p0l0.x * plane->direction.x + p0l0.y * plane->direction.y + p0l0.z * plane->direction.z) / denom;
// // 		return (*t >= 0);
// // 	}
// // 	return (false);
// // }

// t_vec normalize(t_vec v)
// {
// 	double length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
// 	if (length > 0)
// 	{
// 		v.x /= length;
// 		v.y /= length;
// 		v.z /= length;
// 	}
// 	return v;
// }


// void render_plane(mlx_image_t *img, const t_plane *plane, const t_vp *vp)
// {
// 	const t_vec	*ray_pos = &vp->ray_position;
// 	// const t_vec	*ray_dir = &vp->coords;
// 	const t_vec	*base_ray_dir = &vp->coords;
// 	uint32_t bg_color = 0xFF0000;	// black
	
// 	uint32_t color = 0xFF00FF;
// 	color = 0x00FFFF;	// cyan worked
// 	// color = 0xFF00FF;	// magentha but showed green anyway
// 	// color = 0xFFFFFF;	// showed Cyan???
// 	// uint32_t color = ((uint32_t)(plane->color.r * 255) << 16) |
// 	// 					((uint32_t)(plane->color.g * 255) << 8) |
// 	// 					((uint32_t)(plane->color.b * 255));

// 	printf("Background color: 0x%06X\n", bg_color);  // Debug print for background color
// 	printf("Plane color: 0x%06X\n", color);  // Debug print for plane color
// 	double aspect_ratio = (double)WINDOW_WIDTH / WINDOW_HEIGHT;

// 	for (int j = 0; j < WINDOW_HEIGHT; j++)
// 	{
// 		for (int i = 0; i < WINDOW_WIDTH; i++)
// 		{
// 			t_vec coords = {
// 				.x = base_ray_dir->x + (2.0 * ((i + 0.5) / WINDOW_WIDTH) - 1.0) * aspect_ratio,
// 				.y = base_ray_dir->y + (1.0 - 2.0 * ((j + 0.5) / WINDOW_HEIGHT)),
// 				.z = base_ray_dir->z
// 			};
// 			coords = normalize(coords);


// 			double t;
// 			// if (intersect_plane(plane, &coords, ray_pos, &t))
// 			if (intersect_plane(plane, &coords, ray_pos, &t))
// 			{
// 				// printf("Hit at pixel (%d, %d) with color 0x%06X\n", i, j, color);
// 				mlx_put_pixel(img, i, j, bg_color);
// 			} else {
// 				mlx_put_pixel(img, i, j, color);
// 			}
// 		}
// 	}
// }


// t_plane plane(t_rt *rt)
// {
// 	t_vec point = {.x = 0.0, .y = 0.0, .z = 0.0};  // Point on the plane
// 	t_vec direction = {.x = 0.0, .y = 1.0, .z = 0.0};
// 	direction = normalize(direction);
// 	t_vec color = {.r = 1.0, .g = 0.0, .b = 1.0};  // Blue color
// 	t_plane plane = create_plane(point, direction, color);

// 	// render_plane(rt->img, &plane, &rt->vp.ray_position);
// 	render_plane(rt->img, &plane, &rt->vp);
// 	return (plane);
// }
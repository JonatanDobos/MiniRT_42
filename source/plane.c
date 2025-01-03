#include "../includes/miniRT.h"

t_plane create_plane(t_vec point, t_vec normal, t_vec color)
{
	t_plane plane;
	plane.point = point;
	plane.direction = normal;
	plane.color = color;
	return (plane);
}

bool intersect_plane(const t_plane *plane, const t_vec *ray_direction, const t_vec *ray_origin, double *t)
{
	t_vec p0l0 = {
		.x = plane->point.x - ray_origin->x,
		.y = plane->point.y - ray_origin->y,
		.z = plane->point.z - ray_origin->z
	};
	double denom = plane->direction.x * ray_direction->x + plane->direction.y * ray_direction->y + plane->direction.z * ray_direction->z;
	if (fabs(denom) > 1e-6)
	{
		*t = (p0l0.x * plane->direction.x + p0l0.y * plane->direction.y + p0l0.z * plane->direction.z) / denom;
		return (*t >= 0);
	}
	return (false);
}

void render_plane(mlx_image_t *img, const t_plane *plane, const t_vec *ray_origin)
{
	uint32_t bg_color = 0xFF0000;	// black
	
	uint32_t color = 0xFF00FF;
	color = 0x00FFFF;	// cyan worked
	// color = 0xFF00FF;	// magentha but showed green anyway
	// color = 0xFFFFFF;	// showed Cyan???
	// uint32_t color = ((uint32_t)(plane->color.r * 255) << 16) |
	// 					((uint32_t)(plane->color.g * 255) << 8) |
	// 					((uint32_t)(plane->color.b * 255));

	printf("Background color: 0x%06X\n", bg_color);  // Debug print for background color
    printf("Plane color: 0x%06X\n", color);  // Debug print for plane color

	for (int j = 0; j < HEIGHT; j++)
	{
		for (int i = 0; i < WIDTH; i++)
		{
			t_vec ray_direction = {
				.x = (double)i / WIDTH - 0.5,
				.y = (double)j / HEIGHT - 0.5,
				.z = -1.0
			};
			double t;
			if (intersect_plane(plane, &ray_direction, ray_origin, &t))
			{
				// printf("Hit at pixel (%d, %d) with color 0x%06X\n", i, j, color);
				mlx_put_pixel(img, i, j, bg_color);
			} else {
				mlx_put_pixel(img, i, j, color);
			}
		}
	}
}

t_vec normalize(t_vec v)
{
	float magnitude = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	t_vec normalized = {
		.x = v.x / magnitude,
		.y = v.y / magnitude,
		.z = v.z / magnitude
	};
	return (normalized);
}

t_plane plane(t_rt *rt)
{
	t_vec point = {.x = 0.0, .y = 0.0, .z = 0.0};  // Point on the plane
	t_vec direction = {.x = 0.0, .y = 1.0, .z = 0.0};
	direction = normalize(direction);
	t_vec color = {.r = 1.0, .g = 0.0, .b = 1.0};  // Blue color
	t_plane plane = create_plane(point, direction, color);

	render_plane(rt->img, &plane, &rt->ray_origin);
	return (plane);
}
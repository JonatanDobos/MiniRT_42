#ifndef MINIRT_DATA_H
# define MINIRT_DATA_H

// Data structures and types

typedef float	t_vec4 __attribute__((vector_size(16), aligned(16)));

// Small struct types

typedef struct s_ray
{
	t_vec4			origin;
	t_vec4			vec;
}	t_ray;

typedef struct s_plane
{
	t_vec4			point;
	t_vec4			normal;
	t_vec4			color;
}	t_plane;

typedef struct s_sphere
{
	t_vec4			center;
	float			radius;
	t_vec4			color;
}	t_sphere;

typedef struct s_cylinder
{
	t_vec4			center;
	t_vec4			normal;
	float			radius;
	float			height;
	t_vec4			color;
}	t_cylinder;

typedef struct s_light
{
	t_vec4			point;
	float			brightness;
	t_vec4			color;
}	t_light;

typedef struct s_cam
{
	t_vec4			point;
	t_vec4			orient;
	uint8_t			fov;
}	t_cam;

typedef struct s_amblight
{
	float			ratio;
	t_vec4			color;
}	t_amblight;

typedef struct s_poly
{
	t_vec4			a;
	t_vec4			b;
	t_vec4			c;
	t_vec4			color;
}	t_poly;

// Main structs

typedef struct s_scene
{
	t_amblight		ambient;
	t_cam			cam;
	t_light			light;
	t_plane			*plane;
	uint16_t		plane_count;
	t_sphere		*sphere;
	uint16_t		sphere_count;
	t_cylinder		*cylinder;
	uint16_t		cylinder_count;
	float			z_dist;
	float			realtime_fov;
	float			cam_r_speed;
	float			cam_m_speed;
	float			cam_fov_speed;
	float			cam_sens;
	float			delta_time;
	bool			render;
}	t_scene;

typedef struct s_window
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	uint8_t			*pixels;
	int16_t			id;
	uint16_t		rndr_wdth;
	uint16_t		rndr_hght;
	uint16_t		window_wdth;
	uint16_t		window_hght;
	float			res_ratio;
	float			aspectratio_w;
	bool			mouse_integration;
	bool			mouse_pos_re_init;
	bool			resize;
}	t_window;

typedef struct s_minirt
{
	t_window		win;
	t_scene			scene;
	int16_t			errnum;
}	t_minirt;

// Unique structs

// Nested loops

typedef struct s_axis2_16
{
	uint16_t		x;
	uint16_t		y;
}	t_axis2;

// Parsing

typedef struct s_parsing_value_check
{
	uint16_t		cam_amount;
	uint16_t		light_amount;
	uint16_t		amb_amount;
	uint16_t		obj_amount;
}	t_value_check;

#endif

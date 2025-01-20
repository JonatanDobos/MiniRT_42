#ifndef MINIRT_DATA_H
# define MINIRT_DATA_H

// Data structures and types

// Fast integer types

typedef int_fast32_t	t_int;
typedef int_fast64_t	t_long;
typedef int_fast16_t	t_short;
typedef int_fast8_t		t_int8;
typedef uint_fast8_t	t_uint8;
typedef uint_fast16_t	t_uin16;
typedef uint_fast32_t	t_uint;
typedef uint_fast64_t	t_ulong;

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
	t_uint8			fov;
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
	t_uin16			plane_count;
	t_sphere		*sphere;
	t_uin16			sphere_count;
	t_cylinder		*cylinder;
	t_uin16			cylinder_count;
	float			z_dist;
	float			realtime_fov;
	bool			render;
}	t_scene;

typedef struct s_window
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_uint8			*pixels;
	t_short			id;
	t_uin16			rndr_wdth;
	t_uin16			rndr_hght;
	t_uin16			set_rndr_hght;
	float			ratio_w;
	bool			resize;
}	t_window;

typedef struct s_minirt
{
	t_window		win;
	t_scene			scene;
	t_short			errnum;
}	t_minirt;

// Unique structs

// Parsing

typedef struct s_parsing_value_check
{
	t_uin16			cam_amount;
	t_uin16			light_amount;
	t_uin16			amb_amount;
	t_uin16			obj_amount;
}	t_value_check;

#endif

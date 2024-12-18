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

// Small struct types

typedef struct s_rgba
{
	t_uint8			r;
	t_uint8			g;
	t_uint8			b;
	t_uint8			a;
}	t_rgba;

typedef struct s_eucl
{
	float			x;
	float			y;
	float			z;
}	t_eucl;

typedef struct s_ray
{
	t_eucl			origin;
	t_eucl			vec;
}	t_ray;

typedef struct s_plane
{
	t_eucl			point;
	t_eucl			normal;
	t_rgba			color;
}	t_plane;

typedef struct s_sphere
{
	t_eucl			center;
	float			radius;
	t_rgba			color;
}	t_sphere;

typedef struct s_cilinder
{
	t_eucl			center;
	t_eucl			normal;
	float			radius;
	float			height;
	t_rgba			color;
}	t_cilinder;

typedef struct s_light
{
	t_eucl			point;
	float			brightness;
	t_rgba			color;
}	t_light;

typedef struct s_cam
{
	t_eucl			point;
	t_eucl			orient;
	t_uint8			fov;
}	t_cam;

typedef struct s_amblight
{
	float			ratio;
	t_rgba			color;
}	t_amblight;

typedef struct s_poly
{
	t_eucl			a;
	t_eucl			b;
	t_eucl			c;
	t_rgba			color;
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
	t_cilinder		*cilinder;
	t_uin16			cilinder_count;
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

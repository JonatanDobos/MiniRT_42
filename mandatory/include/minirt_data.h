#ifndef MINIRT_DATA_H
# define MINIRT_DATA_H

// data structures

typedef int_fast32_t	t_int;
typedef int_fast64_t	t_long;
typedef int_fast16_t	t_short;
typedef int_fast8_t		t_int8;
typedef uint_fast8_t	t_uint8;
typedef uint_fast32_t	t_uint;
typedef uint_fast64_t	t_ulong;

typedef struct s_eucl
{
	float	x;
	float	y;
	float	z;
}	t_eucl;

typedef struct s_pvec
{
	t_eucl	origin;
	t_eucl	vec;
}	t_pvec;

typedef struct s_obj
{
	t_uint	id;
	t_eucl	origin;
	t_eucl	vec;
}	t_obj;

typedef struct s_light
{
	t_uint	id;
	t_eucl	origin;
	t_eucl	vec;
}	t_light;

typedef struct s_cam
{
	t_uint	id;
	t_eucl	origin;
	t_eucl	vec;
}	t_cam;

typedef struct s_amblight
{
	t_eucl	origin;
	t_eucl	vec;
}	t_amblight;

typedef struct s_window
{
	mlx_t		*inst;
	mlx_image_t	*img;
	t_uint8		*pixels;
	t_uint8		id;
	t_uint		wdth;
	t_uint		hght;
	t_uint		pixel_amount;
	bool		resize;
}	t_window;

typedef struct s_minirt
{
	t_window	win;
	t_short		errnum;
}	t_minirt;

#endif
#ifndef MINIRT_DATA_H
# define MINIRT_DATA_H

// data structures

typedef int_fast32_t	t_int;
typedef int_fast64_t	t_long;
typedef int_fast16_t	t_short;
typedef int_fast8_t		t_shrt8;
typedef uint_fast32_t	t_uint;
typedef uint_fast64_t	t_ulong;
typedef uint_fast8_t	t_ushrt;

typedef struct s_vec
{
	float	x;
	float	y;
	float	z;
}	t_vec;

typedef struct s_window
{
	mlx_t		*inst;
	mlx_image_t	*img;
	t_uint		*pixels;
	t_ushrt		id;
	t_uint		wdth;
	t_uint		hght;
	t_uint		total_pixels;
	bool		resize;
}	t_window;

#endif
#ifndef MINIRT_H
# define MINIRT_H

#include "../extern_libraries/libft/libft.h"
#include "../extern_libraries/MLX42/include/MLX42/MLX42.h"
#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#define WIDTH 800
#define ASPECT_RATIO (16.0 / 9.0)
#define HEIGHT ((int)(WIDTH / ASPECT_RATIO))

typedef float			t_vec3 __attribute__ ((vector_size(16)));
typedef union u_vec		t_vec;
// typedef union u_rgb		t_rgb;
// typedef struct s_vec	t_vec3;
typedef struct s_plane	t_plane;
typedef struct s_sphere	t_sphere;
typedef struct s_rt		t_rt;

typedef void			(*t_mlx_keyhook_cast)(mlx_key_data_t, void *);

union u_vec
{
	t_vec3 vec3;
	struct
	{
		float x;
		float y;
		float z;
	};
	struct
	{
		float r;
		float g;
		float b;
	};
	struct
	{
		float i;
		float j;
		float k;
	};
};

struct	s_plane
{
	t_vec	point;
	t_vec	direction;
	t_vec	color;
};

struct	s_sphere
{
	t_vec center;
	float radius;
	t_vec color;
};

struct s_rt
{
	char			**map;
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_plane			*plane;
	t_sphere		*sphere;
	t_vec			ray_origin;
};

void	my_keyhook(mlx_key_data_t keydata, t_rt *rt);
t_plane	plane(t_rt *rt);
t_sphere sphere(t_rt *rt);

#endif

#ifndef MINIRT_H
# define MINIRT_H

// # include <libft.h>
// # include <MLX42/MLX42.h>
// #include <math.h>

//	temporary include for debugging.
#include <stdio.h>

#ifndef SCREEN_WIDTH
# define SCREEN_WIDTH 800
#endif

#ifndef SCREEN_HEIGHT
# define SCREEN_HEIGHT ((int)(WIDTH / ASPECT_RATIO))
#endif

//	Norminette doesn't allow our macros
#define WIDTH 800
#define ASPECT_RATIO (16.0 / 9.0)
#define HEIGHT ((int)(WIDTH / ASPECT_RATIO))

typedef float				t_vec3 __attribute__ ((vector_size(16)));
//	Forward declaration of structs;
typedef struct s_scene		t_scene;
typedef struct mlx			mlx_t;
typedef struct mlx_texture	mlx_texture_t;
typedef struct mlx_image	mlx_image_t;

enum e_axis {
	X,
	Y,
	Z
};

typedef struct	s_rt
{
	t_scene			*scene;
	mlx_t			*mlx;
	mlx_texture_t	*logo;
	mlx_image_t		*img;
}	t_rt;
#endif
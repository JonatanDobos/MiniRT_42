#ifndef MINIRT_H
# define MINIRT_H

// # include <libft.h>
// # include <MLX42/MLX42.h>
// #include <math.h>

//	temporary include for debugging.
# include <stdio.h>
# include <errno.h>

# ifndef SCREEN_WIDTH
#  define SCREEN_WIDTH 2000
# endif

# ifndef SCREEN_HEIGHT
#  define SCREEN_HEIGHT ((int)(SCREEN_WIDTH / ASPECT_RATIO))
# endif

//	Norminette doesn't allow our macros
# define WINDOW_WIDTH 1600
# define ASPECT_RATIO (16.0 / 9.0)
# define WINDOW_HEIGHT ((int)(WINDOW_WIDTH / ASPECT_RATIO))

typedef float				t_vec3 __attribute__ ((vector_size(16)));
// typedef uint8_t				t_rgba __attribute__ ((vector_size(sizeof(uint8_t) * 4)));

typedef const t_vec3		t_cvec3;
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

// enum e_axis {
// 	R,
// 	G,
// 	B,
// 	A
// };

typedef struct	s_rt
{
	t_scene			*scene;
	mlx_t			*mlx;
	mlx_texture_t	*logo;
	mlx_image_t		*img;
	int				errnum;
}	t_rt;

#endif

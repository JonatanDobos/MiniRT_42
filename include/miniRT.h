#ifndef MINIRT_H
# define MINIRT_H

// # include <libft.h>
// # include <MLX42/MLX42.h>
// #include <math.h>
# define _GNU_SOURCE

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

typedef float				t_vec4 __attribute__ ((vector_size(16)));
// typedef uint8_t				t_rgba __attribute__ ((vector_size(sizeof(uint8_t) * 4)));

typedef const t_vec4		t_cvec4;
//	Forward declaration of structs;
typedef struct s_scene		t_scene;
typedef struct s_window		t_window;
typedef struct mlx			mlx_t;
typedef struct mlx_texture	mlx_texture_t;
typedef struct mlx_image	mlx_image_t;

enum e_axis
{
	X,
	Y,
	Z,
	W
};

enum e_rgba
{
	R,
	G,
	B,
	A
};

typedef struct	s_rt
{
	t_scene			*scene;
	t_window		*win;
	int				errnum;
}	t_rt;

#endif

#ifndef MINIRT_H
# define MINIRT_H

// # include <libft.h>
// # include <MLX42/MLX42.h>
// #include <math.h>
# define _GNU_SOURCE

//	temporary include for debugging.
# include <stdbool.h>
# include <stdio.h>
# include <errno.h>
# include <pthread.h>

# ifndef SCREEN_WIDTH
#  define SCREEN_WIDTH 800
# endif

# ifndef SCREEN_HEIGHT
#  define SCREEN_HEIGHT 450
# endif

# ifndef THREADS
#  define THREADS 1
# endif

typedef float				t_vec4 __attribute__ ((vector_size(16)));

typedef const t_vec4		t_cvec4;
//	Forward declaration of structs;
typedef struct s_scene		t_scene;
typedef struct s_window		t_window;
typedef struct mlx			mlx_t;
typedef struct mlx_texture	mlx_texture_t;
typedef struct mlx_image	mlx_image_t;
typedef struct s_thread		t_thread;

typedef pthread_mutex_t		t_mtx;
typedef void				*(*t_cast)(void *);
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

enum e_mtx
{
	MTX_PRINT,
	MTX_SYNC,
	MTX_CREATION_CHECK,
	MTX_AMOUNT
};

typedef struct	s_rt
{
	t_scene			*scene;
	t_window		*win;
	t_mtx			mtx[MTX_AMOUNT];
	t_thread		*threads;
	bool			thread_creation_check;
	int				errnum;
}	t_rt;

bool	init_pthread_mutex(t_rt *rt);
bool	launch_pthreads(t_rt *rt);
void	destroy_threads(t_rt *rt, size_t thread_amount);
void	destroy_mutexes(t_rt *rt, size_t amount);

// tmp
void	my_screw_you_joni_render(t_rt *rt);

#endif

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
# include <threadsRT.h>

# ifndef SCREEN_WIDTH
#  define SCREEN_WIDTH 5120
# endif

# ifndef SCREEN_HEIGHT
#  define SCREEN_HEIGHT 2700
# endif

# ifndef THREADS
#  define THREADS 1
# endif

// # define THREADS 2

typedef float				t_vec4 __attribute__ ((vector_size(16)));

typedef const t_vec4		t_cvec4;
//	Forward declaration of structs;
typedef struct s_scene		t_scene;
typedef struct s_window		t_window;
typedef struct mlx			mlx_t;
typedef struct mlx_texture	mlx_texture_t;
typedef struct mlx_image	mlx_image_t;
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
	MTX_RESYNC,
	MTX_DONE_RENDERING,
	MTX_CREATION_CHECK,
	MTX_QUIT_ROUTINE,
	MTX_STOPPED_THREADS,
	MTX_RES_RATIO,
	MTX_RENDER,
	MTX_AMOUNT
};

typedef struct	s_rt
{
	t_scene			*scene;
	t_scene			*read_scene;
	t_window		*win;
	pthread_cond_t	cond;
	uint16_t		finished_rendering;
	uint16_t		stopped_threads;
	uint16_t		thread_rend_step;
	bool			pressed_key;
	bool			creation_check;
	bool			mtx_init_check;
	bool			quit_routine;
	int				errnum;
	t_mtx			mtx[MTX_AMOUNT];
	t_thread		thread;
}	t_rt;

#endif

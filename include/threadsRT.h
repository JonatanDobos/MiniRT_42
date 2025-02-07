#ifndef THREADSRT_H
# define THREADSRT_H

# include <miniRT.h>
# include <common_defs.h>

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


typedef struct	s_thread
{
	uint16_t		id;
	t_rt			*rt;
	mlx_image_t		*img;
	t_mtx			mtx;
	pthread_t		thread;
	int				errnum;
}	t_thread;

bool	init_pthread_mutex(t_rt *rt);
bool	launch_pthreads(t_rt *rt);
void	destroy_threads(t_rt *rt, size_t thread_amount);
void	destroy_mutexes(t_rt *rt, size_t amount);

// tmp
void	my_screw_you_joni_render(t_rt *rt);

#endif

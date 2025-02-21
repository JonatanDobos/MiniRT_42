#ifndef THREADSRT_H
# define THREADSRT_H

# include <pthread.h>
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
typedef struct s_rt			t_rt;

typedef pthread_mutex_t		t_mtx;
typedef void				*(*t_cast)(void *);


typedef struct	s_thread
{
	uint16_t		id;
	t_rt			*rt;
	t_scene			*scene;
	t_window		*win;
	mlx_image_t		*img;
	uint8_t			*pixels;
	uint16_t		img_width;
	uint16_t		img_height;
	uint16_t		rdr_height;
	uint16_t		start_y;
	float			aspectr;
	t_mtx			mtx;
	pthread_t		thread;
}	t_thread;

// bool	init_pthread_mutex(t_rt *rt);
bool	initialize_mutexes(t_rt *rt);
bool	initialize_conditions(t_rt *rt);
bool	launch_pthreads(t_rt *rt);
void	destroy_threads(t_rt *rt, size_t thread_amount);
bool	destroy_conditions(t_rt *rt);
void	destroy_mutexes(t_rt *rt, size_t amount);

bool	img_multithreaded(t_rt *rt);
void	thread_routine_init(t_thread *th);
void	img_deletion(t_rt *rt, uint16_t img_amount);

bool	check_bool(t_mtx *mutex, bool to_check);
bool	toggle_bool(t_mtx *mutex, bool *to_toggle, bool new_value);
void	print_lock(t_mtx *print, char *str);

#endif

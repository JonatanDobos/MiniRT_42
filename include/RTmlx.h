#ifndef RTMLX_H
# define RTMLX_H
# include <MLX42/MLX42.h>
# include <common_defs.h>
# include <miniRT.h>

# define LOGO_PATH "images/glasses.png"

// Maybe scrool FOV hook speed??

# define CAM_ROTATION_SPEED 2.6f

# define CAM_MOVE_SPEED 18.0f

typedef struct	s_rt		t_rt;
typedef struct	s_scene		t_scene;
typedef struct	s_window	t_window;


bool	windows_setup_mlx(t_rt *rt);
void	my_keyhook(mlx_key_data_t keydata, t_rt *rt);
void	init_hooks(t_rt *m);

void	loop_hook(void *param);
void	fov_hook(double xdelta, double ydelta, void *param);

// scaling.c

void	scaled_res_set_pixel(t_window *w, uint16_t x, uint16_t y, t_vec4 color);
void	res_downscale(t_rt *rt);
void	res_upscale(t_rt *rt);
void	res_rescale(t_rt *rt);


// camera_move.c

void		cam_move_forw(t_scene *sc);
void		cam_move_backw(t_scene *sc);
void		cam_move_right(t_scene *sc);
void		cam_move_left(t_scene *sc);
void		cam_move_up(t_scene *sc);
void		cam_move_down(t_scene *sc);

// camera_rotate.c

void		cam_rotate_right(t_scene *sc);
void		cam_rotate_left(t_scene *sc);
void		cam_rotate_up(t_scene *sc);
void		cam_rotate_down(t_scene *sc);

typedef struct s_window
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	uint8_t			*pixels;
	int16_t			id;
	uint16_t		rndr_wdth;
	uint16_t		rndr_hght;
	uint16_t		window_wdth;
	uint16_t		window_hght;
	uint16_t		set_rndr_hght;
	float			aspectrat;
	float			res_ratio;
	float			delta_time;
	bool			resize;
	mlx_texture_t	*logo;
}	t_window;

#endif

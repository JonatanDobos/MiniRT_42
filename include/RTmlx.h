#ifndef RTMLX_H
# define RTMLX_H
# include <MLX42/MLX42.h>
# include <libft.h> 
# include <miniRT.h>

# define LOGO_PATH "images/glasses.png"
# define NAME_FILE "Name your .rt file:  "
# define CAM_ROTATION_SPEED 1.0F
# define CAM_MOVE_SPEED 12.0F
# define FOV_SCROLL_SPEED 160.0F

# define FOV_MAX 180.0F

typedef struct	s_rt		t_rt;
typedef struct	s_scene		t_scene;
typedef struct	s_window	t_window;

typedef struct s_window
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	uint8_t			*pixels;
	int16_t			id;
	uint32_t		rndr_wdth;
	uint32_t		rndr_hght;
	uint32_t		window_wdth;
	uint32_t		window_hght;
	float			aspectrat;
	uint16_t		res_ratio;
	uint16_t		res_r_start;
	float			target_time;
	float			delta_time;
	bool			resize;
	bool			file_creation;
	char			filename[FILE_CREATION + (sizeof(NAME_FILE) - 1)];
	uint16_t		filename_len;
	mlx_texture_t	*logo;
}	t_window;

// window_setup.c

bool	windows_setup_mlx(t_rt *rt);
void	my_keyhook(mlx_key_data_t keydata, t_rt *rt);

// hooks.c

void	init_hooks(t_rt *rt);
void	loop_hook(t_rt *rt);
void	loop_hook_threaded(t_rt *rt);
void	my_keyhook(mlx_key_data_t keydata, t_rt *rt);
void	scroll_fov_hook(double xdelta, double ydelta, t_scene *sc);

// hooks_move.c

void	movement(t_rt *rt);
void	mouse_hook(mouse_key_t button, action_t action, modifier_key_t mods, t_rt *rt);

// object_modification.c

bool	handle_object_modification(const keys_t key, t_scene *sc);

// scaling.c

void	scaled_res_set_pixel(t_window *w, uint16_t x, uint16_t y, t_vec4 color);

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


bool		obj_move_forw(t_scene *sc);
bool		obj_move_backw(t_scene *sc);
bool		obj_move_left(t_scene *sc);
bool		obj_move_right(t_scene *sc);
bool		obj_move_up(t_scene *sc);
bool		obj_move_down(t_scene *sc);

void		obj_rotate_up(t_scene *sc);
void		obj_rotate_down(t_scene *sc);
void		obj_rotate_left(t_scene *sc);
void		obj_rotate_right(t_scene *sc);

void		set_filename(const keys_t key, t_window *win, t_scene *sc);
void		reset_filename(t_window *win);

void	create_bmp(t_rt *rt/* , const char *filename */);

#endif
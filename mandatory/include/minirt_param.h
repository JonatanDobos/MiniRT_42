#ifndef MINIRT_PARAM_H
# define MINIRT_PARAM_H

// function parameters (main header file)

# include "../../libs/libft/libft.h"
# include "../../libs/MLX42/include/MLX42/MLX42.h"
# include "minirt_extern.h"
# include "minirt_define.h"
# include "minirt_data.h"

// render.c

void		render(t_minirt *m);

// render_utils.c

void		set_pixel(t_minirt *m, t_uin16 x, t_uin16 y, t_rgba color);

// mlx_init.c

t_short		window_init(t_window *win, t_uint wdth, t_uint hght, const char *name);

// mlx_hook.c

void		init_hooks(t_minirt *m);

// parsing.c

t_short		input_parse(t_minirt *m, const char *file);

// init.c

void		init_struct_m(t_minirt *m);

// print.c

t_short		perr(char *place, t_short num);
t_short		perrmlx(char *place, const t_short num);
t_short		perr_msg(char *place, const t_short errnum, char *msg);

// cleanup.c

void		clean_window(t_window *win);
void		clean_scene(t_scene *sc);
void		clean_all(t_minirt *m);

// error.c

t_long		errset(const t_long errnum);
t_short		nsave(const t_short num);

// exit.c

void		exit_clean(t_minirt *m, t_short errnum);

// scaling.c

float		render_scale_x(t_window *win, float val);
float		render_scale_y(t_window *win, float val);

// parse_peripherals.c

t_short		parse_amb(t_scene *sc, t_value_check *vc, char *line);
t_short		parse_cam(t_scene *sc, t_value_check *vc, char *line);
t_short		parse_light(t_scene *sc, t_value_check *vc, char *line);

// parse_objects.c

t_short		parse_pl(t_scene *sc, t_value_check *vc, char *line);
t_short		parse_sp(t_scene *sc, t_value_check *vc, char *line);
t_short		parse_cy(t_scene *sc, t_value_check *vc, char *line);

// parsing_utils.c

void		*memappend(void **ptr, void *append, size_t size, size_t len);
double		range(double value, double min, double max);

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

// string_utils.c

float		rt_atof(const char *str);
t_int		rt_atoi(const char *str);
char		*nxtv(char *str);
char		*nxtvp(char **str);

// vec_advanced.c

t_eucl		vec_cross(t_eucl a, t_eucl b);
t_eucl		vec_normalize(t_eucl v);
t_eucl		vec_project(t_eucl a, t_eucl b);
t_eucl		vec_reflect(t_eucl v, t_eucl n);
float		vec_len(t_eucl v);

// vec_math.c

t_eucl		vec_add(t_eucl a, t_eucl b);
t_eucl		vec_sub(t_eucl a, t_eucl b);
t_eucl		vec_scale(t_eucl v, float scalar);
float		vec_dot(t_eucl a, t_eucl b);
t_eucl		vec_mul(t_eucl a, float s);

// _debug.c

void	_print_parsing(t_scene *sc);

#endif

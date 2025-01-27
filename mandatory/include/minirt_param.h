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

void		set_pixel(t_window *w, uint16_t x, uint16_t y, t_vec4 color)__attribute__((hot));
t_vec4		bcast4(float scalar)__attribute__((const, hot));
t_vec4		bcast3(float scalar)__attribute__((const, hot));

// mlx_init.c

int16_t		window_init(t_window *win, uint32_t wdth, uint32_t hght, const char *name);

// mlx_hook.c

void		init_hooks(t_minirt *m);

// mlx_hook_mouse.c

void		cursor_cam_switch(t_minirt *m, bool state);
void		mouse_hook(mouse_key_t but, action_t act, modifier_key_t mods, void *param);
void		fov_hook(double xdelta, double ydelta, void *param);
void		cam_cursor_move(int32_t x, int32_t y, t_minirt *m);


// mlx_hook_utils.c

bool		switch_bool(bool *value);
bool		cursor_inboud(mlx_t *mlx, uint16_t margin);
bool		axis2_inboud(t_axis2 val, t_axis2 xlim, t_axis2 ylim);

// parsing.c

int16_t		input_parse(t_minirt *m, const char *file);

// init.c

void		init_struct_m(t_minirt *m);

// print.c

int16_t		perr(char *place, int16_t num);
int16_t		perrmlx(char *place, const int16_t num);
int16_t		perr_msg(char *place, const int16_t errnum, char *msg);

// cleanup.c

void		clean_window(t_window *win);
void		clean_scene(t_scene *sc);
void		clean_all(t_minirt *m);

// error.c

int64_t		errset(const int64_t errnum);
int16_t		nsave(const int16_t num);

// exit.c

void		exit_clean(t_minirt *m, int16_t errnum);

// scaling.c

void		scaled_res_set_pixel(t_window *w, uint16_t x, uint16_t y, t_vec4 color);
void		res_upscale(t_minirt *m);
void		res_downscale(t_minirt *m);
void		res_rescale(t_minirt *m);

// parse_peripherals.c

int16_t		parse_amb(t_scene *sc, t_value_check *vc, char *line);
int16_t		parse_cam(t_scene *sc, t_value_check *vc, char *line);
int16_t		parse_light(t_scene *sc, t_value_check *vc, char *line);

// parse_objects.c

int16_t		parse_pl(t_scene *sc, t_value_check *vc, char *line);
int16_t		parse_sp(t_scene *sc, t_value_check *vc, char *line);
int16_t		parse_cy(t_scene *sc, t_value_check *vc, char *line);

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
int32_t		rt_atoi(const char *str);
char		*nxtv(char *str);
char		*nxtvp(char **str);

// vec_advanced.c

t_vec4		vec_cross(t_vec4 a, t_vec4 b)__attribute__((const, hot));
t_vec4		vec_normalize(t_vec4 v)__attribute__((const, hot));
t_vec4		vec_project(t_vec4 a, t_vec4 b)__attribute__((const, hot));
t_vec4		vec_reflect(t_vec4 v, t_vec4 n)__attribute__((const, hot));
float		vec_len(t_vec4 v)__attribute__((const, hot));
t_vec4		vec_rotate(t_vec4 v, t_vec4 axis, float angle);

// vec_math.c

t_vec4		vec_add(t_vec4 a, t_vec4 b)__attribute__((const, hot));
t_vec4		vec_sub(t_vec4 a, t_vec4 b)__attribute__((const, hot));
t_vec4		vec_scale(t_vec4 v, float scalar)__attribute__((const, hot));
float		vec_dot(t_vec4 a, t_vec4 b)__attribute__((const, hot));
t_vec4		vec_mul(t_vec4 a, float s)__attribute__((const, hot));

// _debug.c

void		_print_parsing(t_scene *sc);

#endif

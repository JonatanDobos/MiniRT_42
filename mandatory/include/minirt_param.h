#ifndef MINIRT_PARAM_H
# define MINIRT_PARAM_H

// function parameters (main header file)

# include "../../libs/libft/libft.h"
# include "../../libs/MLX42/include/MLX42/MLX42.h"
# include "minirt_extern.h"
# include "minirt_define.h"
# include "minirt_data.h"

// mlx_init.c

t_short	window_init(t_window *win, t_uint wdth, t_uint hght, const char *name);

// mlx_hook.c

void		init_hooks(t_minirt *m);

// input_parsing.c

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

// vec_advanced.c

t_eucl		vec_cross(t_eucl a, t_eucl b);
t_eucl		vec_normalize(t_eucl v);
t_eucl		vec_project(t_eucl a, t_eucl b);
t_eucl		vec_reflect(t_eucl v, t_eucl n);

// vec_math.c

t_eucl		vec_add(t_eucl a, t_eucl b);
t_eucl		vec_sub(t_eucl a, t_eucl b);
float		vec_len(t_eucl v);
t_eucl		vec_scale(t_eucl v, float scalar);
float		vec_dot(t_eucl a, t_eucl b);

#endif

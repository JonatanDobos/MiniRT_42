#ifndef MINIRT_PARAM_H
# define MINIRT_PARAM_H

// function parameters (main header file)

# include "../../libs/libft/libft.h"
# include "../../libs/MLX42/include/MLX42/MLX42.h"
# include "minirt_extern.h"
# include "minirt_define.h"
# include "minirt_data.h"

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

// mlx_init.c
t_short		window_init(t_window *wdw, const char *name);

// input_parsing.c
t_short		input_parse(t_minirt *mrt, const char *inp);

// print.c
t_short		perr(char *place, t_short num);
t_short		perrmlx(char *place, const t_short num);

// error.c
t_short		errn_set(const t_short num);

#endif
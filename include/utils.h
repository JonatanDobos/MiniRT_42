#ifndef UTILS_H
# define UTILS_H
# include <common_defs.h>
# include <math.h>
# include <miniRT.h>

// static inline float	rt_minf(float a, float b)
// {
// 		if (a > b)
// 			return (b);
// 		else
// 			return (a);
// }
	// utils.c
int32_t		cleanup(t_rt *rt);

void		init_main(t_rt *rt, t_scene *scn, t_scene *read_scn, t_window *win);
int32_t		multithreaded(t_rt *rt);
int16_t 	setup_init_parsing(t_rt *rt, const int argc, const char *argv);

// init.c

void		set_starting_res_ratio(t_rt *rt, double delta_time);

#endif
#ifndef UTILS_H
# define UTILS_H
# include <common_defs.h>
# include <math.h>
# include <miniRT.h>

t_cint32	cleanup(t_rt *rt);

static inline float	rt_minf(float a, float b)
{
	if (a > b)
		return (b);
	else
		return (a);
}

// utils.c

t_vec4		bcast4(float scalar);
t_vec4		bcast3(float scalar);
float		clamp(float value, float min, float max);
t_vec4		vec_clamp(t_vec4 value, float min, float max);

#endif
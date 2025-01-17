#ifndef UTILS_H
# define UTILS_H
# include <common_defs.h>
# include <math.h>
# include <miniRT.h>

t_cint32	cleanup(t_rt *rt);

//	if many more math functions come, create ft_math.h
float	fast_sqrt(float number);
t_vec3	normalize(t_vec3 v);
t_vec3	subtract(t_vec3 a, t_vec3 b);
float	dot_product(t_vec3 a, t_vec3 b);

static inline float	rt_minf(float a, float b)
{
	if (a > b)
		return (b);
	else
		return (a);
}
#endif
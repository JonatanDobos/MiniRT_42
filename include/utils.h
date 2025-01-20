#ifndef UTILS_H
# define UTILS_H
# include <common_defs.h>
# include <math.h>
# include <miniRT.h>

#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

t_cint32	cleanup(t_rt *rt);

//	if many more math functions come, create ft_math.h
float	fast_sqrt(float number);
t_vec4	normalize(t_vec4 v);
t_vec4	subtract(t_vec4 a, t_vec4 b);
float	dot_product(t_vec4 a, t_vec4 b);
t_vec4	cross(t_vec4 a, t_vec4 b);

static inline float	rt_minf(float a, float b)
{
	if (a > b)
		return (b);
	else
		return (a);
}
#endif
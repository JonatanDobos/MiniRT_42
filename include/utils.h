#ifndef UTILS_H
# define UTILS_H
# include <common_defs.h>
# include <math.h>
# include <miniRT.h>

# define EPSILON 1e-6f

#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

# define RES_STEP_SIZE 1.0f
# define RES_RATIO_MAX 10.0f

t_cint32	cleanup(t_rt *rt);

//	if many more math functions come, create ft_math.h
float	fast_sqrt(float number);

// render.c:

void		set_pixel(t_window *win, uint16_t x, uint16_t y, t_vec4 color);

t_vec4		bcast4(float scalar)__attribute__((const, hot));
t_vec4		bcast3(float scalar)__attribute__((const, hot));

t_vec4		vcross(t_vec4 a, t_vec4 b)__attribute__((const, hot));
t_vec4		vnorm(t_vec4 v)__attribute__((const, hot));
t_vec4		vproj(t_vec4 a, t_vec4 b)__attribute__((const, hot));
t_vec4		vrefl(t_vec4 v, t_vec4 n)__attribute__((const, hot));
float		vlen(t_vec4 v)__attribute__((const, hot));
t_vec4		vrotate(t_vec4 v, t_vec4 axis, float angle);

t_vec4		vadd(t_vec4 a, t_vec4 b)__attribute__((const, hot));
t_vec4		vsub(t_vec4 a, t_vec4 b)__attribute__((const, hot));
t_vec4		vscale(t_vec4 v, float scalar)__attribute__((const, hot));
float		vdot(t_vec4 a, t_vec4 b)__attribute__((const, hot));
t_vec4		vmul(t_vec4 a, float s)__attribute__((const, hot));
t_vec4		vneg(t_vec4 v)__attribute__((const, hot));

static inline float	rt_minf(float a, float b)
{
	if (a > b)
		return (b);
	else
		return (a);
}
#endif
#ifndef MATHRT_H
# define MATHRT_H
# include <common_defs.h>
# include <mathRT.h>
# include <miniRT.h>

# define EPSILON 1e-6f

#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

// math.c

float		fast_sqrt(float number);

// vec_arithmetic.c

t_vec4		vadd(t_vec4 a, t_vec4 b)__attribute__((const, hot));
t_vec4		vsub(t_vec4 a, t_vec4 b)__attribute__((const, hot));
t_vec4		vscale(t_vec4 v, float scalar)__attribute__((const, hot));
t_vec4		vneg(t_vec4 v)__attribute__((const, hot));

// vec_geometry.c

t_vec4		vcross(t_vec4 a, t_vec4 b)__attribute__((const, hot));
t_vec4		vnorm(t_vec4 v)__attribute__((const, hot));
t_vec4		vproj(t_vec4 a, t_vec4 b)__attribute__((const, hot));
float		vdot(t_vec4 a, t_vec4 b)__attribute__((const, hot));
float		vlen(t_vec4 v)__attribute__((const, hot));

// vec_transform.c

t_vec4		vrefl(t_vec4 v, t_vec4 n)__attribute__((const, hot));
t_vec4		vrotate(t_vec4 v, t_vec4 axis, float angle);


#endif
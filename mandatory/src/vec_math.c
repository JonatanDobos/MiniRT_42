#include "../include/minirt_param.h"

t_vec4	vec_add(t_vec4 a, t_vec4 b)
{
	return (a + b);
}

t_vec4	vec_sub(t_vec4 a, t_vec4 b)
{
	return (a - b);
}

t_vec4	vec_scale(t_vec4 v, float scalar)
{
	const t_vec4	scale_vec = bcast4(scalar);

	return (v * scale_vec);
}

float	vec_dot(t_vec4 a, t_vec4 b)
{
	const t_vec4	vmult = a * b;

	return (vmult[X] + vmult[Y] + vmult[Z]);
}

// ! Where is this one used? isnt vec_scale the same?
t_vec4	vec_mul(t_vec4 a, float s)
{
	const t_vec4	scale_vec = bcast4(s);

	return (a * scale_vec);
}

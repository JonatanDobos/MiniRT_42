#include "../include/minirt_param.h"

t_vec4	vec_cross(t_vec4 a, t_vec4 b)
{
	return ((t_vec4)
	{
		a[Y] * b[Z] - a[Z] * b[Y],
		a[Z] * b[X] - a[X] * b[Z],
		a[X] * b[Y] - a[Y] * b[X]
	});
}

t_vec4	vec_normalize(t_vec4 v)
{
	const t_vec4	len = bcast4(vec_len(v));

	if (len[0] < EPSILON)
		return (v);
	return (v / len);
}

t_vec4	vec_project(t_vec4 a, t_vec4 b)
{
	return (vec_scale(b, vec_dot(a, b) / vec_dot(b, b)));
}

t_vec4	vec_reflect(t_vec4 v, t_vec4 n)
{
	return (vec_sub(v, vec_scale(n, 2.0f * vec_dot(v, n))));
}

float	vec_len(t_vec4 v)
{
	const t_vec4	vsquared = v * v;

	return (sqrtf(vsquared[X] + vsquared[Y] + vsquared[Z]));
}

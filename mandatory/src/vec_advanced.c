#include "../include/minirt_param.h"

t_eucl	vec_cross(t_eucl a, t_eucl b)
{
	return ((t_eucl)
	{
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
	});
}

t_eucl	vec_normalize(t_eucl v)
{
	const float	len = vec_len(v);

	if (len == 0.0f)
		return ((t_eucl){0, 0, 0});
	return ((t_eucl){v.x / len, v.y / len, v.z / len});
}

t_eucl	vec_project(t_eucl a, t_eucl b)
{
	return (vec_scale(b, vec_dot(a, b) / vec_dot(b, b)));
}

t_eucl	vec_reflect(t_eucl v, t_eucl n)
{
	return (vec_sub(v, vec_scale(n, 2.0f * vec_dot(v, n))));
}

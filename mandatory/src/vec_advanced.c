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

// Function to rotate a vector around an axis
t_vec4	vec_rotate(t_vec4 v, t_vec4 axis, float angle)
{
	const float cos_angle = cosf(angle);
	const float sin_angle = sinf(angle);

	return ((t_vec4)
	{
		v[X] * (cos_angle + axis[X] * axis[X] * (1 - cos_angle)) +
			 v[Y] * (axis[X] * axis[Y] * (1 - cos_angle) - axis[Z] * sin_angle) +
			 v[Z] * (axis[X] * axis[Z] * (1 - cos_angle) + axis[Y] * sin_angle),
		v[X] * (axis[Y] * axis[X] * (1 - cos_angle) + axis[Z] * sin_angle) +
			 v[Y] * (cos_angle + axis[Y] * axis[Y] * (1 - cos_angle)) +
			 v[Z] * (axis[Y] * axis[Z] * (1 - cos_angle) - axis[X] * sin_angle),
		v[X] * (axis[Z] * axis[X] * (1 - cos_angle) - axis[Y] * sin_angle) +
			 v[Y] * (axis[Z] * axis[Y] * (1 - cos_angle) + axis[X] * sin_angle) +
			 v[Z] * (cos_angle + axis[Z] * axis[Z] * (1 - cos_angle))
	});
}

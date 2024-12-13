#include "../include/minirt_param.h"

t_eucl	vec_add(t_eucl a, t_eucl b)
{
	return ((t_eucl){a.x + b.x, a.y + b.y, a.z + b.z});
}

t_eucl	vec_sub(t_eucl a, t_eucl b)
{
	return ((t_eucl){a.x - b.x, a.y - b.y, a.z - b.z});
}

float	vec_len(t_eucl v)
{
	return (sqrtf(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_eucl	vec_scale(t_eucl v, float scalar)
{
	return ((t_eucl){v.x * scalar, v.y * scalar, v.z * scalar});
}

float	vec_dot(t_eucl a, t_eucl b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

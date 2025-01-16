#include <miniRT.h>
#include <utils.h>

float	fast_sqrt(float number)
{
	const float	threehalfs = 1.5F;
	int32_t		i;
	float		x2;
	float		y;

	x2 = number * 0.5F;
	y = number;
	i = *(int32_t *)&y; // evil floating point bit level hacking
	i = 0x5f3759df - (i >> 1); // what the fuck?
	y = *(float *)&i;
	y = y * (threehalfs - (x2 * y * y)); // 1st iteration

	return (number * y);
}

t_vec3	normalize(t_vec3 v)
{
	t_cfloat length = fast_sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	return (v / length);
}

t_vec3	subtract(t_vec3 a, t_vec3 b)
{
	return (a - b);
}

float	dot_product(t_vec3 a, t_vec3 b)
{
	t_cvec3 result = a * b;
	return (result[0] + result[1] + result[2]);
}

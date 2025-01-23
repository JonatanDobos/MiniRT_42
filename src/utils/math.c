#include <miniRT.h>
#include <utils.h>

# define EPSILON 1e-6f

// typedef union {
// 	float f;
// 	uint32_t i;
// } float_int_union;
// float fast_sqrt(float number) {
// 	const float threehalfs = 1.5F;
// 	float x2 = number * 0.5F;
// 	float_int_union conv = { .f = number };

// 	conv.i = 0x5f3759df - (conv.i >> 1);
// 	conv.f = conv.f * (threehalfs - (x2 * conv.f * conv.f)); // 1st iteration

// 	return conv.f;
// }

float	fast_sqrt(float number)
{
	const float	threehalfs = 1.5F;
	const float	x2 = number * 0.5F;
	int32_t		i;
	float		y;

	y = number;
	i = *(int32_t *)&y; // evil floating point bit level hacking
	i = 0x5f3759df - (i >> 1); // what the fuck?
	y = *(float *)&i;
	y = y * (threehalfs - (x2 * y * y)); // 1st iteration
	return (number * y);
}

t_vec4	normalize(t_vec4 v)
{
	const float	length = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);

	if (length < EPSILON)
		return (v);
	return (v / length);
}

t_vec4	subtract(t_vec4 a, t_vec4 b)
{
	return (a - b);
}

float	dot_product(t_vec4 a, t_vec4 b)
{
	t_cvec4 result = a * b;
	return (result[0] + result[1] + result[2]);
}

t_vec4	cross(t_vec4 a, t_vec4 b)
{
	return ((t_vec4)
	{
		a[Y] * b[Z] - a[Z] * b[Y],
		a[Z] * b[X] - a[X] * b[Z],
		a[X] * b[Y] - a[Y] * b[X]
	});
}

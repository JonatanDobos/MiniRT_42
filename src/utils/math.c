#include <miniRT.h>
#include <utils.h>

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

/**
 * @brief Broadcasts scalar value to all four indexes of the t_vec4.
 * @param scalar Value to broadcast to vector[X, Y, Z, W].
 * @return (t_vec4){scalar, scalar, scalar, scalar}
 */
t_vec4	bcast4(float scalar)
{
	return ((t_vec4){scalar, scalar, scalar, scalar});
}

/**
 * @brief Broadcasts scalar value to first three indexes of the t_vec4.
 * @param scalar Value to broadcast to vector[X, Y, Z].
 * @return (t_vec4){scalar, scalar, scalar, 1.0f}
 */
t_vec4	bcast3(float scalar)
{
	return ((t_vec4){scalar, scalar, scalar, 1.0F});
}

// Vector cross-product.
t_vec4	vcross(t_vec4 a, t_vec4 b)
{
	return ((t_vec4)
	{
		a[Y] * b[Z] - a[Z] * b[Y],
		a[Z] * b[X] - a[X] * b[Z],
		a[X] * b[Y] - a[Y] * b[X]
	});
}

// Vector normalization.
t_vec4	vnorm(t_vec4 v)
{
	const t_vec4	len = bcast4(vlen(v));

	if (len[0] < EPSILON)
		return (v);
	return (v / len);
}

// Vector projection.
t_vec4	vproj(t_vec4 a, t_vec4 b)
{
	return (vscale(b, vdot(a, b) / vdot(b, b)));
}

// Vector reflection.
t_vec4	vrefl(t_vec4 v, t_vec4 n)
{
	return (vsub(v, vscale(n, 2.0F * vdot(v, n))));
}

// Vector length.
float	vlen(t_vec4 v)
{
	const t_vec4	vsquared = v * v;

	return (sqrtf(vsquared[X] + vsquared[Y] + vsquared[Z]));
}

// Vector rotate around an axis.
t_vec4	vrotate(t_vec4 v, t_vec4 axis, float angle)
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
			 v[Z] * (cos_angle + axis[Z] * axis[Z] * (1 - cos_angle)),
		v[W]
	});
}

// Vector addition.
t_vec4	vadd(t_vec4 a, t_vec4 b)
{
	return (a + b);
}

// Vector substraction.
t_vec4	vsub(t_vec4 a, t_vec4 b)
{
	return (a - b);
}

// Vector scaling.
t_vec4	vscale(t_vec4 v, float scalar)
{
	return (v * bcast4(scalar));
}

// Vector dot-product.
float	vdot(t_vec4 a, t_vec4 b)
{
	const t_vec4	vmult = a * b;

	return (vmult[X] + vmult[Y] + vmult[Z]);
}

// ! Where is this one used? isnt vscale the same?
// Vector multiply.
t_vec4	vmul(t_vec4 a, float s)
{
	const t_vec4	scale_vec = bcast4(s);

	return (a * scale_vec);
}

// Vector negate.
t_vec4 vneg(t_vec4 v)
{
	return (t_vec4){-v[X], -v[Y], -v[Z]};
}


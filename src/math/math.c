#include <miniRT.h>
#include <mathRT.h>

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
	union {
		float f;
		int32_t i;
	} conv;
	float		y;

	conv.f = number;
	conv.i = 0x5f3759df - (conv.i >> 1); // magic number
	y = conv.f;
	y = y * (threehalfs - (x2 * y * y)); // 1st iteration
	return (number * y);
}

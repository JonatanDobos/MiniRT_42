#include <miniRT.h>
#include <utils.h>

t_vec3	normalize(t_vec3 v)
{
    float length = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
    return (v / length);
}

t_vec3	subtract(t_vec3 a, t_vec3 b)
{
    return (a - b);
}

double	dot_product(t_vec3 a, t_vec3 b)
{
	t_vec3 result = a * b;
	return (result[0] + result[1] + result[2]);
}

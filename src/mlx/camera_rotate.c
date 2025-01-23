#include <RTmlx.h>
#include <scene.h>
#include <utils.h>

// Function to rotate a vector around an axis
t_vec4 rotate_vector(t_vec4 v, t_vec4 axis, float angle)
{
	const float cos_angle = cosf(angle);
	const float sin_angle = sinf(angle);

	return (t_vec4)
	{
		v[0] * (cos_angle + axis[0] * axis[0] * (1 - cos_angle)) +
		v[1] * (axis[0] * axis[1] * (1 - cos_angle) - axis[2] * sin_angle) +
		v[2] * (axis[0] * axis[2] * (1 - cos_angle) + axis[1] * sin_angle),

		v[0] * (axis[1] * axis[0] * (1 - cos_angle) + axis[2] * sin_angle) +
		v[1] * (cos_angle + axis[1] * axis[1] * (1 - cos_angle)) +
		v[2] * (axis[1] * axis[2] * (1 - cos_angle) - axis[0] * sin_angle),

		v[0] * (axis[2] * axis[0] * (1 - cos_angle) - axis[1] * sin_angle) +
		v[1] * (axis[2] * axis[1] * (1 - cos_angle) + axis[0] * sin_angle) +
		v[2] * (cos_angle + axis[2] * axis[2] * (1 - cos_angle)),

		v[3] // Assuming w is not affected by rotation
	};
}

# define EPSILON 1e-6f
#include <math.h>

float	vec_len(t_vec4 v)
{
	const t_vec4	vsquared = v * v;

	return (sqrtf(vsquared[X] + vsquared[Y] + vsquared[Z]));
}
t_vec4	vcast(float scalar)
{
	return ((t_vec4){scalar, scalar, scalar, scalar});
}

t_vec4	vec_normalize(t_vec4 v)
{
	const t_vec4	len = vcast(vec_len(v));

	if (len[0] < EPSILON)
		return (v);
	return (v / len);
}

// Rotate the camera orientation up
void	cam_rotate_up(t_scene *scene)
{
	printf("\033[0;36m rotate UP\033[0m\n");
	t_vec4 right = cross(scene->camera.c.orientation, (t_vec4){0, 1, 0});
	scene->camera.c.orientation = vec_normalize(rotate_vector(scene->camera.c.orientation, right, CAM_ROTATION_SPEED));
	scene->render = true;
}

// Rotate the camera orientation down
void	cam_rotate_down(t_scene *scene)
{
	printf("\033[0;36m rotate DOWN\033[0m\n");
	t_vec4 right = cross(scene->camera.c.orientation, (t_vec4){0, 1, 0});
	scene->camera.c.orientation = vec_normalize(rotate_vector(scene->camera.c.orientation, right, -CAM_ROTATION_SPEED));
	scene->render = true;
}

// Rotate the camera orientation left
void	cam_rotate_left(t_scene *scene)
{
	printf("\033[0;36m rotate LEFT\033[0m\n");
	scene->camera.c.orientation = vec_normalize(rotate_vector(scene->camera.c.orientation, (t_vec4){0, 1, 0}, -CAM_ROTATION_SPEED));
	scene->render = true;
}

// Rotate the camera orientation right
void	cam_rotate_right(t_scene *scene)
{
	printf("\033[0;36m rotate RIGHT\033[0m\n");
	scene->camera.c.orientation = vec_normalize(rotate_vector(scene->camera.c.orientation, (t_vec4){0, 1, 0}, CAM_ROTATION_SPEED));
	scene->render = true;
}

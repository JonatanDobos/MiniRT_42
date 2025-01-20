#include <RTmlx.h>
#include <scene.h>
#include <utils.h>

// Function to rotate a vector around an axis
t_vec4	rotate_vector(t_vec4 v, t_vec4 axis, float angle)
{
	const float cos_angle = cosf(angle);
	const float sin_angle = sinf(angle);

	return ((t_vec4)
	{
		v[X] = v[X] * (cos_angle + axis[X] * axis[X] * (1 - cos_angle)) +
			 v[Y] * (axis[X] * axis[Y] * (1 - cos_angle) - axis[Z] * sin_angle) +
			 v[Z] * (axis[X] * axis[Z] * (1 - cos_angle) + axis[Y] * sin_angle),
		v[Y] = v[X] * (axis[Y] * axis[X] * (1 - cos_angle) + axis[Z] * sin_angle) +
			 v[Y] * (cos_angle + axis[Y] * axis[Y] * (1 - cos_angle)) +
			 v[Z] * (axis[Y] * axis[Z] * (1 - cos_angle) - axis[X] * sin_angle),
		v[Z] = v[X] * (axis[Z] * axis[X] * (1 - cos_angle) - axis[Y] * sin_angle) +
			 v[Y] * (axis[Z] * axis[Y] * (1 - cos_angle) + axis[X] * sin_angle) +
			 v[Z] * (cos_angle + axis[Z] * axis[Z] * (1 - cos_angle))
	});
}

// Rotate the camera orientation up
void	cam_rotate_up(t_scene *scene)
{
	printf("KEY: UP\n");
	t_vec4 right = cross(scene->camera.camera.orientation, (t_vec4){0, 1, 0});
	scene->camera.camera.orientation = normalize(rotate_vector(scene->camera.camera.orientation, right, CAM_ROTATION_SPEED));
	scene->render = true;
}

// Rotate the camera orientation down
void	cam_rotate_down(t_scene *scene)
{
	printf("KEY: DOWN\n");
	t_vec4 right = cross(scene->camera.camera.orientation, (t_vec4){0, 1, 0});
	scene->camera.camera.orientation = normalize(rotate_vector(scene->camera.camera.orientation, right, -CAM_ROTATION_SPEED));
	scene->render = true;
}

// Rotate the camera orientation left
void	cam_rotate_left(t_scene *scene)
{
	printf("KEY: LEFT\n");
	scene->camera.camera.orientation = normalize(rotate_vector(scene->camera.camera.orientation, (t_vec4){0, 1, 0}, -CAM_ROTATION_SPEED));
	scene->render = true;
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

// Rotate the camera orientation right
void	cam_rotate_right(t_scene *scene)
{
	printf("KEY: RIGHT\n");
	// t_vec4 dobos = scene->camera.camera.orientation;
	printf("CAM orient r: x: %f, y: %f, z: %f\n", scene->camera.camera.orientation[X], scene->camera.camera.orientation[Y], scene->camera.camera.orientation[Z]);
	scene->camera.camera.orientation = vec_normalize(rotate_vector(scene->camera.camera.orientation, (t_vec4){0, 1, 0}, CAM_ROTATION_SPEED));
	printf("CAM orient r: x: %f, y: %f, z: %f\n", scene->camera.camera.orientation[X], scene->camera.camera.orientation[Y], scene->camera.camera.orientation[Z]);
	scene->render = true;
}

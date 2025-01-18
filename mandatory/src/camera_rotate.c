#include "../include/minirt_param.h"

// Function to rotate a vector around an axis
t_vec4	rotate_vector(t_vec4 v, t_vec4 axis, float angle)
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

// Rotate the camera orientation up
void	cam_rotate_up(t_scene *scene)
{
	printf("KEY: UP\n");
	t_vec4 right = vec_cross(scene->cam.orient, (t_vec4){0, 1, 0});
	scene->cam.orient = vec_normalize(rotate_vector(scene->cam.orient, right, CAM_ROTATION_SPEED));
	scene->render = true;
}

// Rotate the camera orientation down
void	cam_rotate_down(t_scene *scene)
{
	printf("KEY: DOWN\n");
	t_vec4 right = vec_cross(scene->cam.orient, (t_vec4){0, 1, 0});
	scene->cam.orient = vec_normalize(rotate_vector(scene->cam.orient, right, -CAM_ROTATION_SPEED));
	scene->render = true;
}

// Rotate the camera orientation left
void	cam_rotate_left(t_scene *scene)
{
	printf("KEY: LEFT\n");
	scene->cam.orient = vec_normalize(rotate_vector(scene->cam.orient, (t_vec4){0, 1, 0}, -CAM_ROTATION_SPEED));
	scene->render = true;
}

// Rotate the camera orientation right
void	cam_rotate_right(t_scene *scene)
{
	printf("KEY: RIGHT\n");
	scene->cam.orient = vec_normalize(rotate_vector(scene->cam.orient, (t_vec4){0, 1, 0}, CAM_ROTATION_SPEED));
	scene->render = true;
}

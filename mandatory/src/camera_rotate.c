#include "../include/minirt_param.h"

// Function to rotate a vector around an axis
t_eucl	rotate_vector(t_eucl v, t_eucl axis, float angle)
{
	const float cos_angle = cosf(angle);
	const float sin_angle = sinf(angle);

	return ((t_eucl)
	{
		.x = v.x * (cos_angle + axis.x * axis.x * (1 - cos_angle)) +
			 v.y * (axis.x * axis.y * (1 - cos_angle) - axis.z * sin_angle) +
			 v.z * (axis.x * axis.z * (1 - cos_angle) + axis.y * sin_angle),
		.y = v.x * (axis.y * axis.x * (1 - cos_angle) + axis.z * sin_angle) +
			 v.y * (cos_angle + axis.y * axis.y * (1 - cos_angle)) +
			 v.z * (axis.y * axis.z * (1 - cos_angle) - axis.x * sin_angle),
		.z = v.x * (axis.z * axis.x * (1 - cos_angle) - axis.y * sin_angle) +
			 v.y * (axis.z * axis.y * (1 - cos_angle) + axis.x * sin_angle) +
			 v.z * (cos_angle + axis.z * axis.z * (1 - cos_angle))
	});
}

// Rotate the camera orientation up
void	cam_rotate_up(t_scene *scene)
{
	printf("KEY: UP\n");
	t_eucl right = vec_cross(scene->cam.orient, (t_eucl){0, 1, 0});
	scene->cam.orient = vec_normalize(rotate_vector(scene->cam.orient, right, CAM_ROTATION_SPEED));
	scene->render = true;
}

// Rotate the camera orientation down
void	cam_rotate_down(t_scene *scene)
{
	printf("KEY: DOWN\n");
	t_eucl right = vec_cross(scene->cam.orient, (t_eucl){0, 1, 0});
	scene->cam.orient = vec_normalize(rotate_vector(scene->cam.orient, right, -CAM_ROTATION_SPEED));
	scene->render = true;
}

// Rotate the camera orientation left
void	cam_rotate_left(t_scene *scene)
{
	printf("KEY: LEFT\n");
	scene->cam.orient = vec_normalize(rotate_vector(scene->cam.orient, (t_eucl){0, 1, 0}, CAM_ROTATION_SPEED));
	scene->render = true;
}

// Rotate the camera orientation right
void	cam_rotate_right(t_scene *scene)
{
	printf("KEY: RIGHT\n");
	scene->cam.orient = vec_normalize(rotate_vector(scene->cam.orient, (t_eucl){0, 1, 0}, -CAM_ROTATION_SPEED));
	scene->render = true;
}

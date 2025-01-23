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

// Rotate the camera orientation up
void	cam_rotate_up(t_scene *scene)
{
	// printf("KEY: UP\n");
	t_vec4 right = cross(scene->camera.c.orientation, (t_vec4){0, 1, 0});
	scene->camera.c.orientation = normalize(rotate_vector(scene->camera.c.orientation, right, CAM_ROTATION_SPEED));
	scene->render = true;
}

// Rotate the camera orientation down
void	cam_rotate_down(t_scene *scene)
{
	// printf("KEY: DOWN\n");
	t_vec4 right = cross(scene->camera.c.orientation, (t_vec4){0, 1, 0});
	scene->camera.c.orientation = normalize(rotate_vector(scene->camera.c.orientation, right, -CAM_ROTATION_SPEED));
	scene->render = true;
}

// Rotate the camera orientation left
void	cam_rotate_left(t_scene *scene)
{
	// printf("KEY: LEFT\n");
	scene->camera.c.orientation = normalize(rotate_vector(scene->camera.c.orientation, (t_vec4){0, 1, 0}, -CAM_ROTATION_SPEED));
	scene->render = true;
}

void rotate_vector_x(t_vec4 *vec, float angle)
{
    float cos_angle = cos(angle);
    float sin_angle = sin(angle);
    float y = (*vec)[1] * cos_angle - (*vec)[2] * sin_angle;
    float z = (*vec)[1] * sin_angle + (*vec)[2] * cos_angle;
    (*vec)[1] = y;
    (*vec)[2] = z;
}
// Rotate the camera orientation right
void	cam_rotate_right(t_scene *scene)
{
	// printf("KEY: RIGHT\n");
	// t_vec4 dobos = scene->camera.camera.orientation;
	// printf("CAM orient r: x: %f, y: %f, z: %f\n", scene->camera.c.orientation[X], scene->camera.c.orientation[Y], scene->camera.c.orientation[Z]);
	// scene->camera.c.orientation = normalize(rotate_vector(scene->camera.c.orientation, (t_vec4){0, 1, 0}, CAM_ROTATION_SPEED));
	// printf("CAM orient r: x: %f, y: %f, z: %f\n", scene->camera.c.orientation[X], scene->camera.c.orientation[Y], scene->camera.c.orientation[Z]);

    rotate_vector_x(&scene->camera.c.orientation, CAM_ROTATION_SPEED);
    scene->camera.c.orientation = normalize(scene->camera.c.orientation);
    // printf("CAM orient r: x: %f, y: %f, z: %f\n", scene->camera.c.orientation[X], scene->camera.c.orientation[Y], scene->camera.c.orientation[Z]);
	scene->render = true;
}

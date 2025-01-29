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
void	cam_rotate_up(t_scene *sc)
{
	// printf("KEY: UP\n");
	t_vec4 right = cross(sc->camera.c.orientation, (t_vec4){0, 1, 0});
	sc->camera.c.orientation = vec_normalize(rotate_vector(sc->camera.c.orientation, right, sc->cam_r_speed));
	sc->render = true;
}

// Rotate the camera orientation down
void	cam_rotate_down(t_scene *sc)
{
	// printf("KEY: DOWN\n");
	t_vec4 right = cross(sc->camera.c.orientation, (t_vec4){0, 1, 0});
	sc->camera.c.orientation = vec_normalize(rotate_vector(sc->camera.c.orientation, right, -sc->cam_r_speed));
	sc->render = true;
}

// Rotate the camera orientation left
void	cam_rotate_left(t_scene *sc)
{
	// printf("KEY: LEFT\n");
	sc->camera.c.orientation = vec_normalize(rotate_vector(sc->camera.c.orientation, (t_vec4){0, 1, 0}, -sc->cam_r_speed));
	sc->render = true;
}

void	cam_rotate_right(t_scene *sc)
{
	// printf("\033[0;36m RIGHT\033[0m\n");
	sc->camera.c.orientation = vec_normalize(vec_rotate(sc->camera.c.orientation, (t_vec4){0, 1, 0}, sc->cam_r_speed));
	sc->render = true;
}

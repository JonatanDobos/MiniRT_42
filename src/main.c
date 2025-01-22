#include <stdlib.h>
#include <miniRT.h>
#include <parsing.h>
#include <scene.h>
#include <RTmlx.h>
#include <utils.h>

bool	check_input(t_rt *rt, int argc, char **argv)
{
	(void)rt;
	(void)argc;
	(void)argv;
	return (EXIT_SUCCESS);
}

void	init_main(t_rt *rt, t_scene *scn, t_window *win)
{
	ft_bzero(rt, sizeof(t_rt));
	ft_bzero(scn, sizeof(t_scene));
	ft_bzero(win, sizeof(t_window));
	errset((int64_t)rt->errnum);
	rt->scene = scn;
	rt->win = win;

}
int main(int argc, char **argv)
{
	t_rt		rt;
	t_scene		sc;
	t_window	win;

	printf("miniRT startwatch %f\n", mlx_get_time());
	init_main(&rt, &sc, &win);
	if (check_input(&rt, argc, argv) == EXIT_FAILURE || \
		input_parse(&rt, argv[1]) != 0 || \
		windows_setup_mlx(&rt) == EXIT_FAILURE)
	{
		return (perr("Parsing", errset(ERTRN)), cleanup(&rt));
	}
	render_scene(&rt, rt.scene);

	printf("%f\n", mlx_get_time());

	mlx_loop(rt.win->mlx); // Start the MLX loop
	// mlx_run_time()
	cleanup(&rt);
	printf("exiting miniRT\n");
	return (EXIT_SUCCESS);
}


// GitHub Copilot
// Correct, changing the field of view (FOV) does not directly affect the distance to a viewpoint. The FOV is an angular measurement that determines how wide or narrow the camera's view is. Adjusting the FOV changes the perspective and how much of the scene is visible, but it does not change the distance to objects in the scene.

// If you need to adjust the distance to a viewpoint, you would typically move the camera position or adjust the projection matrix parameters, but not the FOV itself.

// RJW-db
// but if the windows where it's projected on is 16:9, and you widen the fov, the window doesn't get widen thus the screen will distort?

// GitHub Copilot
// Yes, if you widen the field of view (FOV) while keeping the aspect ratio (such as 16:9) constant, the image will appear more distorted. This is because a wider FOV means that more of the scene is being projected onto the same screen space, leading to a "fish-eye" effect where objects near the edges of the screen appear stretched.

// To handle this correctly, you need to adjust the projection matrix to account for the aspect ratio and the new FOV. Here's an example of how you might set up a perspective projection matrix in a typical graphics application:

// #include <math.h>

// typedef struct {
//     float fov; // Field of view in degrees
//     float aspect_ratio; // Aspect ratio of the screen (width / height)
//     float near_plane; // Near clipping plane
//     float far_plane; // Far clipping plane
// } t_camera;

// void set_perspective_projection_matrix(t_camera *camera, float matrix[4][4]) {
//     float fov_rad = camera->fov * (M_PI / 180.0f); // Convert FOV to radians
//     float tan_half_fov = tan(fov_rad / 2.0f);

//     matrix[0][0] = 1.0f / (camera->aspect_ratio * tan_half_fov);
//     matrix[1][1] = 1.0f / tan_half_fov;
//     matrix[2][2] = -(camera->far_plane + camera->near_plane) / (camera->far_plane - camera->near_plane);
//     matrix[2][3] = -1.0f;
//     matrix[3][2] = -(2.0f * camera->far_plane * camera->near_plane) / (camera->far_plane - camera->near_plane);
//     matrix[3][3] = 0.0f;
// }

// This function sets up a perspective projection matrix based on the camera's FOV, aspect ratio, and near/far clipping planes. Adjusting the FOV will change the perspective, but the aspect ratio ensures that the image does not get distorted.


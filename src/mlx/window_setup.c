#include <stdlib.h>
#include <miniRT.h>
#include <RTmlx.h>

//	Static Functions
static bool	init_mlx(t_rt *rt);
static bool	img_to_window(t_rt *rt);
static bool	windows_logo(t_rt *rt);
static void	center_window(t_rt *rt);

bool	windows_setup_mlx(t_rt *rt)
{
	if (init_mlx(rt) == false || \
		img_to_window(rt) == false || \
		windows_logo(rt) == false)
		return (EXIT_FAILURE);
	center_window(rt);
	mlx_set_window_title(rt->mlx, "miniRT");
	// mlx_set_window_title(rt->mlx, "miniRT is still rendering!");
	mlx_key_hook(rt->mlx, (mlx_keyfunc)my_keyhook, rt);

	return (EXIT_SUCCESS);
}

static bool	init_mlx(t_rt *rt)
{
	rt->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "miniRT is setting up MLX", true);
	if (rt->mlx == NULL)
		return (false);
	return (true);
}

static bool	img_to_window(t_rt *rt)
{
	rt->img = mlx_new_image(rt->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (rt->img == NULL)
		return (false);
	if (mlx_image_to_window(rt->mlx, rt->img, 0, 0) == -1)
		return (false);
	return (true);
}

static bool	windows_logo(t_rt *rt)
{
	mlx_texture_t	*logo_texture;

	logo_texture = mlx_load_png(LOGO_PATH);
	if (logo_texture == NULL)
		return (false);
	mlx_set_icon(rt->mlx, logo_texture);
	mlx_delete_texture(logo_texture);
	return (true);
}

static void	center_window(t_rt *rt)
{
	int32_t	window_x;
	int32_t	window_y;

	// window_x = (SCREEN_WINDOW_WIDTH - WINDOW_WIDTH) / 2;
	// window_y = (SCREEN_WINDOW_HEIGHT - WINDOW_HEIGHT) / 2;
	mlx_get_monitor_size(0, &window_x, &window_y);
	window_x = (window_x - WINDOW_WIDTH) / 2;
	window_y = (window_y - WINDOW_HEIGHT) / 2;
	mlx_set_window_pos(rt->mlx, window_x, window_y);
}

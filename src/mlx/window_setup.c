#include <stdlib.h>
#include <miniRT.h>
#include <RTmlx.h>

//	Static Functions
static bool	init_mlx(t_window *win);
static bool	img_to_window(t_window *win);
static bool	windows_logo(t_window *win);
static void	center_window(t_window *win);

bool	windows_setup_mlx(t_rt *rt)
{
	if (init_mlx(rt->win) == false || \
		img_to_window(rt->win) == false || \
		windows_logo(rt->win) == false)
		return (EXIT_FAILURE);
	center_window(rt->win);
	mlx_set_window_title(rt->win->mlx, "miniRT");
	// mlx_set_window_title(win->mlx, "miniRT is still rendering!");
	init_hooks(rt);

	return (EXIT_SUCCESS);
}

static bool	init_mlx(t_window *win)
{
	// resize = false!
	win->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "miniRT is setting up MLX", false);
	if (win->mlx == NULL)
		return (false);
	return (true);
}

static bool	img_to_window(t_window *win)
{
	win->img = mlx_new_image(win->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (win->img == NULL)
		return (false);
	win->id = mlx_image_to_window(win->mlx, win->img, 0, 0);
	if (win->id == -1)
		return (false);
	return (true);
}

static bool	windows_logo(t_window *win)
{
	mlx_texture_t	*logo_texture;

	logo_texture = mlx_load_png(LOGO_PATH);
	if (logo_texture == NULL)
		return (false);
	mlx_set_icon(win->mlx, logo_texture);
	mlx_delete_texture(logo_texture);
	return (true);
}

static void	center_window(t_window *win)
{
	int32_t	window_x;
	int32_t	window_y;

	// window_x = (SCREEN_WINDOW_WIDTH - WINDOW_WIDTH) / 2;
	// window_y = (SCREEN_WINDOW_HEIGHT - WINDOW_HEIGHT) / 2;
	mlx_get_monitor_size(0, &window_x, &window_y);

	win->rndr_hght = WINDOW_HEIGHT;
	win->rndr_wdth = WINDOW_WIDTH;
	win->window_hght = WINDOW_HEIGHT;
	win->window_wdth = WINDOW_WIDTH;
	win->aspectrat = (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT;
	win->pixels = (uint8_t *)win->img->pixels;

	printf("x %d\ny = %d\n", window_x, window_y);
	printf("win->aspectrat = %f\n", win->aspectrat);
	window_x = (window_x - WINDOW_WIDTH) / 2;
	window_y = (window_y - WINDOW_HEIGHT) / 2;
	mlx_set_window_pos(win->mlx, window_x, window_y);
}

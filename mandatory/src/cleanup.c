#include "../include/minirt_param.h"

/**
 * @brief Terminates mlx, and sets all bytes to 0.
 * @param win Pointer to t_window to be cleaned.
 */
void	clean_window(t_window *win)
{
	if (win == NULL)
		return ;
	if (win->mlx)
	{
		if (win->img)
			mlx_delete_image(win->mlx, win->img);
		mlx_close_window(win->mlx);
		mlx_terminate(win->mlx);
	}
	ft_bzero(win, sizeof(t_window));
}

/**
 * @brief Frees what was malloc'd, and sets all bytes to 0.
 * @param sc Pointer to t_scene to be cleaned.
 */
void	clean_scene(t_scene *sc)
{
	if (sc == NULL)
		return ;
	ft_vfree((void **)&sc->cam);
	ft_vfree((void **)&sc->light);
	ft_vfree((void **)&sc->plane);
	ft_vfree((void **)&sc->sphere);
	ft_vfree((void **)&sc->cilinder);
	ft_bzero(sc, sizeof(t_scene));
}

/**
 * @brief Frees what was malloc'd, and sets all bytes to 0.
 * @param mrt Pointer to t_minirt to be cleaned.
 */
void	clean_all(t_minirt *mrt)
{
	clean_scene(&mrt->scene);
	clean_window(&mrt->win);
	ft_bzero(&mrt->errnum, sizeof(mrt->errnum));
}

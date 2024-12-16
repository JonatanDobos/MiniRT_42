#include "../include/minirt_param.h"

/**
 * @brief Terminates mlx, and sets all bytes to 0.
 * @param win Pointer to t_window to be cleaned.
 */
void	clean_window(t_window *win)
{
	const int	err_backup = errno;
	const int	errmlx_backup = mlx_errno;

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
	errno = err_backup;
	mlx_errno = errmlx_backup;
}

/**
 * @brief Frees what was malloc'd, and sets all bytes to 0.
 * @param sc Pointer to t_scene to be cleaned.
 */
void	clean_scene(t_scene *sc)
{
	const int	err_backup = errno;

	if (sc == NULL)
		return ;
	ft_vfree((void **)&sc->plane);
	ft_vfree((void **)&sc->sphere);
	ft_vfree((void **)&sc->cilinder);
	ft_bzero(sc, sizeof(t_scene));
	errno = err_backup;
}

/**
 * @brief Frees what was malloc'd, and sets all bytes to 0.
 * @param m Pointer to t_minirt to be cleaned.
 */
void	clean_all(t_minirt *m)
{
	clean_scene(&m->scene);
	clean_window(&m->win);
}

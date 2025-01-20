#ifndef RTMLX_H
# define RTMLX_H
# include <MLX42/MLX42.h>
# include <common_defs.h>
# define LOGO_PATH "images/glasses.png"

bool	windows_setup_mlx(t_window *win);
void	my_keyhook(mlx_key_data_t keydata, t_window *win);

typedef struct s_window
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	uint8_t			*pixels;
	int16_t			id;
	uint16_t		rndr_wdth;
	uint16_t		rndr_hght;
	uint16_t		set_rndr_hght;
	float			ratio_w;
	bool			resize;
	mlx_texture_t	*logo;
}	t_window;

#endif
#ifndef RTMLX_H
# define RTMLX_H
# include <MLX42/MLX42.h>

# define LOGO_PATH "images/glasses.png"

bool	windows_setup_mlx(t_rt *rt);
void	my_keyhook(mlx_key_data_t keydata, t_rt *rt);


#endif
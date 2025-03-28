#include <MLX42/MLX42.h>
#include <scene.h>
#include <utils.h>
#include <RTmlx.h>
#include <render.h>

void	set_starting_res_ratio(t_rt *rt, double delta_time)
{
	const double	target_time = 0.014F + ((float)(SCREEN_HEIGHT + SCREEN_WIDTH) * 0.000001F);
	const double	error = delta_time - target_time;
	const double	adjustment_factor = 8.0F;
	const double	new_ratio = rt->win->res_r_start * (1.0F + (error * adjustment_factor));

	rt->win->res_r_start = intclamp((int)new_ratio, 2, 30);
}

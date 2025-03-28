#include <MLX42/MLX42.h>
#include <scene.h>
#include <utils.h>
#include <RTmlx.h>
#include <render.h>

void	set_starting_res_ratio(t_rt *rt, double delta_time)
{
	const double	target_time = 0.018F + ((float)(SCREEN_HEIGHT + SCREEN_WIDTH) * 0.000001F); // Target render time
	const double	error = delta_time - target_time;
	const double	adjustment_factor = 7.0F; // Tune this to control sensitivity
	const double	new_ratio = rt->win->res_r_start * (1.0F + (error * adjustment_factor));

	rt->win->res_r_start = intclamp((int)new_ratio, 2, 30);
	pthread_mutex_lock(rt->mtx + MTX_PRINT);
	printf("\n\\/ DTime: %.4f sec, target: %.4f sec\n|  err: %.4f sec, start res_r: %hu\n", 
		delta_time, target_time, error, rt->win->res_r_start);
	pthread_mutex_unlock(rt->mtx + MTX_PRINT);
}

#include <stdlib.h>
#include <miniRT.h>
#include <RTmlx.h>
#include <render.h>
#include <miniRT.h>
#include <threadsRT.h>

void	init_threads_structs(t_rt *rt, t_thread *th)
{
	th->rt = rt;
	th->scene = rt->read_scene;
	th->win = rt->win;
	th->img = rt->win->img;
	th->pixels = rt->win->pixels;
	th->aspectr = rt->win->aspectrat;
	th->y_index = &rt->win->y_shared;
}

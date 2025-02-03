#ifndef RENDER_H
# define RENDER_H
# include <common_defs.h>
# include <math.h>
# include <miniRT.h>

# define RES_STEP_SIZE 1.0f
# define RES_RATIO_MAX 10.0f

// render.c:

void		set_pixel(t_window *win, uint16_t x, uint16_t y, t_vec4 color);

#endif
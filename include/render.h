#ifndef RENDER_H
# define RENDER_H
# include <common_defs.h>
# include <math.h>
# include <miniRT.h>

# define RES_STEP_SIZE 1.0f
# define RES_RATIO_MAX 10.0f

#define MAX_DEPTH 5

// render.c:

void		set_pixel(t_window *win, uint16_t x, uint16_t y, t_vec4 color);

// lighting.c

t_vec4		calculate_lighting(
	t_scene *scene, t_vec4 point, t_vec4 normal, t_vec4 obj_color);

// cylinder.c

uint8_t		ray_intersect_cylinder(t_ray ray, t_objs *obj, float *t);

// set_pixels.c

void		set_pixel(t_window *win, uint16_t x, uint16_t y, t_vec4 color);
void		scaled_res_set_pixel(t_window *w, uint16_t x, uint16_t y, t_vec4 color);

#endif
#ifndef RENDER_H
# define RENDER_H
# include <common_defs.h>
# include <math.h>
# include <miniRT.h>
# include <scene.h>

# define RES_STEP_SIZE 1.0F
# define RES_RATIO_MAX 20.0F
# define RES_R_LOW 18.0F
# define RES_R_FULL 1.0F

# define SHADOW_EPSILON 1e-3F

typedef enum e_intersect_types
{
	CYL_BODY = 1,
	CYL_TOP,
	CYL_BOTTOM
}	t_intersect_type;

// set_pixel.c

void		set_pixel(t_window *win, uint16_t x, uint16_t y, t_vec4 color);

// lighting.c

t_vec4		calc_lighting(t_scene *sc, t_vec4 point, t_vec4 normal, t_vec4 obj_color);
bool		calc_shadow(t_scene *sc, t_ray ray, t_vec4 light_dir, uint32_t light);
t_objs		*render_light(t_scene *scene, t_ray ray, float *closest_t, t_objs *closest_obj);

// obj_intersect.c

uint8_t		ray_intersect_plane(t_ray ray, t_objs *obj, float *t);
uint8_t		ray_intersect_sphere(t_ray ray, t_objs *obj, float *t);

// cylinder.c

uint8_t		ray_intersect_cylinder(t_ray ray, t_objs *obj, float *t);

// set_pixels.c

void		set_pixel(t_window *win, uint16_t x, uint16_t y, t_vec4 color);
void		scaled_res_set_pixel(t_window *w, uint16_t x, uint16_t y, t_vec4 color);

// trace_ray.c

t_vec4		trace_ray(t_scene *scene, t_ray ray);
t_vec4		transform_ray_dir(t_vec4 ndc_dir, t_vec4 cam_orient);
uint8_t		ray_intersect_table(t_ray ray, t_objs *obj, float *t);
uint32_t	find_closest_object(t_scene *scene, t_ray ray, float *closest_t, uint8_t *closest_intersect_type);

// render_upscale.c

void		render_manager(t_rt *rt);

void		thread_render(t_thread *th);

#endif
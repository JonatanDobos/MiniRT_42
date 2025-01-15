#ifndef MINIRT_H
# define MINIRT_H

# include <libft.h>
# include <dynarr.h>
# include <MLX42/MLX42.h>
#include <math.h>
#include <stdio.h>

#ifndef SCREEN_WIDTH
# define SCREEN_WIDTH 800
#endif

#ifndef SCREEN_HEIGHT
# define SCREEN_HEIGHT ((int)(WIDTH / ASPECT_RATIO))
#endif

#define WIDTH 800
#define ASPECT_RATIO (16.0 / 9.0)
#define HEIGHT ((int)(WIDTH / ASPECT_RATIO))
// #define HEIGHT 800
#define OBJS_AMOUNT 2
#define NUM_OBJ_TYPES 2

// typedef enum e_obj_types	t_obj_type;
// typedef struct s_objs		t_objs;
typedef float				t_vec3 __attribute__ ((vector_size(16)));
// // typedef union u_vec			t_vec;
// typedef struct s_viewpoint	t_vp;
// // typedef union u_rgb		t_rgb;
// // typedef struct s_vec	t_vec3;
// typedef struct s_plane		t_plane;
// typedef struct s_sphere		t_sphere;
// typedef struct s_camera		t_camera;
typedef struct s_scene		t_scene;

typedef struct s_rt			t_rt;

enum e_axis {
	X,
	Y,
	Z
};

struct s_rt
{
	char			**map;
	mlx_t			*mlx;
	mlx_texture_t	*logo;

	mlx_image_t		*img;
	// t_vp			vp;
	t_scene			*scene;
	
};


//	forward declaration,		Could be resolve by including scene.h into main.c
void	object_array(t_rt *rt);
void	render_scene(t_rt *rt, t_scene *scn);


static inline float	rt_minf(float a, float b)
{
	if (a > b)
		return (b);
	else
		return (a);
}
#endif

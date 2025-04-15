#ifndef SCENE_H
# define SCENE_H

# include <stdlib.h>
# include <miniRT.h>
# include <dynarr.h>
# include <dbltoa.h>

# define RT_MAX_LINE_LEN 150
//	3 objects, Plane Sphere Cylinder
# define NUM_OBJ_TYPES 3

enum e_axis
{
	X,
	Y,
	Z,
	W
};

enum e_rgba
{
	R,
	G,
	B,
	A
};

typedef struct s_axis2_16
{
	uint16_t		x;
	uint16_t		y;
}	t_axis2;

typedef struct s_ray
{
	t_vec4		origin;
	t_vec4		vec;
}	t_ray;

typedef struct s_light
{
	float		brightness;
	float		radius;
	bool		intersect_lights;
	bool		visible;
}	t_light;

typedef struct s_amblight
{
	float		ratio;
}	t_amblight;

typedef enum e_obj_types
{
	PLANE,
	SPHERE,
	CYLINDER,
	LIGHT,
	AMBIENT
}	t_obj_type;

typedef struct	s_plane
{
	t_vec4	orientation;
}	t_plane;

typedef struct	s_sphere
{
	float	radius;
	float	diameter;
}	t_sphere;

typedef struct	s_cylinder
{
	t_vec4	orientation;
	float	radius;
	float	diameter;
	float	height;
}	t_cylinder;

typedef struct	s_camera
{
	t_vec4	orientation;
	float	fov;
	float	zvp_dist;
}	t_camera;

typedef struct	s_objs
{
	t_obj_type		type;
	union
	{
		t_camera	c;
		t_amblight	a;
		t_light		l;

		t_plane		plane;
		t_sphere	sphere;
		t_cylinder	cylinder;
	};
	t_vec4			coords;
	t_vec4			color;
}	t_objs;

typedef struct	s_scene
{
	t_objs		camera;
	t_objs		ambient;
	bool		render;
	bool		render_ongoing;
	struct
	{
		t_objs		*objs;
		size_t		o_arr_size;	
	};
	struct
	{
		t_objs		*lights;
		size_t		l_arr_size;
	};
	t_objs		*selected_obj;
	ssize_t		sel_obj_index;
	float		cam_m_speed;
	float		cam_r_speed;
	float		cam_fov_speed;
	bool		soft_shadows;
	uint16_t	shadow_grsize;
}	t_scene;

void	create_scene_rt_file(t_scene *sc, const char *filename);
size_t	color_line(t_dbltoa *dbl, char *rt_line, t_vec4 color);
size_t	coords_line(t_dbltoa *dbl, char *rt_line, t_vec4 coords);

void	ambient_line(t_objs *ambient, t_dbltoa *dbl, int fd);
void	camera_line(t_objs *camera, t_dbltoa *dbl, int fd);
void	lights_line(t_objs *lights, size_t amount, t_dbltoa *dbl, int fd);

void	objs_line(t_objs *objs, size_t amount, t_dbltoa *dbl, int fd);

void	print_obj_info(t_scene *sc);
void	geometric_primitives(t_objs *obj);
#endif
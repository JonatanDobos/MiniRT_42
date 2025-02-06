#ifndef SCENE_H
# define SCENE_H

# include <stdlib.h>
# include <miniRT.h>
# include <dynarr.h>


//	3 objects, Plane Sphere Cylinder
# define NUM_OBJ_TYPES 3

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
	LIGHT
}	t_obj_type;

typedef struct	s_plane
{
	t_vec4	orientation;
}	t_plane;

typedef struct	s_sphere
{
	float radius;
	float diameter;
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
	float	realtime_fov;
	float	zvp_dist;
	// t_fvec	rotated;
	// float	rotation[2];
	// t_fvec	u;
	// t_fvec	v;
	// t_fvec	proj_vec;
	// float	exposure;
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
	t_objs	camera;
	// t_objs	light;
	t_objs	ambient;
	bool	render;
	struct
	{
		t_dynarr	obj_dynarr;
		t_objs		*objs;
		size_t		o_arr_size;	
	};
	struct
	{
		t_dynarr	light_dynarr;
		t_objs		*lights;
		size_t		l_arr_size;	
	};
	t_objs	*selected_obj;
	ssize_t	sel_obj_index;
	float	cam_m_speed;
	float	cam_r_speed;
	float	cam_fov_speed;
}	t_scene;

void	render(t_rt *rt);

#endif
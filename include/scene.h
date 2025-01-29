#ifndef SCENE_H
# define SCENE_H

# include <stdlib.h>
# include <miniRT.h>
# include <dynarr.h>

// typedef union u_vec			t_vec;

//	3 objects, Plane Sphere Cylinder
# define NUM_OBJ_TYPES 3

# define FOV_MAX 180.0f

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
}	t_light;

typedef struct s_amblight
{
	float		ratio;
}	t_amblight;

typedef enum e_obj_types
{
	PLANE,
	SPHERE,
	CYLINDER
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
	float			hit;	//	Evt weg pleuren
}	t_objs;

typedef struct	s_scene
{
	t_objs	camera;
	t_objs	light;
	t_objs	ambient;
	bool	render;
	struct
	{
		t_dynarr	obj_dynarr;
		t_objs		*objs;
		size_t		arr_size;	
	};
	float	cam_m_speed;
	float	cam_r_speed;
	// t_object	ambient;
	// t_object	*lights;
	// size_t		lights_len;
	// t_object	*objects;
	// size_t		objects_len;
	// t_bvh		bvh;
	// t_mtl		*materials;
	// size_t		materials_len;
	// float		scale;
}	t_scene;

// bool	scene_creation(t_rt *rt);


// t_plane	plane(t_rt *rt);
// t_sphere sphere(t_rt *rt);

// void render_scene(t_rt *rt, mlx_image_t *img, t_objs *objarr, t_vp *vp);
void	render_scene(t_rt *rt, t_scene *scn);
void	render(t_rt *rt);

#endif
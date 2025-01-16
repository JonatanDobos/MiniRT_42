#ifndef SCENE_H
# define SCENE_H

# include <stdlib.h>
# include <miniRT.h>
# include <dynarr.h>

// typedef union u_vec			t_vec;

//	3 objects, Plane Sphere Cylinder
# define NUM_OBJ_TYPES 3

typedef enum e_obj_types
{
	PLANE,
	SPHERE,
	CYLINDER
}	t_obj_type;

// union u_vec
// {
// 	t_vec3 vec3;
// 	struct
// 	{
// 		float x;
// 		float y;
// 		float z;
// 		float w; // Padding or additional value
// 	};
// 	struct
// 	{
// 		float r;
// 		float g;
// 		float b;
// 		float a; // Padding or alpha value for color
// 	};
// 	// struct
// 	// {
// 	// 	float i;
// 	// 	float j;
// 	// 	float k;
// 	//	float l; // Padding or additional value
// 	// };
// };

typedef struct	s_viewpoint
{
	// t_vec3	ray_position;
	t_vec3	coords;
}	t_vp;

typedef struct	s_plane
{
	// t_vec3	point;
	t_vec3	direction;
	// t_vec3	color;
}	t_plane;

typedef struct	s_sphere
{
	// t_vec3 center;
	float radius;
	// t_vec3 color;
}	t_sphere;

typedef struct	s_cylinder
{
	t_vec3	direction;
	float	radius;
	float	height;
}	t_cylinder;

typedef struct	s_camera {
	t_vec3	ray_direction;
	float	fov;
	t_vec3	orientation;
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
		t_camera	camera;
		t_vp		vp;

		t_plane		plane;
		t_sphere	sphere;
		t_cylinder	cylinder;
	};
	t_vec3			coords;
	t_vec3			color;
	float			hit;
}	t_objs;


typedef struct	s_scene {
	t_objs	camera;
	struct
	{
		t_objs		*objarr;
		size_t		arr_size;	
	};
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

bool	scene_creation(t_rt *rt);


// t_plane	plane(t_rt *rt);
// t_sphere sphere(t_rt *rt);

// void render_scene(t_rt *rt, mlx_image_t *img, t_objs *objarr, t_vp *vp);
void	render_scene(t_rt *rt, t_scene *scn);

#endif
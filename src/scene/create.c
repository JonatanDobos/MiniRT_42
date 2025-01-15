#include <miniRT.h>
#include <scene.h>

void	assign_plane(t_objs *obj, t_vec3 v)
{
	// t_plane	*plane = &obj->plane;
	// t_vec3 direction = {.x = 0.0, .y = 1.0, .z = 0.7};
	obj->plane.direction = v;
}

void	assign_sphere(t_objs *obj, t_vec3 v)
{
	// t_sphere	*sphere = &obj->sphere;
	// sphere->radius = 10;
	obj->sphere.radius = v[X];
}

void	obj_assign_table(t_objs *obj, t_obj_type type, t_vec3 v)
{
	static void	(*assign_obj[NUM_OBJ_TYPES])(t_objs *, t_vec3) = {
		assign_plane,
		assign_sphere
	};

	assign_obj[type](obj, v);
}

void	plane_sphere(t_dynarr *arr, t_scene *scn)
{
	t_objs plane1;
	plane1.type = PLANE;
	plane1.coords = (t_vec3) {0.0, 0.0, -1.0};
	plane1.color = (t_vec3) {0.0, 0.5, 0.5, 1};

	t_vec3 direction = {0.0, 1.0, 0.7};
	obj_assign_table(&plane1, plane1.type, direction);
	dynarr_insert(arr, &plane1);

	t_objs sphere1;
	sphere1.type = SPHERE;
	sphere1.coords = (t_vec3) {-1.0, 0.0, -1.0};
	sphere1.color = (t_vec3) {0.5, 0.0, 0.5, 1.0};

	t_vec3 radius = {10};
	obj_assign_table(&sphere1, sphere1.type, radius);
	dynarr_insert(arr, &sphere1);
}

void	sphere_behind_another_sphere(t_dynarr *arr, t_scene *scn)
{
	t_objs sphere1;
	sphere1.type = SPHERE;
	sphere1.coords = (t_vec3) {0.0, 0.0, -5.0};
	sphere1.color = (t_vec3) {1.0, 0.0, 0.0, 1};

	t_vec3 radius = {10};
	obj_assign_table(&sphere1, sphere1.type, radius);
	dynarr_insert(arr, &sphere1);

	sphere1.coords = (t_vec3) {0.0, 0.0, 5.0};
	sphere1.color = (t_vec3) {1.0, 1.0, 1.0, 1};

	t_vec3 radius2 = {10};
	obj_assign_table(&sphere1, sphere1.type, radius2);

	dynarr_insert(arr, &sphere1);
}

void	spheres_next_to_eachother(t_dynarr *arr, t_scene *scn)
{
	t_objs sphere1;
	sphere1.type = SPHERE;
	sphere1.coords = (t_vec3) {-5.0, 0.0, -1.0};
	sphere1.color = (t_vec3) {1.0, 0.0, 0.0, 1};

	t_vec3 radius = {10};
	obj_assign_table(&sphere1, sphere1.type, radius);
	dynarr_insert(arr, &sphere1);

	sphere1.coords = (t_vec3) {5.0, 0.0, -1.0};
	sphere1.color = (t_vec3) {1.0, 1.0, 1.0, 1};

	t_vec3 radius2 = {10};
	obj_assign_table(&sphere1, sphere1.type, radius2);

	dynarr_insert(arr, &sphere1);
}
void	create_each_obj(t_dynarr *arr, t_rt *rt, t_scene *scn)
{
	// size_t	i;

	// i = 0;
	// while (i < rt->arr_size)
	// {
	// 	obj_assign_table(&rt->objarr[i], rt->objarr[i].type);
	// 	++i;
	// }

	plane_sphere(arr, scn);
	// sphere_behind_another_sphere(arr,scn);
	// spheres_next_to_eachother(arr, scn);

	scn->objarr = arr->arr;
	scn->arr_size = arr->length;
}

void	camera_setup(t_rt *rt, t_objs *obj)
{
	// // rt.vp.ray_position = (t_vec) {.x = 0.0, .y = 0.0, .z = -1.0};
	// rt.vp.ray_position = (t_vec) {.x = 0.0, .y = 0.0, .z = 20.0};
	// rt.vp.ray_direction = (t_vec) {.x = 0.0, .y = 0.5, .z = -0.8}; // Example direction vector
	// // rt.vp.ray_direction = normalize((t_vec) {.x = 0.0, .y = 0.5, .z = -0.8});

	obj->coords = (t_vec3){0.0, 0.0, 20.0};
	obj->camera.ray_direction = (t_vec3){0.0, 0.0, -1.0};
	obj->camera.fov = 60;
}

bool	alloc_scene_struct(t_scene **scn)
{
    *scn = (t_scene *)malloc(sizeof(t_scene));
    if (*scn == NULL)
        return (EXIT_FAILURE);
    ft_bzero(*scn, sizeof(t_scene));
    return (EXIT_SUCCESS);
}

void	object_array(t_rt *rt)
{
	t_dynarr arr;
	int initialSize = 5;
	int dataSize = sizeof(t_objs);

	if (!dynarr_create(&arr, initialSize, dataSize))
	{
		// return 1;
	}
	if (alloc_scene_struct(&rt->scene) == EXIT_FAILURE)
	{
		// return
	}
	
	camera_setup(rt, &rt->scene->camera);
	create_each_obj(&arr, rt, rt->scene);
}
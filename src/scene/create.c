#include <miniRT.h>
#include <scene.h>

void	assign_plane(t_objs *obj, t_vec3 v)
{
	obj->plane.direction = v;
}

void	assign_sphere(t_objs *obj, t_vec3 v)
{
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
	plane1.ray_direction = (t_vec3) {0.0, 0.0, -1.0};
	plane1.color = (t_vec3) {0.0, 0.5, 0.5, 1};

	t_vec3 direction = {0.0, 1.0, 0.7};
	obj_assign_table(&plane1, plane1.type, direction);
	dynarr_insert(arr, &plane1);

	t_objs sphere1;
	sphere1.type = SPHERE;
	sphere1.ray_direction = (t_vec3) {-1.0, 0.0, -1.0};
	sphere1.color = (t_vec3) {0.5, 0.0, 0.5, 1.0};

	t_vec3 radius = {10};
	obj_assign_table(&sphere1, sphere1.type, radius);
	dynarr_insert(arr, &sphere1);
}

void	sphere_behind_another_sphere(t_dynarr *arr, t_scene *scn)
{
	t_objs sphere1;
	sphere1.type = SPHERE;
	sphere1.ray_direction = (t_vec3) {0.0, 0.0, -5.0};
	sphere1.color = (t_vec3) {1.0, 0.0, 0.0, 1};

	t_vec3 radius = {10};
	obj_assign_table(&sphere1, sphere1.type, radius);
	dynarr_insert(arr, &sphere1);

	sphere1.ray_direction = (t_vec3) {0.0, 0.0, 5.0};
	sphere1.color = (t_vec3) {1.0, 1.0, 1.0, 1};

	t_vec3 radius2 = {10};
	obj_assign_table(&sphere1, sphere1.type, radius2);

	dynarr_insert(arr, &sphere1);
}

void	spheres_next_to_eachother(t_dynarr *arr, t_scene *scn)
{
	t_objs sphere1;
	sphere1.type = SPHERE;
	sphere1.ray_direction = (t_vec3) {-5.0, 0.0, -1.0};
	sphere1.color = (t_vec3) {1.0, 0.0, 0.0, 1};

	t_vec3 radius = {10};
	obj_assign_table(&sphere1, sphere1.type, radius);
	dynarr_insert(arr, &sphere1);

	sphere1.ray_direction = (t_vec3) {5.0, 0.0, -1.0};
	sphere1.color = (t_vec3) {1.0, 1.0, 1.0, 1};

	t_vec3 radius2 = {10};
	obj_assign_table(&sphere1, sphere1.type, radius2);

	dynarr_insert(arr, &sphere1);
}
void	create_each_obj(t_dynarr *arr, t_rt *rt, t_scene *scn)
{
	// plane_sphere(arr, scn);
	sphere_behind_another_sphere(arr,scn);
	// spheres_next_to_eachother(arr, scn);

	scn->objarr = arr->arr;
	scn->arr_size = arr->length;
}

void	camera_setup(t_rt *rt, t_objs *obj)
{
	// obj->camera.coords = (t_vec3){0.0, 0.0, -1.0};
	// obj->ray_direction = (t_vec3){0.0, 0.0, 55.0};
	obj->camera.coords = (t_vec3){-0.3, 0.0, -1.0};
	obj->ray_direction = (t_vec3){-55.0, 0.0, 55.0};
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

bool	scene_creation(t_rt *rt)
{
	t_dynarr arr;
	int initialSize = 5;
	int dataSize = sizeof(t_objs);

	if (dynarr_create(&arr, initialSize, dataSize) == false || \
		alloc_scene_struct(&rt->scene) == EXIT_FAILURE)
	{
		return (EXIT_FAILURE);
	}
	camera_setup(rt, &rt->scene->camera);
	create_each_obj(&arr, rt, rt->scene);
	return (EXIT_SUCCESS);
}
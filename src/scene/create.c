// #include <miniRT.h>
// #include <scene.h>

// void	assign_plane(t_objs *obj, t_vec4 v)
// {
// 	obj->plane.direction = v;
// }

// void	assign_sphere(t_objs *obj, t_vec4 v)
// {
// 	obj->sphere.radius = v[X];
// }

// void	obj_assign_table(t_objs *obj, t_obj_type type, t_vec4 v)
// {
// 	static void	(*assign_obj[NUM_OBJ_TYPES])(t_objs *, t_vec4) = {
// 		assign_plane,
// 		assign_sphere
// 	};

// 	assign_obj[type](obj, v);
// }

// void	plane_sphere(t_dynarr *arr, t_scene *scn)
// {
// 	t_objs plane1;
// 	plane1.type = PLANE;
// 	plane1.coords = (t_vec4) {0.0F, 0.0F, -1.0F};
// 	plane1.color = (t_vec4) {0.0F, 0.5F, 0.5F, 1.0F};

// 	t_vec4 direction = {0.0F, 0.5F, 0.1F};
// 	obj_assign_table(&plane1, plane1.type, direction);
// 	dynarr_insert(arr, &plane1);

// 	t_objs sphere1;
// 	sphere1.type = SPHERE;
// 	sphere1.coords = (t_vec4) {0.0F, 0.0F, -1.0F};
// 	sphere1.color = (t_vec4) {0.5F, 0.0F, 0.5F, 1.0F};

// 	t_vec4 radius = {10.0F};
// 	obj_assign_table(&sphere1, sphere1.type, radius);
// 	dynarr_insert(arr, &sphere1);

// 	scn->camera.coords = (t_vec4){0.0F, 0.0F, 55.0F};
// 	scn->camera.cam.orientation = (t_vec4){0.0F, 0.0F, 0.0F};
// 	scn->camera.cam.fov = 80.0F;
// }

// void	sphere_behind_another_sphere(t_dynarr *arr, t_scene *scn)
// {
// 	t_objs sphere1;
// 	sphere1.type = SPHERE;
// 	sphere1.coords = (t_vec4) {0.0F, 0.0F, -5.0F};
// 	sphere1.color = (t_vec4) {1.0F, 0.0F, 0.0F, 1.0F};

// 	t_vec4 radius = {10.0F};
// 	obj_assign_table(&sphere1, sphere1.type, radius);
// 	dynarr_insert(arr, &sphere1);

// 	sphere1.coords = (t_vec4) {0.0F, 0.0F, 5.0F};
// 	sphere1.color = (t_vec4) {1.0F, 1.0F, 1.0F, 1.0F};

// 	t_vec4 radius2 = {10.0F};
// 	obj_assign_table(&sphere1, sphere1.type, radius2);

// 	dynarr_insert(arr, &sphere1);

// 	// scn->camera.coords = (t_vec4){0.0F, 0.0F, 55.0F};
// 	// scn->camera.cam.orientation = (t_vec4){0.0F, 0.0F, -1.0F};
// 	scn->camera.coords = (t_vec4){-133.0F, 0.0F, 135.0F};
// 	scn->camera.cam.orientation = (t_vec4){2.0F, 0.0F, -1.0F};
// 	scn->camera.cam.fov = 80.0F;
// }

// void	spheres_next_to_eachother(t_dynarr *arr, t_scene *scn)
// {
// 	t_objs sphere1;
// 	sphere1.type = SPHERE;
// 	sphere1.coords = (t_vec4) {-5.0F, 0.0F, -1.0F};
// 	sphere1.color = (t_vec4) {1.0F, 0.0F, 0.0F, 1.0F};

// 	t_vec4 radius = {10.0F};
// 	obj_assign_table(&sphere1, sphere1.type, radius);
// 	dynarr_insert(arr, &sphere1);

// 	sphere1.coords = (t_vec4) {5.0F, 0.0F, -1.0F};
// 	sphere1.color = (t_vec4) {1.0F, 1.0F, 1.0F, 1.0F};

// 	t_vec4 radius2 = {10.0F};
// 	obj_assign_table(&sphere1, sphere1.type, radius2);

// 	dynarr_insert(arr, &sphere1);

// 	scn->camera.coords = (t_vec4){0.0F, 0.0F, 55.0F};
// 	scn->camera.cam.orientation = (t_vec4){0.0F, 0.0F, -1.0F};
// 	scn->camera.cam.fov = 80.0F;
// }

// void	cylinder(t_dynarr *arr, t_scene *scn)
// {
// 	t_objs cylinder;
// 	cylinder.type = CYLINDER;
// 	cylinder.coords = (t_vec4){0.0F, 0.0F, -1.0F};
// 	// cylinder.cylinder.direction = (t_vec4){0.0F, 1.0F, 0.0F};
// 	// cylinder.cylinder.direction = (t_vec4){0.0F, 0.0F, 0.75F};
// 	cylinder.cylinder.direction = (t_vec4){0.0F, 0.3F, 1.0F};
// 	cylinder.cylinder.radius = 10.0F;
// 	cylinder.cylinder.height = 20.0F;
// 	cylinder.color = (t_vec4){0.0F, 1.0F, 0.0F, 1.0F};

// 	dynarr_insert(arr, &cylinder);


// 	scn->camera.coords = (t_vec4){0.0F, 0.0F, 55.0F};
// 	scn->camera.cam.orientation = (t_vec4){0.0F, 0.0F, -1.0F};
// 	scn->camera.cam.fov = 80.0F;
// }

// void	create_each_obj(t_dynarr *arr, t_rt *rt, t_scene *scn)
// {
// 	// plane_sphere(arr, scn);
// 	// sphere_behind_another_sphere(arr, scn);
// 	// spheres_next_to_eachother(arr, scn);
// 	cylinder(arr,scn);

// 	scn->objarr = arr->arr;
// 	scn->arr_size = arr->length;
// }
// 	// obj->coords = (t_vec4){0.0F, 55.0F, 65.0F};
// 	// obj->camera.orientation = (t_vec4){0.0F, -0.9F, 0.0F};
// void	camera_setup(t_rt *rt, t_objs *obj)
// {
// 	// obj->coords = (t_vec4){0.0, 0.0, 55.0};
// 	// obj->camera.orientation = (t_vec4){0.0F, 0.0F, -1.0F};
// 	// // obj->coords = (t_vec4){-133.0F, 0.0F, 135.0F};
// 	// // obj->camera.orientation = (t_vec4){2.0F, 0.0F, -1.0F};
// 	// obj->camera.fov = 80.0F;
// }

// bool	alloc_scene_struct(t_scene **scn)
// {
// 	*scn = (t_scene *)malloc(sizeof(t_scene));
// 	if (*scn == NULL)
// 		return (EXIT_FAILURE);
// 	ft_bzero(*scn, sizeof(t_scene));
// 	return (EXIT_SUCCESS);
// }

// bool	scene_creation(t_rt *rt)
// {
// 	t_dynarr arr;
// 	size_t initialSize = 5;
// 	size_t dataSize = sizeof(t_objs);

// 	if (dynarr_create(&arr, initialSize, dataSize) == false || \
// 		alloc_scene_struct(&rt->scene) == EXIT_FAILURE)
// 	{
// 		return (EXIT_FAILURE);
// 	}
// 	camera_setup(rt, &rt->scene->camera);
// 	create_each_obj(&arr, rt, rt->scene);
// 	return (EXIT_SUCCESS);
// }
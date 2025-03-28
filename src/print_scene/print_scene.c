#include <miniRT.h>
#include <parsing.h>
#include <scene.h>
#include <RTmlx.h>
#include <utils.h>
#include <render.h>
#include <dbltoa.h>

#define NAME_FILE "Name your <new>.rt file\n"

#define	RT_MAX_LINE_LEN 150

t_dbltoa	setup_dbltoa_params(char *buff)
{
	t_dbltoa	params;

	params.value = 0;
	params.buff = buff;
	params.buff_size = MAX_DBL_BUFF;
	params.precision = 1;
	params.trim_trailing_zeros = false;
	return (params);
}

size_t	color_line(t_dbltoa *dbl, char *rt_line, t_vec4 color)
{
	size_t	line_index;

	dbl->value = color[R] * 255;
	dbl->precision = 0;
	dbltoa_buff_prec(*dbl);
	line_index = cpy_str(rt_line + line_index, dbl->buff);
	rt_line[line_index++] = ',';
	dbl->value = color[G] * 255;
	dbltoa_buff_prec(*dbl);
	line_index += cpy_str(rt_line + line_index, dbl->buff);
	rt_line[line_index++] = ',';
	dbl->value = color[B] * 255;
	dbltoa_buff_prec(*dbl);
	line_index += cpy_str(rt_line + line_index, dbl->buff);
	return (line_index);
}

size_t	coords_line(t_dbltoa *dbl, char *rt_line, t_vec4 coords)
{
	size_t	line_index;

	dbl->value = coords[X];
	dbl->precision = 1;
	dbl->trim_trailing_zeros = true;
	dbltoa_buff_prec(*dbl);
	line_index = cpy_str(rt_line + line_index, dbl->buff);
	rt_line[line_index++] = ',';
	dbl->value = coords[Y];
	dbltoa_buff_prec(*dbl);
	line_index += cpy_str(rt_line + line_index, dbl->buff);
	rt_line[line_index++] = ',';
	dbl->value = coords[Z];
	dbltoa_buff_prec(*dbl);
	line_index += cpy_str(rt_line + line_index, dbl->buff);
	line_index += cpy_str(rt_line + line_index, "\t\t");
	return (line_index);
}

void	ambient_line(t_objs *ambient, t_dbltoa *dbl, int fd)
{
	char	rt_line[RT_MAX_LINE_LEN];
	size_t	line_index;

	line_index = cpy_str(rt_line, "A\t");
	dbl->value = ambient->a.ratio;
	dbltoa_buff_prec(*dbl);
	line_index += cpy_str(rt_line + line_index, dbl->buff);
	line_index += cpy_str(rt_line + line_index, "\t\t");
	line_index += color_line(dbl, rt_line + line_index, ambient->color);
	ft_putendl_fd(rt_line, fd);
}

void	camera_line(t_objs *camera, t_dbltoa *dbl, int fd)
{
	char	rt_line[RT_MAX_LINE_LEN];
	size_t	line_index;

	line_index = cpy_str(rt_line, "C\t");
	line_index += coords_line(dbl, rt_line + line_index, camera->coords);
	line_index += coords_line(dbl, rt_line + line_index, camera->c.orientation);
	dbl->value = camera->c.fov;
	dbl->precision = 0;
	dbltoa_buff_prec(*dbl);
	cpy_str(rt_line + line_index, dbl->buff);
	ft_putendl_fd(rt_line, fd);
}

void	lights_line(t_objs *lights, size_t amount, t_dbltoa *dbl, int fd)
{
	char	rt_line[RT_MAX_LINE_LEN];
	size_t	line_index;
	size_t	i;

	i = 0;
	while (i < amount)
	{
		line_index = cpy_str(rt_line, "L\t");
		line_index += coords_line(dbl, rt_line + line_index, lights[i].coords);

		dbl->value = lights[i].l.brightness;
		dbl->precision = 1;
		dbltoa_buff_prec(*dbl);
		line_index += cpy_str(rt_line + line_index, dbl->buff);

		line_index += cpy_str(rt_line + line_index, "\t\t");


		line_index += color_line(dbl, rt_line + line_index, lights[i].color);
		ft_putendl_fd(rt_line, fd);
		++i;
	}
}

void	plane_line(t_objs *pl, t_dbltoa *dbl, int fd)
{
	char	rt_line[RT_MAX_LINE_LEN];
	size_t	line_index;

	line_index = cpy_str(rt_line, "pl\t");
	line_index += coords_line(dbl, rt_line + line_index, pl->coords);
	line_index += coords_line(dbl, rt_line + line_index, pl->plane.orientation);
	line_index += color_line(dbl, rt_line + line_index, pl->color);
	ft_putendl_fd(rt_line, fd);
}

void	sphere_line(t_objs *sp, t_dbltoa *dbl, int fd)
{
	char	rt_line[RT_MAX_LINE_LEN];
	size_t	line_index;

	line_index = cpy_str(rt_line, "sp\t");
	line_index += coords_line(dbl, rt_line + line_index, sp->coords);

	dbl->value = sp->sphere.diameter;
	dbltoa_buff_prec(*dbl);
	line_index += cpy_str(rt_line + line_index, dbl->buff);
	line_index += cpy_str(rt_line + line_index, "\t\t");
	line_index += color_line(dbl, rt_line + line_index, sp->color);
	ft_putendl_fd(rt_line, fd);
}

void	cylinder_line(t_objs *cy, t_dbltoa *dbl, int fd)
{
	char	rt_line[RT_MAX_LINE_LEN];
	size_t	line_index;

	line_index = cpy_str(rt_line, "cy\t");
	line_index += coords_line(dbl, rt_line + line_index, cy->coords);
	line_index += coords_line(dbl, rt_line + line_index, cy->cylinder.orientation);
	dbl->value = cy->cylinder.diameter;
	dbltoa_buff_prec(*dbl);
	line_index += cpy_str(rt_line + line_index, dbl->buff);
	line_index += cpy_str(rt_line + line_index, "\t\t");

	dbl->value = cy->cylinder.height;
	dbltoa_buff_prec(*dbl);
	line_index += cpy_str(rt_line + line_index, dbl->buff);
	line_index += cpy_str(rt_line + line_index, "\t\t");

	line_index += color_line(dbl, rt_line + line_index, cy->color);
	ft_putendl_fd(rt_line, fd);
}

void	objs_line(t_objs *objs, size_t amount, t_dbltoa *dbl, int fd)
{
	size_t	i;

	i = 0;
	while (i < amount)
	{
		if (objs[i].type == PLANE)
			plane_line(objs + i, dbl, fd);
		else if (objs[i].type == SPHERE)
			sphere_line(objs + i, dbl, fd);
		else if (objs[i].type == CYLINDER)
			cylinder_line(objs + i, dbl, fd);
		++i;
	}

}

void	create_scene_rt_file(t_scene *sc)
{
	char	filename[FILE_CREATION];
	int		fd;

	if (get_user_input(filename, FILE_CREATION, NAME_FILE) <= 0)
		return ;
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644); 
	if (fd == -1) {
		perror("create_scene_rt_file: Error opening file");
		return ;
	}

	char		dbltoa_buff[MAX_DBL_BUFF];
	t_dbltoa	dbl;

	dbl = setup_dbltoa_params(dbltoa_buff);

	ambient_line(&sc->ambient, &dbl, fd);
	camera_line(&sc->camera, &dbl, fd);
	lights_line(sc->lights, sc->l_arr_size, &dbl, fd);
	objs_line(sc->objs, sc->o_arr_size, &dbl, fd);

	close(fd);
// printf("camera: %f  %f  %f\n", sc->camera.coords[0], sc->camera.coords[1], sc->camera.coords[2]);
	puts("worked");
	exit(0);
}
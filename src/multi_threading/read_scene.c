#include <parsing.h>
#include <utils.h>
#include <RTmlx.h>

int16_t	init_read_scene(t_scene *src, t_scene *dest)
{
	ft_memcpy(dest, src, sizeof(t_scene));
	dest->objs = NULL;
	dest->lights = NULL;
	dest->objs = (t_objs *)malloc(src->o_arr_size * sizeof(t_objs));
	if (dest->objs == NULL)
		return (errset(errno));
	dest->lights = (t_objs *)malloc(src->l_arr_size * sizeof(t_objs));
	if (dest->lights == NULL)
		return (errset(errno));
	ft_memcpy(dest->objs, src->objs, sizeof(t_objs) * src->o_arr_size);
	ft_memcpy(dest->lights, src->lights, sizeof(t_objs) * src->l_arr_size);
	return (SUCCESS);
}

int16_t	cpy_scene(t_scene *src, t_scene *dest)
{
	const t_objs	*dest_obj = dest->objs;
	const t_objs	*dest_lights = dest->lights;

	ft_memcpy(dest, src, sizeof(t_scene));
	dest->objs = dest_obj;
	dest->lights = dest_lights;
	ft_memcpy(dest->objs, src->objs, sizeof(t_objs) * src->o_arr_size);
	ft_memcpy(dest->lights, src->lights, sizeof(t_objs) * src->l_arr_size);
	return (SUCCESS);
}

#include <parsing.h>

//	Static Functions
static bool	init_dynarr(t_scene *sc);
static bool	shrink_dynarr(t_scene *sc);

int16_t	parse_scene_file(const char *file, t_scene *sc)
{
	const int		fd = open(file, O_RDONLY);

	if (fd < 0)
		return (errset(perr("input_parse", errno)));					//wrong comment?
	if (ft_strncmp(file + (ft_strlen(file) - 3), ".rt", 4) != 0)
		return (close(fd), errset(perr("input_parse", ERRFEXT)));		//wrong comment?
	if (init_dynarr(sc) == false)
		return (close(fd), errset(perr("parse_scene_file", ENOMEM)));
	if (line_validation(fd, sc) != 0)
		return (close(fd), errset(ERTRN));
	if (shrink_dynarr(sc) == false)
		return (close(fd), errset(perr("parse_scene_file", ENOMEM)));
	sc->objs = (t_objs *)dynarr_take_arr(&sc->obj_dynarr);
	sc->lights = (t_objs *)dynarr_take_arr(&sc->light_dynarr);
	close(fd);
	return (errset(ERTRN));
}

static bool	init_dynarr(t_scene *sc)
{
	if (dynarr_create(&sc->obj_dynarr, 5, sizeof(t_objs)) == false)
		return (false);
	if (dynarr_create(&sc->light_dynarr, 5, sizeof(t_objs)) == false)
		return (false);
	return (true);
}

static bool	shrink_dynarr(t_scene *sc)
{
	if (dynarr_shrink_to_fit(&sc->obj_dynarr) == false)
		return (false);
	if (dynarr_shrink_to_fit(&sc->light_dynarr) == false)
		return (false);
	return (true);
}



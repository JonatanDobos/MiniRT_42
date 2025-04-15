#ifndef PARSING_H
# define PARSING_H
# include <common_defs.h>
# include <libft.h>
# include <scene.h>
# include <miniRT.h>
# include <fcntl.h>
# include <RTerror.h>

typedef struct s_parsing_value_check
{
	uint16_t	cam_amount;
	uint16_t	amb_amount;
	uint16_t	obj_amount;
	t_dynarr	obj_dynarr;
	t_dynarr	light_dynarr;
}	t_value_check;

// parsing.c

int16_t		parse_scene_file(const char *file, t_scene *sc);

//	line_validation
int16_t		line_validation(const int fd, t_scene *sc, t_value_check *vc);
bool		check_line(char *line, const char prefix, uint8_t nbr_of_groups);

//	initialize_input_element
bool		input_type_parse(t_scene *sc, t_value_check *vc, char *line);
bool		init_primitives(t_scene *sc, t_value_check *vc, char *line);

// parse_utils.c
float		rt_atof(const char *str);
char		*nxtv(char *str);
char		*nxtvp(char **str);

//trash
void		_print_parsing(t_scene *sc);
#endif

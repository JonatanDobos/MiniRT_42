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
	uint16_t		cam_amount;
	uint16_t		light_amount;
	uint16_t		amb_amount;
	uint16_t		obj_amount;
}	t_value_check;

// parsing.c

int16_t		read_inp_file(const char *file, t_scene *sc);

// line_validation
int16_t		line_validation(char *line);
bool		check_line(char *line, const char prefix, uint8_t nbr_of_groups);

// parse_peripherals.c

int16_t		parse_amb(t_scene *sc, t_value_check *vc, char *line);
int16_t		parse_cam(t_scene *sc, t_value_check *vc, char *line);
int16_t		parse_light(t_scene *sc, t_value_check *vc, char *line);

// parse_objects.c

int16_t		parse_pl(t_scene *sc, t_value_check *vc, char *line);
int16_t		parse_sp(t_scene *sc, t_value_check *vc, char *line);
int16_t		parse_cy(t_scene *sc, t_value_check *vc, char *line);

// parsing_utils.c

void		*memappend(void **ptr, void *append, size_t size, size_t len);
float		range(float value, float min, float max);

// string_utils.c

float		rt_atof(const char *str);
int32_t		rt_atoi(const char *str);
char		*nxtv(char *str);
char		*nxtvp(char **str);



//trash
void		_print_parsing(t_scene *sc);
#endif
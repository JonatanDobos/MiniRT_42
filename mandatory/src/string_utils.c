#include "../include/minirt_param.h"

float	rt_atof(const char *str)
{
	float	num;
	int		i;
	int		sign;
	int		place;

	num = 0;
	i = 0;
	sign = 1;
	while (!ft_isdigit(str[i]))
		++i;
	if (i > 0 && str[i] == '-')
		sign = -1;
	while (str[i] && ft_isdigit(str[i]))
		num = (num * 10) + (str[i++] - '0');
	if (str[i] != '.')
		return (num * sign);
	++i;
	place = 1;
	while (str[i] && ft_isdigit(str[i]))
		num += (float)(str[i++] - '0') / pow(10, (float)(place++));
	return (num * sign);
}

t_int	rt_atoi(const char *str)
{
	int		sign;
	t_int	num;
	size_t	i;

	sign = 1;
	num = 0;
	i = 0;
	while (!ft_isdigit(str[i]))
		++i;
	if (i > 0 && str[i - 1] == '-')
		sign = -1;
	while (ft_isdigit(str[i]))
		num = (num * 10) + (str[i++] - '0');
	return (sign * num);
}

/**
 * @brief Skips till it encounters a new numerical value.
 * @param str Ptr in string to skip from.
 * @return char* to the first character of the next value in str,
 * or \0 if it encountered no whitespace.
 * @note If the given *str is pointing to a value (digit, period or minus),
 * it will also skip that until it finds the next separate value.
 */
char	*nxtvalue(char *str)
{
	while (*str && !ft_iswhitespace(*str) && *str != ',')
		++str;
	while (*str && *str != '.' && *str != '-' && !ft_isdigit(*str))
		++str;
	return (str);
}
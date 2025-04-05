#include <parsing.h>
#include <math.h>

/**
 * @brief Skips till it encounters a new numerical value.
 * @param str Ptr in string to skip from.
 * @return char* to the first character of the next value in str,
 * or \0 if it encountered no whitespace.
 * @note If the given *str is pointing to a value (digit, period or minus),
 * it will also skip that until it finds the next separate value.
 */
char	*nxtv(char *str)
{
	while (*str != '\0' && ft_isspace(*str) == false && *str != ',')
		++str;
	while (*str != '\0' && *str != '.' && *str != '-' && \
	ft_isdigit(*str) == false)
		++str;
	return (str);
}

/**
 * @brief Skips till it encounters a new numerical value.
 * @param str Address of ptr in string to skip from.
 * @return char* to the first character of the next value in str,
 * or \0 if it encountered no whitespace.
 * @note If the given *str is pointing to a value (digit, period or minus),
 * it will also skip that until it finds the next separate value.
 * @note Also changes the original ptr given under the address **str!
 */
char	*nxtvp(char **str)
{
	char	*c;

	c = *str;
	while (*c != '\0' && !ft_isspace(*c) && *c != ',')
		++c;
	while (*c != '\0' && *c != '.' && *c != '-' && ft_isdigit(*c) == false)
		++c;
	*str = c;
	return (c);
}

float	rt_atof(const char *str)
{
	float	num;
	int		i;
	int		sign;
	int		place;

	num = 0.0F;
	i = 0;
	sign = 1;
	while (ft_isdigit(str[i]) == false || str[i] == '.')
		++i;
	if (i > 0 && str[i - 1] == '-')
		sign = -1;
	while (str[i] != '\0' && ft_isdigit(str[i]) == true)
		num = (num * 10.0F) + (str[i++] - '0');
	if (str[i] != '.')
		return (num * sign);
	++i;
	place = 1;
	while (str[i] != '\0' && ft_isdigit(str[i]) == true)
		num += (float)(str[i++] - '0') / pow(10, (float)(place++));
	return (num * sign);
}

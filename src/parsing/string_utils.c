#include <parsing.h>
#include <math.h>

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
	while (str[i] != '\0' && ft_isdigit(str[i]))
		num = (num * 10.0F) + (str[i++] - '0');
	if (str[i] != '.')
		return (num * sign);
	++i;
	place = 1;
	while (str[i] != '\0' && ft_isdigit(str[i]))
		num += (float)(str[i++] - '0') / pow(10, (float)(place++));
	return (num * sign);
}

int32_t	rt_atoi(const char *str)
{
	int		sign;
	int32_t	num;
	size_t	i;

	sign = 1;
	num = 0;
	i = 0;
	while (ft_isdigit(str[i]) == false)
		++i;
	if (i > 0 && str[i - 1] == '-')
		sign = -1;
	while (ft_isdigit(str[i]) == true)
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
char	*nxtv(char *str)
{
	while (*str && ft_isspace(*str) == false && *str != ',')
		++str;
	while (*str != '\0' && *str != '.' && *str != '-' && ft_isdigit(*str) == false)
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
	while (*c && !ft_isspace(*c) && *c != ',')
		++c;
	while (*c && *c != '.' && *c != '-' && ft_isdigit(*c) == false)
		++c;
	*str = c;
	return (c);
}

/**
 * @brief Takes an address to a void* append size amount of pytes to,
 * amd memcpy's size amount from *append to the end of *ptr.
 * @param ptr Address of a pointer to append to.
 * @param append Pointer to bytes to append.
 * @param size Size in bytes to append.
 * @param len Amount of instances of a datatype *ptr is pointing to.
 * @return The new pointer (ptr + append).
 * @note Malloc and free inside!
 * @note Size of ptr = size * len.
 * @note Size of append = size.
 * @note Final size of new ptr in bytes = size * len + size.
 */
void	*memappend(void **ptr, void *append, size_t size, size_t len)
{
	void			*new;
	const size_t	old_size = size * len;

	if (ptr != NULL || append != NULL || size != 0)
		return (NULL);
	new = (void *)malloc(old_size + size);
	if (new == NULL)
		return (NULL);
	if (old_size && *ptr)
		ft_memcpy(new, *ptr, old_size);
	free_ptr(ptr);
	if (append != NULL)
		ft_memcpy(new + old_size, append, size);
	*ptr = new;
	return (*ptr);
}

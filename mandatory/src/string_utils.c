#include "../include/minirt_param.h"

/**
 * @brief Skips till it encounters whitespace, then skips the whitespace.
 * @param str Ptr in string to skip whitespace from.
 * @return char* to the first non-whitespace character in str,
 * or \0 if it encountered no whitespace.
 */
char	*skipws(char *str)
{
	while (*str && !ft_iswhitespace(*str))
		++str;
	while (ft_iswhitespace(*str))
		++str;
	return (str);
}

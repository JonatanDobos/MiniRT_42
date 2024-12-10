/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: joni <joni@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/03 15:14:17 by joni          #+#    #+#                 */
/*   Updated: 2024/12/03 15:14:36 by joni          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static size_t	nl_len(char *str)
{
	size_t	i;

	i = 0;
	if (str)
	{
		while (str[i] && (i == 0 || str[i - 1] != '\n'))
			i++;
		return (i);
	}
	return (0);
}

static size_t	nl_check(char *str)
{
	while (str && *str)
	{
		if (*str == '\n')
			return (1);
		str++;
	}
	return (0);
}

static char	*get_buf(char *buf, char *line, size_t i, size_t j)
{
	const size_t	l_len = nl_len(line);
	const size_t	b_len = nl_len(buf);
	char			*new_line;
	char			*temp_line;

	if (b_len == 0)
		return (line);
	temp_line = line;
	new_line = (char *)malloc(l_len + b_len + 1);
	if (!new_line)
		return (ft_free(&line), NULL);
	while (i < l_len)
		new_line[i++] = *(temp_line++);
	while (j < b_len)
		new_line[i++] = buf[j++];
	new_line[i] = '\0';
	ft_free(&line);
	i = 0;
	while (buf[j])
		buf[i++] = buf[j++];
	buf[i] = '\0';
	return (new_line);
}

// Modified: returns "\0" on EOF instead of NULL
char	*get_next_line(int fd)
{
	static char	buffer[GNL_BUFFER_SIZE + 1];
	ssize_t		bytesread;
	char		*line;

	line = (char *)malloc(sizeof(char));
	if (!line)
		return (NULL);
	line[0] = '\0';
	line = get_buf(buffer, line, 0, 0);
	if (nl_check(line) != 0 || line == NULL)
		return (line);
	bytesread = GNL_BUFFER_SIZE;
	while (line && nl_check(line) == 0 && bytesread == GNL_BUFFER_SIZE)
	{
		bytesread = read(fd, buffer, GNL_BUFFER_SIZE);
		if (bytesread < 0)
			return (ft_free(&line), NULL);
		buffer[bytesread] = '\0';
		line = get_buf(buffer, line, 0, 0);
	}
	return (line);
}

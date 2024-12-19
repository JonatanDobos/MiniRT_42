#include "../include/minirt_param.h"

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
void	*vappend(void **ptr, void *append, size_t size, size_t len)
{
	void	*new;
	const size_t	ptr_size = size * len;

	if (!ptr || !append || !size)
		return (NULL);
	new = (void *)malloc(ptr_size + size);
	if (new == NULL)
		return (NULL);
	if (ptr_size && *ptr)
		ft_memcpy(new, *ptr, size);
	ft_free(ptr);
	if (append)
		ft_memcpy(new + ptr_size, append, size);
	*ptr = new;
	return (*ptr);
}

t_short	parse_pl(t_scene *sc, t_value_check *vc, char *line)
{
	(void)sc;
	(void)vc;
	(void)line;
	return (SUCCESS);
}

t_short	parse_sp(t_scene *sc, t_value_check *vc, char *line)
{
	t_sphere	sp;

	// LEFTOFF fill in sp
	if (!vappend(&sc->sphere, &sp, sizeof(t_sphere), sc->sphere_count))
		return (errset(perr("parse_sp", errno)));
	return (SUCCESS);
}

t_short	parse_cy(t_scene *sc, t_value_check *vc, char *line)
{
	(void)sc;
	(void)vc;
	(void)line;
	return (SUCCESS);
}

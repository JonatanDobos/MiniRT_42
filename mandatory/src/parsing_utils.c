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
void	*memappend(void **ptr, void *append, size_t size, size_t len)
{
	void			*new;
	const size_t	old_size = size * len;

	if (!ptr || !append || !size)
		return (NULL);
	new = (void *)malloc(old_size + size);
	if (new == NULL)
		return (NULL);
	if (old_size && *ptr)
		ft_memcpy(new, *ptr, old_size);
	ft_vfree(ptr);
	if (append)
		ft_memcpy(new + old_size, append, size);
	*ptr = new;
	return (*ptr);
}

double	range(double value, double min, double max)
{
	if (value > max)
		return (max);
	if (value < min)
		return (min);
	return (value);
}

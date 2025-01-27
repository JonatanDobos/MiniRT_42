/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mac_malloc_wrapper.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/26 02:10:48 by rjw           #+#    #+#                 */
/*   Updated: 2025/01/27 14:10:37 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <wrap_functions.h>
// #include <stdio.h>
// #include <stdlib.h>

#if defined(__APPLE__) && defined(__MACH__)
#  ifdef MALLOC_WRAP
#   if MALLOC_WRAP == true

static void	*creating_real_malloc(void)
{
	void	*handle;

	handle = dlopen_handler();
	if (handle == NULL)
	{
		return (NULL);
	}
	return (dlsym_handler(handle, "malloc"));
}

void	*malloc(size_t size)
{
	static void	*(*real_malloc)(size_t) = NULL;

	if (real_malloc == NULL)
	{
		real_malloc = creating_real_malloc();
		if (real_malloc == NULL)
		{
			return (real_malloc);
		}
	}
	if (malloc_toggle(RETRIEVE_MALLOC) == OG_MALLOC_DISABLED && \
		malloc_handler(size, NULL, NULL) == false)
	{
		return (NULL);
	}
	return (real_malloc(size));
}
#  endif
# endif
#endif

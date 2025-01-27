/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dynamic_symbols.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/27 03:03:08 by rjw           #+#    #+#                 */
/*   Updated: 2025/01/27 03:39:26 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <wrap_functions.h>
#include <stdio.h>
#include <errno.h>

//	Static Function
static void	**handle_fixed(void);

void	*dlopen_handler(void)
{
	void	**handle;
	char	*error;

	handle = handle_fixed();
	*handle = dlopen("libSystem.B.dylib", RTLD_LAZY);
	if (*handle == NULL) 
	{
		error = dlerror();
		if (error != NULL) {
			fprintf(stderr, "dlopen error: %s\n", error);
		}
		errno = ENOENT;
	}
	return (*handle);
}

void	*dlsym_handler(void *handle, const char *function_name)
{
	void	*real_malloc;
	char	*error;

	real_malloc = dlsym(handle, function_name);
	if (real_malloc == NULL) {
		error = dlerror();
		if (error != NULL) {
			fprintf(stderr, "dlsym Error: %s\n", error);
			errno = EINVAL;
		}
	}
	return (real_malloc);
}

int	handle_close(void)
{
	void	**handle;
	int		dlcose_ret;
	char	*error;

	handle = handle_fixed();
	if (*handle == NULL)
	{
		fprintf(stderr, "Error: handle is NULL\n");
		errno = EINVAL;
		return (-1);
	}
	dlcose_ret = dlclose(*handle);
	if (dlcose_ret != 0)
	{
		error = dlerror();
		if (error != NULL) {
			fprintf(stderr, "dlclose rror: %s\n", error);
		}
		errno = EINVAL;
	}
	return (dlcose_ret);
}

static void	**handle_fixed(void)
{
	static void	*handle = NULL;

	return (&handle);
}

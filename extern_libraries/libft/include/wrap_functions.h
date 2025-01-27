/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   wrap_functions.h                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/25 02:01:03 by rjw           #+#    #+#                 */
/*   Updated: 2025/01/27 03:34:17 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_WRAPPER_H
# define MALLOC_WRAPPER_H
# define _GNU_SOURCE
# include <stdbool.h>
# include <stddef.h>
# include <dlfcn.h>

# define OG_MALLOC_ENABLED true
# define OG_MALLOC_DISABLED false
# define RETRIEVE_MALLOC true
# define SET_MALLOC false

void	*dlopen_handler(void);
void	*dlsym_handler(void *handle, const char *function_name);
int		handle_close(void);

/**
 * For `Linux`, the same description applies as for the malloc function below.
 * To compile with the malloc wrapper, use the following command:
 * gcc -I -Wl,--wrap=malloc main.c libft.a
 * 2 flags at the end.
 * 
 * Note: The -Wl,--wrap=malloc flag tells the linker to replace calls to malloc
 * with calls to __wrap_malloc, allowing custom behavior for memory allocation.   
*/
void	*__wrap_malloc(size_t size);
void	*__real_malloc(size_t size);

/**
 * @brief Custom malloc function that allows for custom behavior.
 * 
 * @attention If the custom function decides to fail, set errno = ENOMEM.
 * @attention don't use optimization flags like -Ofast or -03
 * This function wraps the standard malloc function and allows for custom 
 * behavior to be executed before the actual memory allocation.
 * If a custom function is set using malloc_handler,
 * it will be called before the actual allocation.
 * The custom function can decide whether to proceed with the allocation or not.
 * 
 * @param[in] size The size of the memory allocation.
 * 
 * @return A pointer to the allocated memory, or NULL if the allocation fails.
*/
void	*malloc(size_t size);

/**
 * @brief malloc_handler - A wrapper function for custom malloc behavior.
 * @attention If the custom function decides to fail, set errno = ENOMEM.
 * @attention don't use optimization flags like -Ofast or -03
 * 
 * @param[in] size The size of the memory allocation.
 * @param[in] ptr: Pointer to custom struct used in the custom function.
 * @param[in] custom: A custom function to handle malloc behavior.
 * 
 * @return A pointer to the allocated memory, or NULL if the allocation fails.
 * 
 * This function allows you to set a custom malloc function that can be used
 * to handle memory allocation. The custom function should have the following
 * signature:
 * 
 * bool custom_malloc_func(size_t size, void *ptr);
 * 
 * Example usage:
 * 
 * typedef struct	set_limit{
 *      int max_malloc_usage = 3;
 * }	t_set_limit;
 * 
 * bool my_custom_malloc(size_t size, void *ptr)
 * {
 *     t_set_limit limit = (t_set_limit)ptr
 *     if (limit->max_malloc_usage != 0) {
 *         errno = ENOMEM;
 *         return (false);
 *     }
 *     limit->max_malloc_usage--;
 *     return (true);
 * }
 * 
 * malloc_handler(0, &my_struct, my_custom_malloc);
*/
bool	malloc_handler(size_t size, void *ptr, bool (*custom)(size_t, void *));

/**
 * @param[in] check Indicates whether to retrieve or set the malloc behavior.
 * Use the defines `RETRIEVE_MALLOC` to retrieve the current malloc setting,
 * or `SET_MALLOC` to set a new behavior.
 * This allows custom malloc to either use standard malloc or custom functions.
*/
bool	malloc_toggle(bool check);
#endif
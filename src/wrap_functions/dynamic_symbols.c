/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dynamic_symbols.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/27 03:03:08 by rjw           #+#    #+#                 */
/*   Updated: 2025/02/24 17:46:19 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <wrap_functions.h>
#include <stdio.h>
#include <errno.h>
#include <libft.h>


// void	*wrap_your_func(void **handle, const char *function_name)
void	*wrap_your_func(const char *function_name)
{
	void	*wrapped_function;

	// dlopen_handler(handle);
	// if (*handle == NULL)
	// {
	// 	return (NULL);
	// }
	// (void)handle;
	// wrapped_function = dlsym_handler(*handle, function_name);
	wrapped_function = dlsym_handler(RTLD_NEXT, function_name);
	if (wrapped_function == NULL)
	{
		// handle_close(handle);
		return (NULL);
	}
	return (wrapped_function);
}

#if defined(__APPLE__) && defined(__MACH__)
const char	*os_file(void)
{
	return ("libSystem.B.dylib");
}
#endif

#if defined(__linux__)
const char	*os_file(void)
{
	return ("libc.so.6");
}
#endif

void	dlopen_handler(void **handle)
{
	char	*error;
// ft_putendl_fd("first",1);
// sleep(1);
	// malloc_toggle(SET_MALLOC);
	*handle = dlopen(os_file(), RTLD_LAZY);
	// malloc_toggle(SET_MALLOC);
	// *handle = dlopen("libc.so.6", RTLD_LAZY);
// ft_putendl_fd("second",1);
	if (*handle == NULL) 
	{
		error = dlerror();
		if (error != NULL) {
			// fprintf(stderr, "dlopen error: %s\n", error);
			ft_putendl_fd("dlopen error: ", 2);

		}
		errno = ENOENT;
	}
}

void	*dlsym_handler(void *handle, const char *function_name)
{
	void	*real_malloc;
	char	*error;
// (void)handle;
	real_malloc = dlsym(handle, function_name);
	// real_malloc = dlsym(RTLD_NEXT, function_name);
	if (real_malloc == NULL) {
		error = dlerror();
		if (error != NULL) {
			// fprintf(stderr, "dlsym Error: %s\n", error);
			ft_putendl_fd("dlsym Error: ", 2);
			errno = EINVAL;
		}
	}
	// else
	// 	ft_putendl_fd("dlsym didn't return NULL??",1);
	return (real_malloc);
}

int	handle_close(void **handle)
{
	int		dlcose_ret;
	char	*error;

	if (handle == NULL || *handle == NULL)
	{
		// fprintf(stderr, "Error: handle is NULL\n");
		ft_putendl_fd("dlsym Error: ", 2);
		errno = EINVAL;
		return (-1);
	}
	dlcose_ret = dlclose(*handle);
	if (dlcose_ret != 0)
	{
		error = dlerror();
		if (error != NULL) {
			// fprintf(stderr, "dlclose error: %s\n", error);
			ft_putendl_fd("dlsym Error: ", 2);
		}
		errno = EINVAL;
	}
	else
	{
		*handle = NULL;
	}
	return (dlcose_ret);
}

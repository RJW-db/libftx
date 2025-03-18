/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dynamic_symbols.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/27 03:03:08 by rjw           #+#    #+#                 */
/*   Updated: 2025/03/17 19:55:26 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <wrap_functions.h>
#include <stdio.h>
#include <errno.h>
#include <libft.h>

void	*dlsym_handler(void *handle, const char *function_name)
{
	void	*real_malloc;
	char	*error;

	real_malloc = dlsym(handle, function_name);
	if (real_malloc == NULL)
	{
		error = dlerror();
		if (error != NULL)
		{
			ft_putendl_fd("dlsym Error: ", 2);
			errno = EINVAL;
		}
	}
	return (real_malloc);
}

int	handle_close(void **handle)
{
	int		dlcose_return;
	char	*error;

	if (handle == NULL || *handle == NULL)
	{
		ft_putendl_fd("dlsym Error: ", 2);
		errno = EINVAL;
		return (-1);
	}
	dlcose_return = dlclose(*handle);
	if (dlcose_return != 0)
	{
		error = dlerror();
		if (error != NULL)
			ft_putendl_fd("dlsym Error: ", 2);
		errno = EINVAL;
	}
	else
		*handle = NULL;
	return (dlcose_return);
}

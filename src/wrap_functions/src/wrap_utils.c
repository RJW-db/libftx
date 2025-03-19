/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   wrap_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/27 03:03:08 by rjw           #+#    #+#                 */
/*   Updated: 2025/03/19 03:10:17 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <wrap_functions.h>

void	*dlsym_handler(void *handle, const char *function_name)
{
	void	*real_malloc;
	char	*error;

	real_malloc = dlsym(handle, function_name);
	if (real_malloc == NULL)
	{
		wrap_error_handling("dlsym Error");
		error = dlerror();
		if (error != NULL)
		{
			wrap_error_handling(error);
			errno = EINVAL;
		}
	}
	return (real_malloc);
}

bool	general_handler(void *ptr, bool (*custom)(void *))
{
	static bool	(*func)(void *) = NULL;

	if (func != NULL)
	{
		if (func(NULL) == true)
		{
			return (true);
		}
		func = NULL;
		return (false);
	}
	else if (func == NULL && custom != NULL && ptr != NULL)
	{
		func = custom;
		func(ptr);
		return (true);
	}
	return (false);
}

bool	general_toggle(bool check)
{
	static bool	switch_malloc = true;

	if (check == true)
	{
		return (switch_malloc);
	}
	else if (check == false)
	{
		switch_malloc = !switch_malloc;
	}
	return (switch_malloc);
}

void	wrap_error_handling(const char *str)
{
	char	destination[ERR_HANDLING_BUFFER];
	size_t	i;

	i = 0;
	while (*str != '\0')
	{
		destination[i] = *str;
		++str;
		if (i == (ERR_HANDLING_BUFFER - 1))
		{
			if (write(STDERR_FILENO, destination, ERR_HANDLING_BUFFER) == -1)
			{
				perror("wrap_error_handling: write");
				return ;
			}
			i = 0;
			continue ;
		}
		++i;
	}
	destination[i] = '\n';
	if (write(STDERR_FILENO, destination, i + 1) == -1)
		perror("wrap_error_handling: write");
}

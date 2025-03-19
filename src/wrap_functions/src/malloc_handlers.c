/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   malloc_handlers.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/25 02:13:59 by rjw           #+#    #+#                 */
/*   Updated: 2025/03/19 02:49:28 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <wrap_functions.h>

bool	malloc_handler(size_t size, void *ptr, bool (*custom)(size_t, void *))
{
	static bool	(*func)(size_t, void *) = NULL;

	if (func != NULL)
	{
		if (func(size, NULL) == true)
		{
			return (true);
		}
		errno = ENOMEM;
		func = NULL;
		return (false);
	}
	else if (func == NULL && custom != NULL && ptr != NULL)
	{
		func = custom;
		func(size, ptr);
		return (true);
	}
	errno = EINVAL;
	return (false);
}

bool	malloc_toggle(bool check)
{
	static bool	switch_malloc = true;

	if (check == RETRIEVE_MALLOC)
	{
		return (switch_malloc);
	}
	else if (check == SET_MALLOC)
	{
		switch_malloc = !switch_malloc;
	}
	return (switch_malloc);
}

void	reset_malloc_state(size_t *malloc_attempts)
{
	*malloc_attempts = 0;
	if (malloc(0) == NULL)
	{
		errno = 0;
	}
}

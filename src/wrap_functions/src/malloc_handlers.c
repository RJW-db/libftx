/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   malloc_handlers.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/25 02:13:59 by rjw           #+#    #+#                 */
/*   Updated: 2025/03/17 20:12:12 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <wrap_functions.h>
// #include <libft.h>
#include <errno.h>

/**
 * 	An int main() example at the bottom.
*/
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

void	reset_static_pointers_and_errno(size_t *malloc_attempts)
{
	*malloc_attempts = 0;
	if (malloc(0) == NULL)
	{
		errno = 0;
	}
}

// bool	set_malloc_amount(size_t size, void *ptr)
// {
// 	static	int limit = -1;
// 	write(1, "cust\n", 5);
// 	if (limit > 0)
// 	{
// 		--limit;
// 	}
// 	else if (limit == 0)
// 	{
// 		write(1, "SHOULDN'T never get here using existing functions, "
// 				"use malloc_toggle()\n", 71);
// 		errno = ENOMEM;
// 		return (false);
// 	}
// 	else if (limit == -1) {
// 		limit = *((int *)ptr);
// 		write(1, "klop\n", 5);
// 	}
// 	return (true);
// }

// int main(void)
// {
// 	int nbr = 0;
// 	// sleep(5);
// 	malloc_handler(0, &nbr, set_malloc_amount);
// 	malloc_toggle(0); // Toggle is necessary to let printf use original malloc
// 	// printf("Use malloc_toggle() to use original malloc with this printf\n");
// 	char *str = malloc(5);
// 	free(str);
// 	if (errno == ENOMEM)
// 		write(1, "errno\n", 6);
// 	write(1, "end\n", 4);
// 	return 0;
// }

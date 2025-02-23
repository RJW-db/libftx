/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mac_malloc_wrapper.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/26 02:10:48 by rjw           #+#    #+#                 */
/*   Updated: 2025/02/23 19:41:35 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <wrap_functions.h>
// #include <stdio.h>
// #include <stdlib.h>
#include <libft.h>
#if defined(__APPLE__)
# if defined(__MACH__)
#  ifdef MALLOC_WRAP
#   if MALLOC_WRAP == true

void	**get_handle(void)
{
	static void	*handle = NULL;
	
	return (&handle);
}

// void	*malloc(size_t size)
// {
// 	static void	*(*real_malloc)(size_t) = NULL;

// 	if (real_malloc == NULL)
// 	{
// 		// real_malloc = creating_real_malloc(get_handle());
// 		real_malloc = wrap_your_func(get_handle(), "malloc");
// 		ft_putendl_fd("voorbij",1);
// 		if (real_malloc == NULL)
// 		{
// 			return (real_malloc);
// 		}
// 	}
// 	ft_putendl_fd("malloc twoo",1);
	
// 	if (malloc_toggle(RETRIEVE_MALLOC) == OG_MALLOC_ENABLED)
// 	{
// 		return (real_malloc(size));

// 	} else if (malloc_handler(size, NULL, NULL) == false)
// 	{
// 		handle_close(get_handle());
// 		return (NULL);
// 	}
// 	return (real_malloc(size));
// }

/** malloc can work for linux without valgrind, with valgrind it uses the original malloc.
 * Thus __wrap_malloc is used for linux.
 */

void	*malloc(size_t size)
{
	static void	*(*real_malloc)(size_t) = NULL;
// ft_putendl_fd("entering malloc",1);

	if (real_malloc == NULL)
	{
		// ft_putendl_fd("not here",1);
		// real_malloc = wrap_your_func("malloc");
		real_malloc = dlsym_handler(RTLD_NEXT, "malloc");
			// ft_putendl_fd("real_malloc = wrap_your_func failed",1);
		if (real_malloc == NULL)
		{
			// ft_putendl_fd("setting dlsym didn't work", 1);

			return (NULL);
		}
		// ft_putendl_fd("voorbij",1);
	}
	// ft_putendl_fd("malloc twoo",1);
	
	if (malloc_toggle(RETRIEVE_MALLOC) == OG_MALLOC_ENABLED)
	{
		// ft_putendl_fd("real malloc being used", 1);
		if (real_malloc == NULL) {
			// ft_putendl_fd("should return NULL", 1);
			return (NULL);
		}
		// ft_putendl_fd("or here", 1);
		return (real_malloc(size));

	} else if (malloc_handler(size, NULL, NULL) == false)
	{
		// ft_putendl_fd("FAILURE", 1);
		real_malloc = NULL;
		return (NULL);
	}
	
	// if () check if handle isnot NULL; errno -1?
	// ft_putendl_fd("passed ptr function, now mallocing", 1);
	return (real_malloc(size));
}


#   endif
#  endif
# endif
#endif

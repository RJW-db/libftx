/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   linux_malloc_wrapper.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/25 22:04:13 by rjw           #+#    #+#                 */
/*   Updated: 2025/02/23 19:42:54 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <wrap_functions.h>
#if defined(__linux__)
# ifdef MALLOC_WRAP
#  if MALLOC_WRAP == true

void	*__wrap_malloc(size_t size)
{
	if (malloc_toggle(RETRIEVE_MALLOC) == OG_MALLOC_ENABLED)
	{
		return (__real_malloc(size));
	}
	else if (malloc_handler(size, NULL, NULL) == false)
	{
		return (NULL);
	}
	return (__real_malloc(size));
}
#  endif
# endif
#endif

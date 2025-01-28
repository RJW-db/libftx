/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   realloc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 20:40:20 by rjw           #+#    #+#                 */
/*   Updated: 2025/01/11 02:46:52 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <sys/param.h>
#include <libft.h>

/*
	Used functions:
	- free_ptr
	-	free
	- malloc
	- ft_memmove
	
	don't return on the same pointer, if malloc fails the old malloced
	pointer will be overwritten with NULL and unable to free the old.
*/
void	*ft_realloc(void **ptr, t_csize_t new_size, t_csize_t old_size)
{
	void	*new;

	if (new_size == 0 && ptr != NULL)
	{
		free_ptr(ptr);
		return (NULL);
	}
	new = malloc(new_size);
	if (new == NULL)
		return (NULL);
	if (ptr != NULL && *ptr != NULL)
	{
		ft_memmove(new, *ptr, MIN(new_size, old_size));
		free_ptr(ptr);
	}
	return (new);
}

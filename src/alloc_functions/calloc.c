/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   calloc.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 20:41:07 by rjw           #+#    #+#                 */
/*   Updated: 2024/09/11 20:41:07 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/*
	nmemb = amount to malloc + 1 for the terminator '\0'
	size = sizeof(char *)

	Used functions:
	- malloc
	- ft_memset
*/
void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	t;
	void	*ptr;

	t = nmemb * size;
	if (nmemb != 0 && size != 0 && t / nmemb != size)
		return (NULL);
	ptr = malloc(t);
	if (ptr == NULL)
		return (NULL);
	ft_memset(ptr, 0, t);
	return (ptr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mem_search.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 20:32:41 by rjw           #+#    #+#                 */
/*   Updated: 2025/01/19 03:39:45 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (n--)
		if (((t_uchr *)s)[i++] == (t_uchr)c)
			return ((void *)(s + --i));
	return (NULL);
}

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	while (n--)
	{
		if (*(t_uchr *)s1 != *(t_uchr *)s2)
			return (*(t_uchr *)s1 - *(t_uchr *)s2);
		++s1;
		++s2;
	}
	return (0);
}

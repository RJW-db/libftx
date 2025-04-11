/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mem_search.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 20:32:41 by rjw           #+#    #+#                 */
/*   Updated: 2025/04/11 02:24:18 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*s_uchar = s;
	size_t				i;

	i = 0;
	while (n != 0)
	{
		if (s_uchar[i++] == c)
			return ((void *)(s_uchar + --i));
		--n;
	}
	return (NULL);
}

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*s1_uchar = s1;
	const unsigned char	*s2_uchar = s2;

	while (n != 0)
	{
		if (*s1_uchar != *s2_uchar)
			return (*s1_uchar - *s2_uchar);
		++s1_uchar;
		++s2_uchar;
		--n;
	}
	return (0);
}

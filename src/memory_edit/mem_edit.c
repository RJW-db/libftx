/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mem_edit.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 20:32:47 by rjw           #+#    #+#                 */
/*   Updated: 2025/01/19 03:41:31 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/*
	Used functions:
	- ft_memset
*/
void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	t_uchr	*tmp_dest;
	t_cuchr	*tmp_src;
	
	if (!dest && !src)
		return (NULL);
	tmp_dest = (t_uchr *)dest;
	tmp_src = (t_cuchr *)src;
	while (n--)
		*tmp_dest++ = *tmp_src++;
	return (dest);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*tmp;

	tmp = dest;
	if (src > dest)
		while (n--)
			*(char *)tmp++ = *(char *)src++;
	if (dest > src)
		while (n--)
			*((char *)dest + n) = *((char *)src + n);
	return (dest);
}

void	*ft_memset(void *b, int c, size_t len)
{
	t_uchr	*charb;

	charb = b;
	while (len--)
		*charb++ = (t_uchr)c;
	return (b);
}

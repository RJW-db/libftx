/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/12 01:39:19 by rjw           #+#    #+#                 */
/*   Updated: 2025/03/12 01:39:23 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/dbltoa.h"

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

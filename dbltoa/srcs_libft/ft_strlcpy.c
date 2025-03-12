/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/12 01:40:00 by rjw           #+#    #+#                 */
/*   Updated: 2025/03/12 03:32:56 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/dbltoa.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t i;
	size_t len;

	i = 0;
	len = 0;
	if (src == NULL)
		return (0);
	while (src[len])
		len++;
	if (dstsize == 0)
		return (len);
	while (i < (dstsize - 1) && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (len);
}


char *ft_strdup(const char *str)
{
	size_t len = ft_strlen(str);
	char *copy = (char *)malloc(len + 1);
	for (size_t i = 0; i < len; i++)
		copy[i] = str[i];
	copy[len] = '\0';
	return copy;
}
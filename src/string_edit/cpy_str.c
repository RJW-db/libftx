/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cpy_str.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 20:31:00 by rjw           #+#    #+#                 */
/*   Updated: 2025/05/09 15:16:18 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libftx.h>

size_t	cpy_str(char *dst, const char *src)
{
	size_t	i;
	char	c;

	i = 0;
	c = src[i];
	while (c != '\0')
	{
		dst[i] = c;
		++i;
		c = src[i];
	}
	return (i);
}

size_t	cpy_str0(char *dst, const char *src)
{
	size_t	i;
	char	c;

	i = 0;
	c = src[i];
	while (c != '\0')
	{
		dst[i] = c;
		++i;
		c = src[i];
	}
	dst[i] = '\0';
	return (i);
}

size_t	cpy_srcs(char *dst, const char *s1, const char *s2, const char *s3)
{
	size_t	i;

	i = cpy_str(dst, s1);
	i += cpy_str(&dst[i], s2);
	i += cpy_str0(&dst[i], s3);
	return (i);
}

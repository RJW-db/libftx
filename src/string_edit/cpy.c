/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cpy.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 20:31:00 by rjw           #+#    #+#                 */
/*   Updated: 2025/01/08 17:44:16 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

size_t	cpy_str(char *dst, t_cchr *src)
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

/**
	Used functions:
	- cpy_str
*/
size_t	cpy_srcs(char *dst, t_cchr *s1, t_cchr *s2, t_cchr *s3)
{
	size_t	i;

	i = cpy_str(dst, s1);
	i += cpy_str(&dst[i], s2);
	i += cpy_str(&dst[i], s3);
	dst[i] = '\0';
	return (i);
}

size_t	cpy_num(char *dst, t_cchr *src, size_t num)
{
	size_t	i;
	char	c;

	i = 0;
	c = src[i];
	while (c != '\0' && num > 0)
	{
		dst[i] = c;
		--num;
		++i;
		c = src[i];
	}
	dst[i] = '\0';
	return (i);
}

/**
 * Memset but returns size_t
*/
size_t	cpy_num_char(char *dst, t_cchr c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		dst[i] = c;
		++i;
	}
	dst[i] = '\0';
	return (i);
}

size_t	cpy_till_char(char *dst, t_cchr *src, t_cchr chr)
{
	size_t	i;
	char	c;

	i = 0;
	c = src[i];
	while (c != '\0' && c != chr)
	{
		dst[i] = c;
		++i;
		c = src[i];
	}
	dst[i] = '\0';
	return (i);
}

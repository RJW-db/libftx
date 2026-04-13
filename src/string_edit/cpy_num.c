/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cpy_num.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 20:30:57 by rjw           #+#    #+#                 */
/*   Updated: 2025/05/09 15:31:33 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libftx.h>

size_t	cpy_num(char *dst, const char *src, size_t num)
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
size_t	cpy_num_char(char *dst, const char c, size_t n)
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

size_t	cpy_till_char(char *dst, const char *src, const char chr)
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

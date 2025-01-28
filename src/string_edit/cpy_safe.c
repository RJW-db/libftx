/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cpy_safe.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 20:30:57 by rjw           #+#    #+#                 */
/*   Updated: 2025/01/08 17:44:16 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/**
	Used functions:
	- cpy_str

 * _s = safe
*/
size_t	cpy_str_s(char *dst, t_cchr *src)
{
	if (strs_ok(dst, src) == false)
		return (0);
	return (cpy_str(dst, src));
}

/**
	Used functions:
	- cpy_str

 * _s = safe
*/
size_t	cpy_srcs_s(char *dst, t_cchr *s1, t_cchr *s2, t_cchr *s3)
{
	size_t	i;

	if (strs_ok(dst, s1) == false)
		return (0);
	i = cpy_str(dst, s1);
	if (s2 == NULL)
	{
		dst[i] = '\0';
		return (i);
	}
	i += cpy_str(&dst[i], s2);
	if (s3 == NULL)
	{
		dst[i] = '\0';
		return (i);
	}
	i += cpy_str(&dst[i], s3);
	dst[i] = '\0';
	return (i);
}

/**
 * _s = safe
*/
size_t	cpy_num_s(char *dst, t_cchr *src, size_t num)
{
	size_t	i;

	if (strs_ok(dst, src) == false)
		return (0);
	i = 0;
	while (src[i] != '\0' && num > 0)
	{
		dst[i] = src[i];
		++i;
		--num;
	}
	dst[i] = '\0';
	return (i);
}

/**
 * _s = safe
*/
size_t	cpy_till_char_s(char *dst, t_cchr *src, t_cchr chr)
{
	size_t	i;
	char	c;

	if (strs_ok(dst, src) == false)
		return (0);
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

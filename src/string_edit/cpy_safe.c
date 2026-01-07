/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cpy_safe.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 20:30:57 by rjw           #+#    #+#                 */
/*   Updated: 2025/05/09 15:31:33 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libftx.h>

size_t	cpy_str_s(char *dst, const char *src)
{
	if (strs_ok(dst, src) == false)
		return (0);
	return (cpy_str0(dst, src));
}

size_t	cpy_srcs_s(char *dst, const char *s1, const char *s2, const char *s3)
{
	size_t	i;

	if (dst == NULL)
		return (0);
	i = 0;
	if (s1 != NULL)
		i = cpy_str(dst, s1);
	if (s2 != NULL)
		i += cpy_str(dst + i, s2);
	if (s3 != NULL)
		i += cpy_str(dst + i, s3);
	dst[i] = '\0';
	return (i);
}

size_t	cpy_num_s(char *dst, const char *src, size_t num)
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

size_t	cpy_till_char_s(char *dst, const char *src, const char chr)
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

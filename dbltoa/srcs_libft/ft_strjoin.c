/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/12 01:39:54 by rjw           #+#    #+#                 */
/*   Updated: 2025/03/12 15:00:33 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/dbltoa.h"
#include <stdlib.h>

bool	strs_ok(const char *s1, const char *s2)
{
	return (!(s1 == NULL || s2 == NULL));
}

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
	dst[i] = '\0';
	return (i);
}

size_t	cpy_str_s(char *dst, const char *src)
{
	if (strs_ok(dst, src) == false)
		return (0);
	return (cpy_str(dst, src));
}

size_t	cpy_srcs_s(char *dst, const char *s1, const char *s2, const char *s3)
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

char	*strjoin_safe(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	index;

	ptr = malloc(sizeof(char) * (strlen_safe(s1) + strlen_safe(s2) + 1));
	if (ptr == NULL)
		return (NULL);
	index = cpy_str_s(ptr, s1);
	index = cpy_str_s(ptr + index, s2);
	if (s1 == NULL && s2 == NULL)
		ptr[0] = '\0';
	return (ptr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/12 01:39:48 by rjw           #+#    #+#                 */
/*   Updated: 2025/03/12 03:32:51 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/dbltoa.h"
#include <stdlib.h>

char	*ft_strchr(const char *s, int c)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)s + i);
	return (NULL);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n--)
	{
		if (*s1 != *s2) {
			return (*(unsigned char *)s1 - *(unsigned char *)s2);
		}
		if (*s1 == '\0') {
			return (0);
		}
		++s1;
		++s2;
	}
	return (0);
}

size_t	find_char_not(const char *str, const char c1)
{
	char	*tmp_str;

	tmp_str = (char *)str;
	while (*tmp_str != '\0' && *tmp_str == c1)
	{
		++tmp_str;
	}
	if (*tmp_str != c1)
	{
		return (tmp_str - str);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   str_compare.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 20:30:16 by rjw           #+#    #+#                 */
/*   Updated: 2025/01/19 03:39:45 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_strcmp(t_cchr *s1, t_cchr *s2)
{
	while (*s1 != '\0' && *s2 != '\0')
	{
		if (*s1 != *s2)
			return (*(t_uchr *)s1 - *(t_uchr *)s2);
		++s1;
		++s2;
	}
	return (0);
}

int	ft_strncmp(t_cchr *s1, t_cchr *s2, size_t n)
{
	while (n--)
	{
		if (*s1 != *s2)
			return (*(t_uchr *)s1 - *(t_uchr *)s2);
		if (*s1 == '\0')
			return (0);
		++s1;
		++s2;
	}
	return (0);
}

int	strncmp_safe(t_cchr *s1, t_cchr *s2, size_t n)
{
	if (strs_ok(s1, s2) == false)
		return (0);
	while (n--)
	{
		if (*s1 != *s2)
			return (*(t_uchr *)s1 - *(t_uchr *)s2);
		if (*s1 == '\0')
			return (0);
		++s1;
		++s2;
	}
	return (0);
}

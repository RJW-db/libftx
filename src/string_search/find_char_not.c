/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_char_not.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 20:30:39 by rjw           #+#    #+#                 */
/*   Updated: 2025/01/08 17:44:16 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/**
 * Return index of the last occurences of set.
 * Using char c vs derefencing was very slightly faster with testing.
 */
size_t	find_set_not(t_cchr *str, char *set)
{
	char	*tmp_str;
	char	c;

	tmp_str = (char *)str;
	c = *tmp_str;
	while (c != '\0' && ft_strchr(set, c) != NULL)
	{
		++tmp_str;
		c = *tmp_str;
	}
	if (ft_strchr(set, c) == NULL)
		return (tmp_str - str);
	return (0);
}

/**
 * Return index of the last occurence of c1.
 * Using char c vs derefencing was very slightly faster with testing.
 */
size_t	find_char_not(t_cchr *str, t_cchr c1)
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

/**
 * Return index of the last occurence of c1, c2.
 * Using char c vs derefencing was quite a bit faster with testing.
 */
size_t	find_char2_not(t_cchr *str, t_cchr c1, t_cchr c2)
{
	char	*tmp_str;
	char	c;

	tmp_str = (char *)str;
	c = *tmp_str;
	while (c != '\0' && (c == c1 || c == c2))
	{
		++tmp_str;
		c = *tmp_str;
	}
	if (c != c1 && c != c2)
		return (tmp_str - str);
	return (0);
}

/**
 * Return index of the last occurence of c1, c2, c3.
 * Using char c vs derefencing was quite a bit faster with testing.
 */
size_t	find_char3_not(t_cchr *str, t_cchr c1, t_cchr c2, t_cchr c3)
{
	char	*tmp_str;
	char	c;

	tmp_str = (char *)str;
	c = *tmp_str;
	while (c != '\0' && (c == c1 || c == c2 || c == c3))
	{
		++tmp_str;
		c = *tmp_str;
	}
	if (c != c1 && c != c2 && c != c3)
		return (tmp_str - str);
	return (0);
}

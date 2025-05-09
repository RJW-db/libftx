/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   str_search_2.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 20:29:46 by rjw           #+#    #+#                 */
/*   Updated: 2025/05/09 15:16:18 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/*
	true  if c is    in str
	false if c isn't in str
*/
bool	c_in_str(int32_t c, const char *str)
{
	while (*str != '\0')
	{
		if (*str == c)
			return (true);
		++str;
	}
	return (false);
}

/*
	true  if str is    equal to set_order
	false if str isn't equal to set_order
*/
bool	strcmp0(const char *str, const char *set_order)
{
	while (*str != '\0' && *set_order != '\0')
		if (*str++ != *set_order++)
			return (false);
	return (true);
}

/*
	string len match, amount of characters that overlap in both strings.
*/
size_t	strlmatch(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			break ;
		++i;
	}
	return (i);
}

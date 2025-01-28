/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   str_search.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-brui <rde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/15 16:27:10 by rde-brui      #+#    #+#                 */
/*   Updated: 2025/01/15 16:27:12 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strchr(t_cchr *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		++i;
	}
	if ((char)c == '\0')
		return ((char *)s + i);
	return (NULL);
}

char	*ft_strnstr(t_cchr *big, t_cchr *little, size_t len)
{
	size_t		i;

	if (len == 0 && *little)
		return (NULL);
	if (!*little)
		return ((char *)big);
	while (*big && len > 0)
	{
		i = 0;
		while (big[i] == little[i] && big[i] && little[i] && len - i)
			++i;
		if (little[i] == '\0')
			return ((char *)big);
		++big;
		--len;
	}
	return (NULL);
}

/*
	Used functions:
	- ft_strlen
*/
char	*ft_strrchr(t_cchr *s, int c)
{
	size_t	i;

	i = ft_strlen(s);
	while (i > 0)
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		--i;
	}
	if (s[i] == (char)c || (char)c == 0)
		return ((char *)s + i);
	return (NULL);
}

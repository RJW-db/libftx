/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   strtrim.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 20:31:16 by rjw           #+#    #+#                 */
/*   Updated: 2025/01/08 17:44:16 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/*
	Used functions:
	- malloc
	- ft_strlen
	- ft_strlcpy
*/
char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*ptr;

	if (strs_ok(s1, set) == false)
		return (NULL);
	start = 0;
	while (s1[start] && c_in_str(s1[start], set) == 1)
		++start;
	end = ft_strlen(s1);
	while (end > start && c_in_str(s1[end - 1], set) == 1)
		--end;
	ptr = (char *)malloc((end - start + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	ft_strlcpy(ptr, s1 + start, end - start + 1);
	return (ptr);
}

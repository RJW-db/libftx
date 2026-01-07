/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   str_len_comparing.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 20:30:12 by rjw           #+#    #+#                 */
/*   Updated: 2025/05/09 15:16:18 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libftx.h>

char	*smallest_str(char *s1, char *s2)
{
	if (ft_strlen(s1) <= ft_strlen(s2))
		return (s1);
	return (s2);
}

char	*biggest_str(char *s1, char *s2)
{
	if (ft_strlen(s1) >= ft_strlen(s2))
		return (s1);
	return (s2);
}

size_t	smallest_str_len(const char *s1, const char *s2)
{
	size_t	s1_len;
	size_t	s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if (s1_len <= s2_len)
		return (s1_len);
	return (s2_len);
}

size_t	biggest_str_len(const char *s1, const char *s2)
{
	size_t	s1_len;
	size_t	s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if (s1_len >= s2_len)
		return (s1_len);
	return (s2_len);
}

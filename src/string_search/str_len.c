/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   str_len.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 20:30:04 by rjw           #+#    #+#                 */
/*   Updated: 2025/05/09 15:16:18 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libftx.h>

size_t	ft_strlen(const char *str)
{
	const char	*tmp = str;

	while (*tmp != '\0')
		++tmp;
	return ((size_t)(tmp - str));
}

size_t	strlen_safe(const char *str)
{
	size_t	n;

	if (str == NULL)
		return (0);
	n = 0;
	while (str[n] != '\0')
		++n;
	return (n);
}

size_t	strlen_chr(const char *str, const char chr)
{
	size_t	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i] != '\0' && str[i] != chr)
		++i;
	if (str[i] == '\0')
		return (0);
	return (i);
}

size_t	strlen_set(const char *str, const char *set)
{
	size_t	i;

	if (strs_ok(str, set) == false)
		return (0);
	i = 0;
	while (str[i] != '\0' && ft_strchr(set, str[i]) == NULL)
		++i;
	if (str[i] == '\0')
		return (0);
	return (i);
}

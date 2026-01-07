/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   str_dup.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 20:31:39 by rjw           #+#    #+#                 */
/*   Updated: 2025/05/09 15:16:18 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libftx.h>

char	*ft_strdup(const char *s)
{
	char	*str;
	size_t	len;

	len = ft_strlen(s);
	str = (char *)malloc((len + 1) * sizeof(char));
	if (str != NULL)
		cpy_str0(str, s);
	return (str);
}

char	*strdup_safe(const char *s)
{
	if (s != NULL)
		return (ft_strdup(s));
	return (NULL);
}

char	*strdup_len(const char *s, size_t size)
{
	char	*str;
	size_t	len;

	if (s == NULL || size == 0)
		return (NULL);
	len = ft_strlen(s);
	if (size < len)
		len = size;
	str = (char *)malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, s, len + 1);
	return (str);
}

char	*strdup_len_free(char **s, size_t size)
{
	char	*str;
	size_t	len;

	if (dpstr_ok(s) == false || size == 0)
		return (free_str(s));
	len = ft_strlen(*s);
	if (size < len)
		len = size;
	str = (char *)malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (free_str(s));
	ft_strlcpy(str, *s, len + 1);
	free_str(s);
	return (str);
}

char	*strdup_size_free(char **s, size_t size)
{
	char	*str;
	size_t	len;

	if (dpstr_ok(s) == false || size == 0)
		return (NULL);
	len = ft_strlen(*s);
	if (size < len)
		len = size;
	str = (char *)malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, *s, len + 1);
	free_str(s);
	return (str);
}

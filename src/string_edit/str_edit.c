/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   str_edit.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 20:30:54 by rjw           #+#    #+#                 */
/*   Updated: 2025/01/08 17:44:16 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_striteri(char *s, void (*f)(uint32_t, char*))
{
	uint32_t	i;

	if (!s || !f)
		return ;
	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		++i;
	}
}

/*
	Used functions:
	- ft_strlen
	- ft_strlcpy
*/
size_t	ft_strlcat(char *dst, t_cchr *src, size_t size)
{
	size_t	dst_len;

	dst_len = ft_strlen(dst);
	if (dst_len > size)
		return (ft_strlen(src) + size);
	return (dst_len + ft_strlcpy(dst + dst_len, src, size - dst_len));
}

/**
 * Copies *src to *dst and terminates it with '\0'.
*/
size_t	ft_strlcpy(char *dst, t_cchr *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
	{
		while (src[i])
			++i;
		return (i);
	}
	while (i < size - 1 && src[i] != '\0')
	{
		dst[i] = src[i];
		++i;
	}
	if (i < size)
		dst[i] = '\0';
	while (src[i] != '\0')
		++i;
	return (i);
}

/*
	Used functions:
	- malloc
	- ft_strlen
*/
char	*ft_strmapi(char const *s, char (*f)(uint32_t, char))
{
	uint32_t	i;
	char		*ptr;

	if (!s || !f)
		return (NULL);
	ptr = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		ptr[i] = f(i, s[i]);
		++i;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*charmove(char *dest, const char *src, size_t n)
{
	char	*tmp;

	tmp = dest;
	if (src > dest)
		while (n--)
			*tmp++ = *src++;
	else if (dest > src)
		while (n--)
			*(dest + n) = *(src + n);
	return (dest);
}

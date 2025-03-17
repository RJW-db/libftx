/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   str_edit.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 20:30:54 by rjw           #+#    #+#                 */
/*   Updated: 2025/03/17 19:49:25 by rde-brui      ########   odam.nl         */
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

void	extract_substr(const char *s, uint32_t start, size_t ln, char *buf)
{
	size_t	s_len;
	size_t	i;

	if (s == NULL || buf == NULL)
		return ;
	s_len = ft_strlen(s);
	if (s_len <= start)
		ln = 0;
	else if ((s_len - start) < ln)
		ln = s_len - start;
	i = 0;
	while (i < ln && s[start + i])
	{
		buf[i] = s[start + i];
		++i;
	}
	buf[i] = '\0';
}

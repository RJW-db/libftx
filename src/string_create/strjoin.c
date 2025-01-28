/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   strjoin.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 20:31:21 by rjw           #+#    #+#                 */
/*   Updated: 2025/01/08 17:44:16 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/*
	Used functions:
	- malloc
	- strs0_ok
	-	str0_ok
	- ft_strlen
*/
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	len;

	if (strs_ok(s1, s2) == false)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	ptr = malloc((len + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	cpy_srcs_s(ptr, s1, s2, NULL);
	return (ptr);
}

/*
	Used functions:
	- malloc
	- str0_ok
	- ft_strlen
	- free
*/
char	*strjoin_free_s1(char *s1, t_cchr *s2)
{
	char	*ptr;
	char	*tmp;
	size_t	len;

	if (s2 == false)
		return (free(s1), NULL);
	tmp = s1;
	len = 0;
	if (tmp != NULL)
		len = ft_strlen(tmp);
	len += ft_strlen(s2);
	ptr = malloc((len + 1) * sizeof(char));
	if (ptr == NULL)
		return (free(s1), NULL);
	if (tmp != NULL)
		while (*tmp)
			*(ptr++) = *(tmp++);
	while (*s2)
		*(ptr++) = *(s2++);
	*ptr = '\0';
	if (s1 != NULL)
		free(s1);
	return (ptr - len);
}

/*
	Used functions:
	- malloc
	- str0_ok
	- ft_strlen
	- free
*/
char	*strjoin_free_s2(t_cchr *s1, char *s2)
{
	char	*ptr;
	char	*tmp;
	size_t	len;

	if (s1 == false)
		return (free(s2), NULL);
	tmp = s2;
	len = 0;
	if (tmp != NULL)
		len = ft_strlen(tmp);
	len += ft_strlen(s1);
	ptr = malloc((len + 1) * sizeof(char));
	if (ptr == NULL)
		return (free(s2), NULL);
	while (*s1)
		*(ptr++) = *(s1++);
	if (tmp != NULL)
		while (*tmp)
			*(ptr++) = *(tmp++);
	*ptr = '\0';
	if (s1 != NULL)
		free(s2);
	return (ptr - len);
}

/*
	Used functions:
	- malloc
	- strs0_ok
	-	str0_ok
	- ft_strlen
*/
char	*strjoin_free_all(char *s1, char *s2)
{
	char	*ptr;
	char	*tmp;
	size_t	len;

	if (strs_ok(s1, s2) == false)
		return (free(s1), free(s2), NULL);
	len = ft_strlen(s1);
	len += ft_strlen(s2);
	ptr = malloc((len + 1) * sizeof(char));
	if (ptr == NULL)
		return (free(s1), free(s2), NULL);
	tmp = s1;
	while (*tmp)
		*(ptr++) = *(tmp++);
	tmp = s2;
	while (*tmp)
		*(ptr++) = *(tmp++);
	*ptr = '\0';
	free(s1);
	free(s2);
	return (ptr - len);
}

char	*strjoin_parts(char const *s1, char const *s2, size_t s2_len)
{
	char	*ptr;
	size_t	len;

	if (strs_ok(s1, s2) == false || s2_len == 0)
		return (NULL);
	len = ft_strlen(s1) + s2_len;
	ptr = malloc((len + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	while (*s1)
		*(ptr++) = *(s1++);
	while (*s2 && s2_len-- != 0)
		*(ptr++) = *(s2++);
	*ptr = '\0';
	return (ptr - len);
}

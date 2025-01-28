/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   strjoin_set_null.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 20:31:25 by rjw           #+#    #+#                 */
/*   Updated: 2025/01/11 21:34:50 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/*
	Used functions:
	- malloc
	- str0_ok
	- ft_strlen
	- free_str
	-	free
*/
char	*strjoin_free_s1_n(char **s1, t_cchr *s2)
{
	char	*ptr;
	char	*tmp;
	size_t	len;

	if (str0_ok(s2) == false)
		return (free_str(s1));
	len = 0;
	if (dpstr_ok(s1) == false)
		len = ft_strlen(*s1);
	len += ft_strlen(s2);
	ptr = malloc((len + 1) * sizeof(char));
	if (ptr == NULL)
		return (free_str(s1));
	tmp = NULL;
	if (s1 != NULL)
		tmp = *s1;
	if (tmp != NULL)
		while (*tmp)
			*(ptr++) = *(tmp++);
	while (*s2)
		*(ptr++) = *(s2++);
	*ptr = '\0';
	if (s1 != NULL && *s1 != NULL)
		free_str(s1);
	return (ptr - len);
}

/*
	Used functions:
	- malloc
	- str0_ok
	- ft_strlen
	- free_str
	-	free
*/
char	*strjoin_free_s2_n(t_cchr *s1, char **s2)
{
	char	*ptr;
	char	*tmp;
	size_t	len;

	if (str0_ok(s1) == false)
		return (free_str(s2));
	len = 0;
	if (dpstr_ok(s2) == false)
		len = ft_strlen(*s2);
	len += ft_strlen(s1);
	ptr = malloc((len + 1) * sizeof(char));
	if (ptr == NULL)
		return (free_str(s2));
	while (*s1)
		*(ptr++) = *(s1++);
	tmp = NULL;
	if (s2 != NULL)
		tmp = *s2;
	if (tmp != NULL)
		while (*tmp)
			*(ptr++) = *(tmp++);
	*ptr = '\0';
	if (s2 != NULL && *s2 != NULL)
		free_str(s2);
	return (ptr - len);
}

/*
	Used functions:
	- malloc
	- strs0_ok
	-	dpstr0_ok
	- ft_strlen
	- free_str
	-	free
*/
char	*strjoin_free_all_n(char **s1, char **s2)
{
	char	*ptr;
	char	*tmp;
	size_t	len;

	if (dpstrs0_ok((t_cchr **)s1, (t_cchr **)s2) == false)
		return (free_str(s1), free_str(s2));
	tmp = *s1;
	len = ft_strlen(tmp);
	len += ft_strlen(*s2);
	ptr = malloc((len + 1) * sizeof(char));
	if (ptr == NULL)
		return (free_str(s1), free_str(s2));
	while (*tmp)
		*(ptr++) = *(tmp++);
	tmp = *s2;
	while (*tmp)
		*(ptr++) = *(tmp++);
	*ptr = '\0';
	free_str(s1);
	free_str(s2);
	return (ptr - len);
}

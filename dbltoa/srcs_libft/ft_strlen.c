/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlen.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/12 01:40:05 by rjw           #+#    #+#                 */
/*   Updated: 2025/03/12 03:32:59 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/dbltoa.h"

size_t	ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t	strlen_safe(const char *str)
{
	size_t	n;

	if (str == NULL)
		return (0);
	n = 0;
	while (str[n])
		++n;
	return (n);
}
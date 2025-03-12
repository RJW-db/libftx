/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/12 01:38:37 by rjw           #+#    #+#                 */
/*   Updated: 2025/03/12 01:38:39 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/dbltoa.h"

int64_t	atoi64(const char *nptr)
{
	int64_t	i;
	int8_t	flag;

	if (*nptr == '\0')
		return (0);
	i = 0;
	flag = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		++nptr;
	if (*nptr == '-' || *nptr == '+')
		if (*nptr++ == '-')
			flag *= -1;
	while (*nptr >= '0' && *nptr <= '9')
		i = i * 10 + (*nptr++ - '0');
	return (i * flag);
}


void ft_bzero(void *str, size_t size_n)
{
    unsigned char *p = (unsigned char *)str;
    for (size_t i = 0; i < size_n; i++)
        p[i] = 0;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   str_to_number.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 20:38:08 by rjw           #+#    #+#                 */
/*   Updated: 2025/01/11 20:57:01 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/*
	For all functions the MIN of all of them overflower, e.g.
	2147483648 overflows to -2147483648, because INT_MAX = 2147483647

	and it overflows again when "i * flag",
	-2147483648 * -1 = 2147483648, but it's bigger than INT_MAX,
	so it overflows back to -2147483648.
*/
int32_t	atoi32(t_cchr *nptr)
{
	int32_t	i;
	int8_t	flag;

	i = 0;
	flag = 1;
	if (*nptr == '\0')
		return (0);
	while (ft_isspace(*nptr) == 1)
		++nptr;
	if (*nptr == '-' || *nptr == '+')
		if (*nptr++ == '-')
			flag *= -1;
	while (*nptr >= '0' && *nptr <= '9')
		i = i * 10 + (*nptr++ - '0');
	return (i * flag);
}

int64_t	atoi64(t_cchr *nptr)
{
	int64_t	i;
	int8_t	flag;

	if (*nptr == '\0')
		return (0);
	i = 0;
	flag = 1;
	while (ft_isspace(*nptr) == 1)
		++nptr;
	if (*nptr == '-' || *nptr == '+')
		if (*nptr++ == '-')
			flag *= -1;
	while (*nptr >= '0' && *nptr <= '9')
		i = i * 10 + (*nptr++ - '0');
	return (i * flag);
}

uint32_t	atui32(t_cchr *nptr)
{
	uint32_t	i;
	int8_t		flag;

	if (*nptr == '\0')
		return (0);
	i = 0;
	flag = 1;
	while (ft_isspace(*nptr) == 1)
		nptr++;
	if (*nptr == '-' || *nptr == '+')
		if (*nptr++ == '-')
			flag *= -1;
	while (*nptr >= '0' && *nptr <= '9')
		i = i * 10 + (*nptr++ - '0');
	return (i * flag);
}

uint64_t	atui64(t_cchr *nptr)
{
	uint64_t	i;
	int8_t		flag;

	if (*nptr == '\0')
		return (0);
	i = 0;
	flag = 1;
	while (ft_isspace(*nptr) == 1)
		nptr++;
	if (*nptr == '-' || *nptr == '+')
		if (*nptr++ == '-')
			flag *= -1;
	while (*nptr >= '0' && *nptr <= '9')
		i = i * 10 + (*nptr++ - '0');
	return (i * flag);
}

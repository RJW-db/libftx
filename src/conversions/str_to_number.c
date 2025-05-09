/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   str_to_number.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 20:38:08 by rjw           #+#    #+#                 */
/*   Updated: 2025/05/09 15:16:18 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/*
	For all functions the MIN of all of them overflower, e.g.
	2147483648 overflows to -2147483648, because INT_MAX = 2147483647

	and it overflows again when "result * flag",
	-2147483648 * -1 = 2147483648, but it's bigger than INT_MAX,
	so it overflows back to -2147483648.
*/
int32_t	atoi32(const char *nptr)
{
	int32_t	result;
	int8_t	flag;

	result = 0;
	flag = 1;
	if (*nptr == '\0')
		return (0);
	while (ft_isspace(*nptr) == 1)
		++nptr;
	if (*nptr == '-' || *nptr == '+')
		if (*nptr++ == '-')
			flag *= -1;
	while (*nptr >= '0' && *nptr <= '9')
		result = result * 10 + (*nptr++ - '0');
	return (result * flag);
}

int64_t	atoi64(const char *nptr)
{
	int64_t	result;
	int8_t	flag;

	if (*nptr == '\0')
		return (0);
	result = 0;
	flag = 1;
	while (ft_isspace(*nptr) == 1)
		++nptr;
	if (*nptr == '-' || *nptr == '+')
		if (*nptr++ == '-')
			flag *= -1;
	while (*nptr >= '0' && *nptr <= '9')
		result = result * 10 + (*nptr++ - '0');
	return (result * flag);
}

uint64_t	atui64(const char *nptr)
{
	uint64_t	result;

	if (*nptr == '\0')
		return (0);
	result = 0;
	while (ft_isspace(*nptr) == true)
		++nptr;
	if (*nptr == '-')
		return (0);
	if (*nptr == '+')
		++nptr;
	while (*nptr >= '0' && *nptr <= '9')
		result = result * 10 + (uint64_t)(*nptr++ - '0');
	return (result);
}

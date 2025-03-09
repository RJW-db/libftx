/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   itoa.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 20:31:43 by rjw           #+#    #+#                 */
/*   Updated: 2025/03/09 03:32:08 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdio.h>
#define DECIMAL_BASE "0123456789"

/*
	Used functions:
	- ft_strdup
	- malloc
	- ft_strdup
*/
char	*ft_itoa(int n)
{
	uint8_t	len;
	bool	sign;
	char	*dst;

	sign = (n < 0);
	len = digit_counter(n, 10);
	dst = malloc((len + TERM) * sizeof(char));
	if (dst == NULL)
		return (NULL);
	if (sign == true)
		dst[0] = '-';
	return (int_to_str(dst + sign, len - sign, n, DECIMAL_BASE));
}

/*
	Used functions:
	- ft_strdup
	- malloc
	- ft_strdup
*/
char	*nbr_to_str(int64_t n)
{
	uint8_t	len;
	bool	sign;
	char	*dst;

	sign = (n < 0);
	len = digit_counter(n, 10);
	dst = malloc((len + TERM) * sizeof(char));
	if (dst == NULL)
		return (NULL);
	if (sign == true)
		dst[0] = '-';
	return (int_to_str(dst + sign, len - sign, n, DECIMAL_BASE));
}

/*
	Used functions:
	- cpy_str
*/
uint8_t	nbr_to_buff(char *dst, int64_t n)
{
	uint8_t	len;
	bool	sign;

	sign = (n < 0);
	len = digit_counter(n, 10);
	if (sign == true)
		dst[0] = '-';
	int_to_str(dst + sign, len - sign, n, DECIMAL_BASE);
	return (len);
}

char	*int_to_str(char *dst, uint8_t len, int64_t n, const char *base)
{
	const size_t	base_len = ft_strlen(base);
	const bool		sign = (n < 0);
	uint64_t		abs_value;

	dst[len] = '\0';
	abs_value = abs_int64(n);
	while (len > 0)
	{
		--len;
		dst[len] = base[(abs_value % base_len)];
		abs_value /= base_len;
	}
	return (dst - sign);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa_base.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/12 01:38:48 by rjw           #+#    #+#                 */
/*   Updated: 2025/03/12 01:38:51 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/dbltoa.h"

uint8_t	digit_counter(int64_t n, uint8_t base_len)
{
	uint8_t	count;

	count = (n <= 0);
	while (n != 0)
	{
		n /= base_len;
		++count;
	}
	return (count);
}

uint64_t	abs_int64(int64_t n)
{
	if (n >= 0)
		return ((uint64_t)n);
	return (uint64_t)((-(n + 1)) + 1);
}

size_t	int64_base(int64_t n, const char *base, char *buff, size_t b_len)
{
	const bool	is_negative = (n < 0);
	size_t		base_len;
	uint64_t	abs_value;
	size_t		index;
	uint8_t		num_digits;

	abs_value = abs_int64(n);
	base_len = strlen_safe(base);
	if ((base_len < 2 || b_len < 2) && (b_len == 0 || cpy_str(buff, "\0") == 0))
		return (0);
	num_digits = digit_counter(n, base_len);
	while (num_digits-- >= b_len)
		abs_value /= base_len;
	index = b_len - 1;
	buff[index] = '\0';
	while ((abs_value > 0 && index > 0) || index == b_len - 1)
	{
		buff[--index] = base[abs_value % base_len];
		abs_value /= base_len;
	}
	if (is_negative == true && index > 0)
		buff[--index] = '-';
	if (index > 0)
		cpy_str(buff, buff + index);
	return (b_len - index - 1);
}

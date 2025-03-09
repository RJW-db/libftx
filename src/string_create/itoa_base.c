/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   itoa_base.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/01 02:29:51 by rjw           #+#    #+#                 */
/*   Updated: 2025/03/09 03:30:56 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*itoa_base(int64_t n, const char *base)
{
	size_t	base_len;
	uint8_t	len;
	bool	sign;
	char	*dst;

	base_len = strlen_safe(base);
	if (base_len < 2)
		return (NULL);
	sign = (n < 0);
	len = digit_counter(n, base_len);
	dst = malloc((len + TERM) * sizeof(char));
	if (dst == NULL)
		return (NULL);
	if (sign == true)
		dst[0] = '-';
	return (int_to_str(dst + sign, len - sign, n, base));
}

/**
 * index == buf_len - 1, is only for the case n = 0.
 */
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

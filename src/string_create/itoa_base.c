/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   itoa_buff.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/01 02:29:51 by rjw           #+#    #+#                 */
/*   Updated: 2025/03/01 02:39:44 by rjw           ########   odam.nl         */
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

size_t	int64_base(int64_t n, const char *base, char *buff, size_t buf_len)
{
	const bool	is_negative = (n < 0);
	size_t		base_len;
	uint64_t	abs_value;
	size_t		index;
	uint8_t		num_digits;

	abs_value = int64_to_abs(n);
	base_len = ft_strlen(base);
	num_digits = digit_counter(n, base_len);
	while (num_digits-- >= buf_len)
		abs_value /= base_len;
	index = buf_len - 1;
	buff[index] = '\0';
	while (abs_value > 0 && index > 0)
	{
		buff[--index] = base[abs_value % base_len];
		abs_value /= base_len;
	}
	if (abs_value == 0 && index == buf_len - 1)
		buff[--index] = base[0];
	if (is_negative && index > 0)
		buff[--index] = '-';
	if (index > 0)
		ft_strlcpy(buff, buff + index, buf_len - index - 1);
	return (buf_len - index - 1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   itoa_base.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/12 17:26:37 by jmetzger      #+#    #+#                 */
/*   Updated: 2025/03/03 17:05:02 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_dbltoa.h"

char	*int_to_str(char *dst, uint8_t len, int64_t n, const char *base)
{
	const size_t	base_len = ft_strlen(base);
	const bool		sign = (n < 0);
	uint64_t		abs_value;

	dst[len] = '\0';
	abs_value = (uint64_t)n;
	if (n < 0)
		abs_value = (uint64_t)(-(n + 1)) + 1;
	while (len > 0)
	{
		--len;
		dst[len] = base[(abs_value % base_len)];
		abs_value /= base_len;
	}
	return (dst - sign);
}

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
	dst = malloc((len + 1) * sizeof(char));
	if (dst == NULL)
		return (NULL);
	if (sign == true)
		dst[0] = '-';
	return (int_to_str(dst + sign, len - sign, n, base));
}

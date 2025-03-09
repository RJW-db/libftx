/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   convert_binary_to_decimal.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/12 17:26:37 by jmetzger      #+#    #+#                 */
/*   Updated: 2025/03/09 03:50:08 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_dbltoa.h"

// base_len && convert_to_base, can be in atoi_utils or something

uint16_t	base_len(uint64_t nbr, uint64_t base)
{
	uint16_t	length;
	
	length = 1;
	while (nbr >= base)
	{
		nbr /= base;
		length += 1;
	}
	return length;
}

void	convert_base(uint64_t nbu, char *base, uint64_t b_val, char *result)
{
	uint64_t	i;
	uint64_t	len;
	char		tmp;

	if (b_val < 2 || b_val > 64)
		return;
	len = 0;
	while (nbu >= b_val)
	{
		result[len++] = base[nbu % b_val];
		nbu /= b_val;
	}
	result[len++] = base[nbu];
	result[len] = '\0';
	for (i = 0; i < len / 2; ++i)
	{
		tmp = result[i];
		result[i] = result[len - i - 1];
		result[len - i - 1] = tmp;
	}
}

bool	binary_to_decimal(const char *bin_str, char *dec_str, size_t size)
{
	uint64_t	binary_value;
	uint16_t	bit_length;
	bool		sign;

	binary_value = abs_int64(atoi_base(bin_str, BINARY_BASE, &sign));

	bit_length = base_len(binary_value, DECIMAL_NBR);

	if (size < (size_t)(bit_length + 1))
		return (false);
	ft_memset(dec_str, '\0', bit_length + 1);
	if (sign == true && binary_value != 0)
		dec_str[0] = '-';
	convert_base(binary_value, DECIMAL_BASE, DECIMAL_NBR, dec_str);
	return (true);
}
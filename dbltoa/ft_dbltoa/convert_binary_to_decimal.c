/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   convert_binary_to_decimal.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/12 17:26:37 by jmetzger      #+#    #+#                 */
/*   Updated: 2025/03/08 03:50:31 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_dbltoa.h"

static void	itoabase_len(uint64_t nbu, uint64_t basevalue, int64_t *len)
{
	while (nbu >= basevalue)
	{
		nbu /= basevalue;
		*len += 1;
	}
	*len += 1;
}

static void	ft_itoabase_val(uint64_t nbu, char *base_to, uint64_t basevalue, char *nbrconv)
{
	uint64_t	i;

	i = 0;
	if (nbu >= basevalue)
	{
		ft_itoabase_val(nbu / basevalue, base_to, basevalue, nbrconv);
		ft_itoabase_val(nbu % basevalue, base_to, basevalue, nbrconv);
	}
	else
	{
		while (nbrconv[i])
			i++;
		nbrconv[i] = base_to[nbu];
		nbrconv[i + 1] = '\0';
	}
}

static uint64_t	convert_to_unsigned(int64_t convert_to_unsigned)
{
	uint64_t unsigned_value;

	unsigned_value = 0;
	if (convert_to_unsigned < 0)
	{
		unsigned_value = -1 * convert_to_unsigned;
	}
	else
		unsigned_value = convert_to_unsigned;
	return (unsigned_value);
}

bool		binary_to_decimal(const char *bin_str, char *dec_str, size_t size)
{
	uint64_t	binary_value;
	int64_t		bit_length;
	bool		sign;

	binary_value = convert_to_unsigned(ft_atoi_b(bin_str, BINARY_BASE, &sign));

	bit_length = 0;
	itoabase_len(binary_value, DECIMAL_NBR, &bit_length);

	if (size < (size_t)(bit_length + 1))
		return (false);

	ft_memset(dec_str, '\0', bit_length + 1);
	if (sign == true && binary_value != 0)
		dec_str[0] = '-';

	ft_itoabase_val(binary_value, DECIMAL_BASE, DECIMAL_NBR, dec_str);
	return (true);
}
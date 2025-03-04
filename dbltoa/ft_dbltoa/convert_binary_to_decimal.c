/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   convert_binary_to_decimal.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/12 17:26:37 by jmetzger      #+#    #+#                 */
/*   Updated: 2025/03/04 21:34:35 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_dbltoa.h"

static void	ft_itoabase_len(uint64_t nbu, char *base_to, uint64_t basevalue, int64_t *len)
{
	if (nbu >= basevalue)
	{
		ft_itoabase_len(nbu / basevalue, base_to, basevalue, len);
		ft_itoabase_len(nbu % basevalue, base_to, basevalue, len);
	}
	else
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

static uint64_t	ft_convunsigned(int64_t nb)
{
	uint64_t nbu;

	nbu = 0;
	if (nb < 0)
	{
		nbu = -1 * nb;
	}
	else
		nbu = nb;
	return (nbu);
}

bool	binary_to_decimal(char *nbr, char *buff, size_t buff_size)
{
	uint64_t	nbu;
	int64_t		len;
	int64_t		sig;

	nbu = ft_convunsigned(ft_atoi_b(nbr, BINARY_BASE, BINARY_NBR, &sig));

	len = 0;
	ft_itoabase_len(nbu, DECIMAL_BASE, DECIMAL_NBR, &len);

	if (buff_size < (size_t)(len + 1))
		return (false);

	ft_memset(buff, '\0', len + 1);
	if (sig < 0 && nbu != 0)
		buff[0] = '-';

	ft_itoabase_val(nbu, DECIMAL_BASE, DECIMAL_NBR, buff);
	return (true);
}
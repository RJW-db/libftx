/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   convert_binary_to_decimal.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/12 17:26:37 by jmetzger      #+#    #+#                 */
/*   Updated: 2025/03/04 21:18:58 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_dbltoa.h"

static void			ft_itoabase_len(unsigned long nbu, char *base_to,
					unsigned long basevalue, long *len)
{
	if (nbu >= basevalue)
	{
		ft_itoabase_len(nbu / basevalue, base_to, basevalue, len);
		ft_itoabase_len(nbu % basevalue, base_to, basevalue, len);
	}
	else
		*len = *len + 1;
}

static void			ft_itoabase_val(unsigned long nbu, char *base_to,
					unsigned long basevalue, char *nbrconv)
{
	unsigned long i;

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

static unsigned long	ft_convunsigned(long nb, long *len)
{
	unsigned long nbu;

	nbu = 0;
	if (nb < 0)
	{
		nbu = -1 * nb;
		// len++;
		(void)len;
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

	len = 0;
	nbu = ft_convunsigned(ft_atoi_b(nbr, BINARY_BASE, BINARY_NBR, &sig), &len);

	ft_itoabase_len(nbu, DECIMAL_BASE, DECIMAL_NBR, &len);

	if (buff_size < (size_t)(len + 1))
		return (false);

	ft_init_malloc(buff, len);
	if (sig < 0 && nbu != 0)
		buff[0] = '-';

	ft_itoabase_val(nbu, DECIMAL_BASE, DECIMAL_NBR, buff);
	return (true);
}
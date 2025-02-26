/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   convert_binary_to_decimal.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/12 17:26:37 by jmetzger      #+#    #+#                 */
/*   Updated: 2025/02/26 15:09:10 by rde-brui      ########   odam.nl         */
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

char			*convert_binary_to_decimal(char *nbr, char *base_from, char *base_to)
{
	unsigned long	nbu;
	long			basevalue;
	long			len;
	char			*nbrconv;
	long			sig;

	basevalue = 0;
	len = 0;
	if (!ft_basecheck(base_from) || !ft_basecheck(base_to))
		return (NULL);
	while (base_from[basevalue])
		basevalue++;
	nbu = ft_convunsigned(ft_atoi_b(nbr, base_from, basevalue, &sig), &len);
	basevalue = 0;
	while (base_to[basevalue])
		basevalue++;
	ft_itoabase_len(nbu, base_to, (unsigned long)basevalue, &len);
	if (!(nbrconv = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	ft_init_malloc(nbrconv, len);
	if (sig < 0 && nbu != 0)
		nbrconv[0] = '-';
	ft_itoabase_val(nbu, base_to, (unsigned long)basevalue, nbrconv);
	return (nbrconv);
}

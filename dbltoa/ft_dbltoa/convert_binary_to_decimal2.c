/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   convert_binary_to_decimal2.c                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/12 17:26:37 by jmetzger      #+#    #+#                 */
/*   Updated: 2025/02/21 19:48:42 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_dbltoa.h"

long			ft_basecheck(char *base_from)
{
	long i;
	long j;

	i = 0;
	if (base_from[0] == '\0' || base_from[1] == '\0')
		return (0);
	while (base_from[i])
	{
		j = i;
		if ((base_from[i] >= 9 && base_from[i] <= 13) || base_from[i] == ' '
				|| base_from[i] == '+' || base_from[i] == '-')
			return (0);
		while (base_from[++j])
			if (base_from[j] == base_from[i])
				return (0);
		i++;
	}
	return (1);
}

long			ft_isnumber(char c, char *base_from)
{
	long i;

	i = 0;
	while (base_from[i] && base_from[i] != c)
		i++;
	if (base_from[i] == '\0' || c == '\0')
		return (-1);
	else
		return (i);
}

long			ft_atoi_b(char *nbr, char *base_from, long basevalue, long *sig)
{
	long nb;
	long i;

	nb = 0;
	i = 0;
	*sig = 1;
	while ((nbr[i] >= 9 && nbr[i] <= 13) || nbr[i] == ' ')
		i++;
	while (nbr[i] == '-' || nbr[i] == '+')
	{
		if (nbr[i] == '-')
			*sig = *sig * -1;
		i++;
	}
	while (ft_isnumber(nbr[i], base_from) + 1)
	{
		nb *= basevalue;
		nb += ft_isnumber(nbr[i], base_from);
		i++;
	}
	return (nb * (*sig));
}

long			ft_init_malloc(char *nbrconv, long len)
{
	long i;

	i = 0;
	while (i < (len + 1))
	{
		nbrconv[i] = '\0';
		i++;
	}
	return (i);
}

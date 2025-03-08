/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   convert_binary_to_decimal2.c                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/12 17:26:37 by jmetzger      #+#    #+#                 */
/*   Updated: 2025/03/08 03:53:37 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_dbltoa.h"

int64_t			ft_basecheck(char *base_from)
{
	int64_t i;
	int64_t j;

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

static int64_t			ft_isnumber(const char c, char *base_from)
{
	int64_t i;

	i = 0;
	while (base_from[i] && base_from[i] != c)
		i++;
	if (base_from[i] == '\0' || c == '\0')
		return (-1);
	return (i);
}

int64_t			ft_atoi_b(const char *nbr, char *base_from, bool *is_neg)
{
	int64_t		nb;
	uint64_t	i;

	nb = 0;
	i = 0;
	*is_neg = false;
	while ((nbr[i] >= 9 && nbr[i] <= 13) || nbr[i] == ' ')
		++i;
	while (nbr[i] == '-' || nbr[i] == '+')
	{
		if (nbr[i] == '-')
			*is_neg = !(*is_neg);
		++i;
	}
	while (ft_isnumber(nbr[i], base_from) + 1 > 0)
	{
		nb *= ft_strlen(base_from);
		nb += ft_isnumber(nbr[i], base_from);
		++i;
	}
	if (*is_neg == false)
		return (nb);
	return (-nb);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   convert_binary_to_decimal2.c                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/12 17:26:37 by jmetzger      #+#    #+#                 */
/*   Updated: 2025/03/09 03:22:54 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_dbltoa.h"

static int64_t	is_valid_base(const char c, const char *base)
{
	int64_t i = 0;
	
	while (base[i] != '\0')
	{
		if (base[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

static int16_t	parse_string(const char *nbr_str, char *base, bool *is_neg)
{
	int16_t	i;

	*is_neg = false;
	if (nbr_str == NULL || base == NULL)
		return (-1);
	i = 0;
	while ((nbr_str[i] >= '\t' && nbr_str[i] <= '\r') || nbr_str[i] == ' ')
		++i;
	while (nbr_str[i] == '-' || nbr_str[i] == '+')
	{
		if (nbr_str[i] == '-')
			*is_neg = !(*is_neg);
		++i;
	}
	return (i);
}

// Main function to convert the string to an integer based on the specified base
int64_t	atoi_base(const char *nbr_str, char *base, bool *is_neg)
{
	uint64_t	base_len;
	int16_t		index;
	int64_t		digit;
	int64_t		nbr;

	index = parse_string(nbr_str, base, is_neg);
	if (index == -1)
		return (0);
	base_len = ft_strlen(base);
	if (base_len < 2)
		return (0);
	nbr = 0;
	digit = is_valid_base(nbr_str[index], base);
	while (digit >= 0)
	{
		nbr = nbr * base_len + digit;
		++index;
		digit = is_valid_base(nbr_str[index], base);
	}
	if (*is_neg)
		nbr = -nbr;
	return (nbr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   str_to_number_base.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 20:31:39 by rjw           #+#    #+#                 */
/*   Updated: 2025/03/17 20:20:43 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

//	Static Functions
static int64_t	is_valid_base(const char c, const char *base);
static int16_t	parse_string(const char *nbr_str, char *base, bool *is_neg);

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

static int64_t	is_valid_base(const char c, const char *base)
{
	int64_t	i;

	i = 0;
	while (base[i] != '\0')
	{
		if (base[i] == c)
			return (i);
		++i;
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

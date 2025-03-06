/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_multi.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/12 17:26:37 by jmetzger      #+#    #+#                 */
/*   Updated: 2025/03/06 21:17:20 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_dbltoa.h"

size_t	find_char_not(const char *str, const char c1)
{
	char	*tmp_str;

	tmp_str = (char *)str;
	while (*tmp_str != '\0' && *tmp_str == c1)
	{
		++tmp_str;
	}
	if (*tmp_str != c1)
	{
		return (tmp_str - str);
	}
	return (0);
}

static void	process_carry(char *result, int32_t carry, int32_t pos)
{
	int32_t	tmp;

	while (carry > 0 && pos >= 1)
	{
		tmp = (result[pos] - '0') + carry;
		result[pos] = (tmp % 10) + '0';
		carry = tmp / 10;
		--pos;
	}
}

static void	multiply_single_digit(t_dbl *s, t_nbr *nbr, int32_t i, int32_t j)
{
	int32_t	pos;
	int32_t	tmp;
	int32_t	carry;

	carry = 0;
	while (j >= 0)
	{
		pos = BIG_INT - 1 - (nbr->j_s2 - i) - (nbr->i_s1 - j);
		if (pos >= 1)
		{
			tmp = ((s->s2[nbr->sig_s2 + i] - '0') * \
				(s->s1[nbr->sig_s1 + j] - '0')) + \
				(s->result[pos] - '0') + carry;
			s->result[pos] = (tmp % 10) + '0';
			carry = tmp / 10;
		}
		--j;
	}
	process_carry(s->result, carry, pos);
}

static void	process_digits(t_dbl *strings, t_nbr *nbr)
{
	int32_t	i;
	int32_t	j;

	i = nbr->j_s2;
	j = nbr->i_s1;
	while (i >= 0)
	{
		multiply_single_digit(strings, nbr, i, j);
		--i;
	}
}

static void	init_numbers(t_nbr *nbr, char *s1, char *s2)
{
	nbr->sig_s1 = find_char_not(s1 + (s1[0] == '+' || s1[0] == '-'), '0');
	nbr->sig_s2 = find_char_not(s2 + (s2[0] == '+' || s2[0] == '-'), '0');
	nbr->i_s1 = ft_strlen(s1 + nbr->sig_s1) - 1;
	nbr->j_s2 = ft_strlen(s2 + nbr->sig_s2) - 1;
}

char	*ft_multi(char *s1, char *s2)
{
	char	result[BIG_INT + 1];
	char	sign;
	t_dbl	strings;
	t_nbr	nbr;

	init_bigChar(result);
	sign = '+';
	if ((s1[0] == '-' && s2[0] != '-') || (s1[0] != '-' && s2[0] == '-'))
		sign = '-';
	init_numbers(&nbr, s1, s2);
	strings = (t_dbl){s1, s2, result};
	process_digits(&strings, &nbr);
	cpy_str(s1, result);
	s1[0] = sign;
	return (s1);
}

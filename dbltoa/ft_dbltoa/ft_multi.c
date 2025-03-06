/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_multi.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/12 17:26:37 by jmetzger      #+#    #+#                 */
/*   Updated: 2025/03/06 03:28:11 by rjw           ########   odam.nl         */
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

static void	multiply_digits(t_mult *d, t_nbr *num, int32_t i, int32_t j)
{
	int32_t pos;
	int32_t tmp;
	int32_t carry;
	
	carry = 0;
	while (j >= 0)
	{
		pos = BIG_INT - 1 - (num->j_s2 - i) - (num->i_s1 - j);
		if (pos >= 1)
		{
			tmp = (d->s2[num->digit_s2 + i] - '0') *
			(d->s1[num->digit_s1 + j] - '0') + carry + (d->result[pos] - '0');
			d->result[pos] = (tmp % 10) + '0';
			carry = tmp / 10;
		}
		--j;
	}
	pos = BIG_INT - 1 - (num->j_s2 - i) - (num->i_s1 - j);
	while (carry > 0 && pos >= 1)
	{
		tmp = (d->result[pos] - '0') + carry;
		d->result[pos] = (tmp % 10) + '0';
		carry = tmp / 10;
		--pos;
	}
}

char	*ft_multi(char *s1, char *s2)
{
	char		result[BIG_INT + 1];
	char		sign;
	t_mult	data;
	t_nbr	num;
	int32_t		i;

	init_bigChar(result);
	data = (t_mult){result, s1, s2};
	sign = '+';
	if (s1[0] == '-' && s2[0] != '-')
		sign = '-';
	num.digit_s1 = find_char_not(s1 + (s1[0] == '+' || s1[0] == '-'), '0');
	num.digit_s2 = find_char_not(s2 + (s2[0] == '+' || s2[0] == '-'), '0');
	num.i_s1 = ft_strlen(s1 + num.digit_s1) - 1;
	num.j_s2 = ft_strlen(s2 + num.digit_s2) - 1;
	i = num.j_s2;
	while (i >= 0)
	{
		multiply_digits(&data, &num, i, num.i_s1);
		--i;
	}
	cpy_str(s1, result);
	s1[0] = sign;
	return s1;
}

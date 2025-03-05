/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_multi.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/12 17:26:37 by jmetzger      #+#    #+#                 */
/*   Updated: 2025/03/05 20:38:56 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_dbltoa.h"

/*
 * This function does signed multiplication of large integers stored as strings.
 *
 * ft_multi: 
 * 		Main function that performs signed multiplication on two BigInts (s1 and s2). 
 * 		It updates s1 with the result.
 * ft_multi2: 
 * 		Core multiplication algorithm that performs digit-by-digit multiplication and sums the results into s1.
 * ft_multi3: 
 * 		A performance optimization for cases where the multiplication is by 10, 
 * 		shifting digits instead of doing full multiplication.
 */

static void	ft_multi3(char *s1, t_number *num)
{
	ft_strlcpy(s1 + num->digit_s1 - 1, s1 + num->digit_s1,
			BIG_INT + 1 - num->digit_s1);
	s1[BIG_INT - 1] = '0';
}

static char	*ft_multi2(char *s1, char *s2, t_number *num)
{
	int			nbr;
	char		tmp[BIG_INT + 1];
	char		tmp2[BIG_INT + 1];

	init_bigChar(tmp);
	while (num->j_s2 >= num->digit_s2 && (num->i_s1 - (BIG_INT - 1 - num->j_s2)) > 1)
	{
		while (num->i_s1 >= num->digit_s1 && (num->i_s1 - (BIG_INT - 1 - num->j_s2)) > 1)
		{
			init_bigChar(tmp2);
			nbr = s1[num->i_s1] - 48;
			nbr *= (s2[num->j_s2] - 48);
			tmp2[num->i_s1 - (BIG_INT - 1 - num->j_s2)] = nbr % 10 + 48;
			tmp2[num->i_s1 - (BIG_INT - 1 - num->j_s2) - 1] = nbr / 10 + 48;
			if (big_int_add(tmp, tmp2) == NULL)
				return (NULL);
			(num->i_s1)--;
		}
		if ((num->i_s1 - (BIG_INT - 1 - num->j_s2)) <= 1)
			return (NULL);
		(num->j_s2)--;
		num->i_s1 = BIG_INT - 1;
	}
	ft_strlcpy(s1, tmp, BIG_INT + 1);
	return (s1);
}

char	*ft_multi(char *s1, char *s2)
{
	t_number	num;
	char		sign;

	init_struct(s1, s2, &num);
	if (num.i_s1 < num.digit_s1 || num.j_s2 < num.digit_s2)
	{
		ft_memset(s1, 48, BIG_INT);
		s1[0] = '+';
		return (s1);
	}
	else if (s1[0] != s2[0])
		sign = '-';
	else if (s1[0] == s2[0])
		sign = '+';
	if (num.digit_s2 == (BIG_INT - 2) && s2[num.digit_s2] == '1' && s2[num.j_s2] == '0'
			&& num.digit_s1 > 1)
		ft_multi3(s1, &num);
	else if (!ft_multi2(s1, s2, &num))
		return (NULL);
	s1[0] = sign;
	return (s1);
}


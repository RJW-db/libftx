/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_add.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/12 17:26:37 by jmetzger      #+#    #+#                 */
/*   Updated: 2025/02/21 19:34:12 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_dbltoa.h"

/*
 * The function ft_add and its helper functions allow the addition of 
 * two signed numbers stored in strings.
 * 
 * The first character (index 0) is the sign ('+' or '-').
 * The remaining characters represent the digits of the number.
 * These strings must be the same length, 
 * and only contain numeric characters, except for the sign.
 * 
 * ft_add:
 * 		The function is the main entry point for adding two large numbers.
 * ft_add2:
 * 		This function handles the case where both numbers have the same sign (either both '+' or both '-').
 * ft_add3:
 * 		This function is used when the two numbers are equal in magnitude but have opposite signs.
 * ft_add4:
 * 		This function handles the case where s1 is positive ('+') and s2 is negative ('-').
 * ft_add5:
 * 		This function is the opposite case of ft_add4, where s1 is negative ('-') and s2 is positive ('+').
 */

static char	*ft_add5(char *s1, char *s2)
{
	char		tmp[BIG_INT + 1];

	ft_memset(tmp, 48, BIG_INT);
	tmp[BIG_INT] = '\0';
	ft_strlcpy(tmp, s1, BIG_INT + 1);
	ft_strlcpy(s1, s2, BIG_INT + 1);
	tmp[0] = '+';
	return (ft_subs(s1, tmp));
}

static char	*ft_add4(char *s1, char *s2)
{
	char		tmp[BIG_INT + 1];

	ft_memset(tmp, 48, BIG_INT);
	tmp[BIG_INT] = '\0';
	ft_strlcpy(tmp, s2, BIG_INT + 1);
	tmp[0] = '+';
	return (ft_subs(s1, tmp));
}

static char	*ft_add3(char *s1)
{
	ft_memset(s1, 48, BIG_INT);
	s1[0] = '+';
	return (s1);
}

static void	ft_add2(char *s1, char *s2, t_number *num)
{
	while (num->j_s2 >= num->digit_s2 && num->i_s1 != 0)
	{
		if (s1[num->i_s1] > '9')
		{
			s1[num->i_s1] -= 10;
			s1[num->i_s1 - 1] += 1;
		}
		if (s1[num->i_s1] + s2[num->j_s2] - 48 <= '9')
			s1[num->i_s1] += s2[num->j_s2] - 48;
		else if (num->i_s1 != 0)
		{
			s1[num->i_s1] += s2[num->j_s2] - 58;
			s1[num->i_s1 - 1] += 1;
		}
		(num->j_s2)--;
		(num->i_s1)--;
	}
	while (s1[num->i_s1] > '9' && num->i_s1 != 0)
	{
		s1[num->i_s1--] -= 10;
		s1[num->i_s1] += 1;
	}
}

char	*ft_add(char *s1, char *s2)
{
	t_number	num;

	init_struct(s1, s2, &num);
	if (num.i_s1 == -1 || num.j_s2 == -1 || s2[num.digit_s2] == '\0')
		return (s1);
	if ((s1[0] == '+' && s2[0] == '+') || (s1[0] == '-' && s2[0] == '-'))
		ft_add2(s1, s2, &num);
	else if (compare_str(s1, s2) == 0 && (s1[0] != s2[0]))
		return (ft_add3(s1));
	else if (s1[0] == '+' && s2[0] == '-')
		return (ft_add4(s1, s2));
	else if (s1[0] == '-' && s2[0] == '+')
		return (ft_add5(s1, s2));
	if (num.i_s1 == 0 && (num.j_s2 != (num.digit_s2 - 1) || s1[num.i_s1] > '9'))
		return (NULL);
	return (s1);
}

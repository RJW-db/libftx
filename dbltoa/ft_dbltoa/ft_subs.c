/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_subs.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/12 17:26:37 by jmetzger      #+#    #+#                 */
/*   Updated: 2025/03/06 03:28:11 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_dbltoa.h"

// This Function does subtraction, working with numbers stored as strings. 
// The subtraction is performed in s1, and the result replaces s1.

static void	ft_subs5(char *s1, char *s2)
{
	char		tmp[BIG_INT + 1];

	ft_memset(tmp, 48, BIG_INT);
	tmp[BIG_INT] = '\0';
	ft_strlcpy(tmp, s2, BIG_INT + 1);
	tmp[0] = '-';
	// ft_add(s1, tmp);
	big_int_add(s1, tmp);
}

static void	ft_subs4(char *s1, char *s2)
{
	char		tmp[BIG_INT + 1];

	ft_memset(tmp, 48, BIG_INT);
	tmp[BIG_INT] = '\0';
	ft_strlcpy(tmp, s2, BIG_INT + 1);
	tmp[0] = '+';
	// ft_add(s1, tmp);
	big_int_add(s1, tmp);
}

static char	*ft_subs3(char *s1)
{
	ft_memset(s1, 48, BIG_INT);
	s1[0] = '+';
	return (s1);
}

static void ft_subs2(char *s1, char *s2, t_nbr *num)
{
	while (num->j_s2 >= num->digit_s2 && num->i_s1 != 0)
	{
		// Borrow if needed
		if (s1[num->i_s1] < s2[num->j_s2])
		{
			s1[num->i_s1] += 10;
			s1[num->i_s1 - 1] -= 1;
		}
		s1[num->i_s1] -= (s2[num->j_s2] - '0');
		num->j_s2--;
		num->i_s1--;
	}
}

static void ft_subs_swap_negate(char *s1, char *s2, t_nbr *num)
{
	char tmp[BIG_INT + 1];

	ft_memset(tmp, '0', BIG_INT);
	tmp[BIG_INT] = '\0';

	ft_strlcpy(tmp, s1, BIG_INT + 1);
	ft_strlcpy(s1, s2, BIG_INT + 1);
	ft_subs2(s1, tmp, num);

	// Flip sign
	if (s1[0] == '+')
		s1[0] = '-';
	else
		s1[0] = '+';
}

char *ft_subs(char *s1, char *s2)
{
	t_nbr	num;
	int			comp;

	init_struct(s1, s2, &num);
	if (num.i_s1 == -1 || num.j_s2 == -1 || s2[num.digit_s2] == '\0')
		return s1;
	
	// If s1 == s2
	if ((comp = compare_str(s1, s2)) == 0)
		return ft_subs3(s1);
	
	if (s1[0] == '+' && s2[0] == '-')
		ft_subs4(s1, s2);
	else if (s1[0] == '-' && s2[0] == '+')
		ft_subs5(s1, s2);
	else if (comp > 0)
		ft_subs2(s1, s2, &num);
	else
		ft_subs_swap_negate(s1, s2, &num);

	// Ensure s1 has enough space
	if (num.i_s1 == 0 && (num.j_s2 != num.digit_s2 - 1 || s1[num.i_s1] < '0'))
		return NULL;
	return s1;
}

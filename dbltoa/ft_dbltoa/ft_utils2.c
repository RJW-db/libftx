/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   big_ints_calc.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: j_s2metzger <j_s2metzger@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/12 17:26:37 by j_s2metzger      #+#    #+#                 */
/*   Updated: 2025/02/21 16:03:48 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/ft_dbltoa.h"

/* init_struct()
 * The function initializes a t_number struct, 
 * which is designed to store metadata about two input strings s1 and s2. 
 * These strings represent big integers.
 */
void init_struct(char *s1, char *s2, t_nbr *num)
{
	num->digit_s1 = (s1[0] == '+' || s1[0] == '-');
	while (s1[num->digit_s1] == '0')
		++num->digit_s1;
	num->i_s1 = num->digit_s1 + ft_strlen(s1 + num->digit_s1);
	num->i_s1 -= (num->i_s1 > 0);
	num->digit_s2 = (s2[0] == '+' || s2[0] == '-');
	while (s2[num->digit_s2] == '0')
		++num->digit_s2;
	num->j_s2 = num->digit_s2 + ft_strlen(s2 + num->digit_s2);
	num->j_s2 -= (num->j_s2 > 0);
}

/* compare_str()
 * The function compares two strings (s1 and s2), 
 * which are represent large integers.
 *
 * - Returns a positive value if the first string (s1) represents a larger number.
 * - Returns a negative value if the first string (s1) represents a smaller number.
 * - Returns 0 if both strings represent the same number.
 */
int		compare_str(char *s1, char *s2)
{
	t_nbr	num;
	int			len_diff;

	init_struct(s1, s2, &num);
	len_diff = (num.i_s1 - num.digit_s1) - (num.j_s2 - num.digit_s2);
	if (len_diff != 0)
		return (len_diff);
	while (s1[num.digit_s1] != '\0' && s2[num.digit_s2] != '\0' &&
			s1[num.digit_s1] == s2[num.digit_s2])
	{
		++num.digit_s1;
		++num.digit_s2;
	}
	return ((unsigned char)(s1[num.digit_s1]) - (unsigned char)(s2[num.digit_s2]));
}



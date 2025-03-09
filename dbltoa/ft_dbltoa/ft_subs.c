/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_subs.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/12 17:26:37 by jmetzger      #+#    #+#                 */
/*   Updated: 2025/03/09 04:23:26 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_dbltoa.h"

static void	add_with_sign(char *s1, char *s2, char sign)
{
	char	tmp[BIG_INT + 1];

	ft_memset(tmp, '0', BIG_INT);
	tmp[BIG_INT] = '\0';
	cpy_str(tmp, s2);
	tmp[0] = sign;
	ft_addition(s1, tmp);
}

static char	*set_to_zero(char *s1)
{
	ft_memset(s1, '0', BIG_INT);
	s1[0] = '+';
	return (s1);
}

static void subtract_values(char *s1, char *s2, t_nbr *nbr)
{
	while (nbr->j_s2 >= nbr->sig_s2 && nbr->i_s1 != 0)
	{
		if (s1[nbr->i_s1] < s2[nbr->j_s2])
		{
			s1[nbr->i_s1] += 10;
			s1[nbr->i_s1 - 1] -= 1;
		}
		s1[nbr->i_s1] -= (s2[nbr->j_s2] - '0');
		--nbr->j_s2;
		--nbr->i_s1;
	}
}

static void swap_and_negate(char *s1, char *s2, t_nbr *nbr)
{
	char tmp[BIG_INT + 1];

	ft_memset(tmp, '0', BIG_INT);
	tmp[BIG_INT] = '\0';

	ft_strlcpy(tmp, s1, BIG_INT + 1);
	ft_strlcpy(s1, s2, BIG_INT + 1);
	subtract_values(s1, tmp, nbr);

	// Flip sign
	if (s1[0] == '+')
		s1[0] = '-';
	else
		s1[0] = '+';
}

void	ft_subtraction(char *s1, char *s2)
{
	int		comparison_result;
	t_nbr	nbr;

	init_struct(s1, s2, &nbr);
	if (nbr.i_s1 == -1 || nbr.j_s2 == -1 || s2[nbr.sig_s2] == '\0')
		return ;
	comparison_result = ft_strncmp(s1, s2, ft_strlen(s1) + 1);
	if (comparison_result == 0)
		set_to_zero(s1);
	else if (s1[0] == '+' && s2[0] == '-')
		add_with_sign(s1, s2, '+');
	else if (s1[0] == '-' && s2[0] == '+')
		add_with_sign(s1, s2, '-');
	else if (comparison_result > 0)
		subtract_values(s1, s2, &nbr);
	else
		swap_and_negate(s1, s2, &nbr);
}

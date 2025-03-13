/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_helpers.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/12 03:14:31 by rjw           #+#    #+#                 */
/*   Updated: 2025/03/13 20:16:02 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <dbltoa.h>

void	intialize_buff(char *buff)
{
	ft_memset(buff, '0', MAX_DBL_STR_LEN);
	buff[MAX_DBL_STR_LEN] = '\0';
	buff[0] = '+';
}

void	init_struct(char *s1, char *s2, t_nbr *num)
{
	num->sig_s1 = (s1[0] == '+' || s1[0] == '-');
	while (s1[num->sig_s1] == '0')
		++num->sig_s1;
	num->i_s1 = num->sig_s1 + ft_strlen(s1 + num->sig_s1);
	num->i_s1 -= (num->i_s1 > 0);
	num->sig_s2 = (s2[0] == '+' || s2[0] == '-');
	while (s2[num->sig_s2] == '0')
		++num->sig_s2;
	num->j_s2 = num->sig_s2 + ft_strlen(s2 + num->sig_s2);
	num->j_s2 -= (num->j_s2 > 0);
}

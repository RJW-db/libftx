/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_divi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/12 17:26:37 by jmetzger      #+#    #+#                 */
/*   Updated: 2025/03/10 03:09:45 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_dbltoa.h"

static uint8_t	find_quotient(char *s1, char *s2)
{
	char tmp[BIG_INT + 1];
	uint8_t quotient = 0;
	
	cpy_str(tmp, s1);
	while (1) {
		int result = ft_subtraction(tmp, s2);	// while testing tmp could be s1
		if (result < 0)
			break;
		// if (result == 0) {					// never got here?
		//     ++quotient;
		//     break;puts("here");
		// }
		++quotient;
	}
	return (quotient);
}
static void	init_buffers(char *numerator, char *denominator)
{
	ft_memset(numerator, '\0', 10);
	ft_memset(denominator, '\0', 10);
	numerator[0] = '0';
	denominator[0] = '0';
}

static void	perform_division(char *s1, char *deno, char *result, t_nbr *nbr)
{
	char	numerator[DBL_MANT_DECIMAL_DIGITS];
	char	denominator[DBL_MANT_DECIMAL_DIGITS];
	uint8_t	quotient;

	init_struct(s1, deno, nbr);
	init_buffers(numerator, denominator);
	quotient = BIG_INT - nbr->sig_s2;
	if (quotient > DBL_MANT_DECIMAL_DIGITS - 1)
		quotient = DBL_MANT_DECIMAL_DIGITS - 1;
	ft_strlcpy(numerator, s1 + nbr->sig_s1, quotient);
	if ((atoi64(numerator) / atoi64(denominator)) == \
		(atoi64(numerator) / ((atoi64(denominator) + 1))))
		quotient = atoi64(numerator) / atoi64(denominator);
		
	else
		quotient = find_quotient(s1, deno);
	result[BIG_INT - 1] = quotient + '0';
}

void	ft_division(char *s1, char *s2)
{
	t_nbr	nbr;
	char	result[BIG_INT + 1];

	intialize_string(result);
	if (ft_strncmp(result, s2, BIG_INT + 1) == 0)
		return ;
	if (ft_strncmp(s1, s2, ft_strlen(s1) + 1) >= 0)
		perform_division(s1, s2, result, &nbr);
	cpy_str(s1, result);
}

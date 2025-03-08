/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_divi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/12 17:26:37 by jmetzger      #+#    #+#                 */
/*   Updated: 2025/03/08 02:32:22 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_dbltoa.h"

/*
 * The function does division for large integers with optimized handling 
 * for floating-point-like calculations by operating mainly on 
 * the first 15 digits of the numbers. 
 * It ensures proper sign handling and falls back on full bigint division when necessary.
 * 
 * ft_divi: 
 * 		This function is the main entry point to divide two large integers represented as strings. 
 * 		It checks for division by zero, calculates the result, and returns the result as a string.
 * division_core: 
 * 		This function performs the optimized division on the large integers, 
 * 		especially for floating-point calculations where only 
 * 		the first 15 digits are typically used for the result.
 * init_buffers: 
 * 		Initializes arrays for storing the numbers involved in the division.
 * ft_divi4: 
 * 		Performs further calculations if necessary to ensure accuracy in the result.
 */

static uint8_t	ft_find_quotient(char *s1, char *s2)
{
	char	tmp[BIG_INT + 1];
	uint8_t	quotient;

	quotient = 0;
	intialize_string(tmp);
	while (compare_str(ft_addition(tmp, s2), s1) <= 0)
		++quotient;
	return (quotient);
}

static void	init_buffers(char *numerator, char *denominator)
{
	ft_memset(numerator, '\0', 10);
	ft_memset(denominator, '\0', 10);
	numerator[0] = '0';
	denominator[0] = '0';
}

static void	division_core(char *s1, char *s2, char *result, t_nbr *nbr)
{
	char	numerator[DBL_MANT_DECIMAL_DIGITS];
	char	denominator[DBL_MANT_DECIMAL_DIGITS];
	uint8_t	quotient;

	init_struct(s1, s2, nbr);
	init_buffers(numerator, denominator);
	quotient = BIG_INT - nbr->sig_s2;
	if (quotient > DBL_MANT_DECIMAL_DIGITS - 1)
		quotient = DBL_MANT_DECIMAL_DIGITS - 1;
	ft_strlcpy(denominator + 1, s2 + nbr->sig_s2, quotient);
	if (nbr->sig_s1 == nbr->sig_s2)
		ft_strlcpy(numerator + 1, s1 + nbr->sig_s1, quotient);
	else
		ft_strlcpy(numerator, s1 + nbr->sig_s1, quotient + 1);
	if ((atoi64(numerator) / atoi64(denominator)) == \
		(atoi64(numerator) / ((atoi64(denominator) + 1))))
		quotient = atoi64(numerator) / atoi64(denominator);
	else
		quotient = ft_find_quotient(s1, s2);
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
		division_core(s1, s2, result, &nbr);
	cpy_str(s1, result);
}
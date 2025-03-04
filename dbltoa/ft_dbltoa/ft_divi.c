/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_divi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/12 17:26:37 by jmetzger      #+#    #+#                 */
/*   Updated: 2025/03/04 20:15:38 by rde-brui      ########   odam.nl         */
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
 * ft_divi2: 
 * 		This function performs the optimized division on the large integers, 
 * 		especially for floating-point calculations where only 
 * 		the first 15 digits are typically used for the result.
 * ft_divi3: 
 * 		Initializes arrays for storing the numbers involved in the division.
 * ft_divi4: 
 * 		Performs further calculations if necessary to ensure accuracy in the result.
 */

static void	ft_divi4(char *s1, char *s2, char *tmp, long *nb)
{
	*nb = 0;
	init_bigChar(tmp);
	while (compare_str(ft_add(tmp, s2), s1) <= 0)
		(*nb)++;
}

static void	ft_divi3(char *numer, char *denom)
{
	ft_memset(numer, 0, 10);
	ft_memset(denom, 0, 10);
	numer[0] = '0';
	denom[0] = '0';
}

static void	ft_divi2(char *s1, char *s2, char *result, t_number *num)
{
	long	nb;
	char	tmp[BIG_INT + 1];
	char	numer[16];
	char	denom[16];

	if (compare_str(s1, s2) < 0)
		return ;
	init_struct(s1, s2, num);
	ft_divi3(numer, denom);
	nb = BIG_INT - num->digit_s2;
	if (nb > 15)
		nb = 15;
	ft_strlcpy(denom + 1, s2 + num->digit_s2, nb);
	if (num->digit_s1 == num->digit_s2)
		ft_strlcpy(numer + 1, s1 + num->digit_s1, nb);
	else
		ft_strlcpy(numer, s1 + num->digit_s1, nb + 1);
	if ((atoi64(numer) / atoi64(denom)) ==
			(atoi64(numer) / ((atoi64(denom) + 1))))
		nb = atoi64(numer) / atoi64(denom);
	else
		ft_divi4(s1, s2, tmp, &nb);
	result[BIG_INT - 1] = nb + 48;
}

char	*ft_divi(char *s1, char *s2)
{
	t_number	num;
	char		sign;
	char		result[BIG_INT + 1];

	sign = '+';
	init_bigChar(result);
	if (!compare_str(result, s2))
		return (NULL);
	else if (s1[0] != s2[0])
		sign = '-';
	else if (s1[0] == s2[0])
		sign = '+';
	s1[0] = '+';
	s2[0] = '+';
	ft_divi2(s1, s2, result, &num);
	ft_strlcpy(s1, result, BIG_INT + 1);
	s1[0] = sign;
	return (s1);
}
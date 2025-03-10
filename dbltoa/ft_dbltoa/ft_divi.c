/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_divi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/12 17:26:37 by jmetzger      #+#    #+#                 */
/*   Updated: 2025/03/10 18:03:09 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_dbltoa.h"

static uint8_t	find_quotient(char *s1, char *s2)
{
	char tmp[MAX_DBL_STR_LEN + 1];
	uint8_t quotient = 0;
	
	cpy_str(tmp, s1);
	while (1) {
		int result = ft_subtraction(tmp, s2);	// while testing tmp could be s1
		if (result < 0) {
			break;
		}
		if (result == 0) {					// never got here?
		    ++quotient;
		    break;
		}
		++quotient;
	}
	return (quotient);
}

static uint8_t is_division_result_equal(char *num_str, char *den_str)
{
	int64_t num = atoi64(num_str);
	int64_t den = atoi64(den_str);
	int64_t quotient;

	if (den > 0)
	{
		quotient = num / den;
		if (quotient == (num / (den + 1)))
			return quotient;
	}
	return (0);
}
static void perform_division(char *s1, char *deno, char *result, t_nbr *nbr)
{
	char numerator[DBL_MANT_DECIMAL_DIGITS];
	char denominator[DBL_MANT_DECIMAL_DIGITS];
	uint8_t quotient;
	
	init_struct(s1, deno, nbr);
	ft_memset(numerator, '\0', DBL_MANT_DECIMAL_DIGITS);
	ft_memset(denominator, '\0', DBL_MANT_DECIMAL_DIGITS);
	numerator[0] = '0';
	denominator[0] = '0';
	quotient = MAX_DBL_STR_LEN - nbr->sig_s2;
	if (quotient > DBL_MANT_DECIMAL_DIGITS - 1)
		quotient = DBL_MANT_DECIMAL_DIGITS - 1;
	ft_strlcpy(denominator + 1, deno + nbr->sig_s2, quotient);
	if (nbr->sig_s1 == nbr->sig_s2)
		ft_strlcpy(numerator + 1, s1 + nbr->sig_s1, quotient);
	else
		ft_strlcpy(numerator, s1 + nbr->sig_s1, quotient + 1);
	quotient = is_division_result_equal(numerator, denominator);
	if (quotient == 0)
		quotient = find_quotient(s1, deno);
	result[MAX_DBL_STR_LEN - 1] = quotient + '0';
}

void	ft_division(char *s1, char *s2)
{
	t_nbr	nbr;
	char	result[MAX_DBL_STR_LEN + 1];

	intialize_string(result);
	if (ft_strncmp(result, s2, MAX_DBL_STR_LEN + 1) == 0)
		return ;
	if (ft_strncmp(s1, s2, ft_strlen(s1) + 1) >= 0)
		perform_division(s1, s2, result, &nbr);
	cpy_str(s1, result);
}



// int		compare_str(char *s1, char *s2)
// {
// 	t_nbr	num;
// 	int		len_diff;

// 	init_struct(s1, s2, &num);
// 	len_diff = (num.i_s1 - num.sig_s1) - (num.j_s2 - num.sig_s2);
// 	if (len_diff != 0)
// 		return (len_diff);
// 	while (s1[num.sig_s1] != '\0' && s2[num.sig_s2] != '\0' &&
// 			s1[num.sig_s1] == s2[num.sig_s2])
// 	{
// 		++num.sig_s1;
// 		++num.sig_s2;
// 	}
// 	return ((unsigned char)(s1[num.sig_s1]) - (unsigned char)(s2[num.sig_s2]));
// }

// static void	ft_divi4(char *s1, char *s2, char *tmp, long *nb)
// {
// 	*nb = 0;
// 	intialize_string(tmp);
// 	while (compare_str(ft_addition(tmp, s2), s1) <= 0)
// 		++(*nb);
// }

// static void	ft_divi3(char *numer, char *denom)
// {
// 	ft_memset(numer, 0, 10);
// 	ft_memset(denom, 0, 10);
// 	numer[0] = '0';
// 	denom[0] = '0';
// }

// static void	ft_divi2(char *s1, char *s2, char *result, t_nbr *num)
// {
// 	long	nb;
// 	char	tmp[MAX_DBL_STR_LEN + 1];
// 	char	numer[16];
// 	char	denom[16];

// 	while (ft_strncmp(s1, s2, ft_strlen(s1) + 1) < 0)
// 		return ;
// 	init_struct(s1, s2, num);
// 	ft_divi3(numer, denom);
// 	nb = MAX_DBL_STR_LEN - num->sig_s2;
// 	if (nb > 15)
// 		nb = 15;
// 	ft_strlcpy(denom + 1, s2 + num->sig_s2, nb);
// 	if (num->sig_s1 == num->sig_s2)
// 		ft_strlcpy(numer + 1, s1 + num->sig_s1, nb);
// 	else
// 		ft_strlcpy(numer, s1 + num->sig_s1, nb + 1);
// 	if ((atoi64(numer) / atoi64(denom)) ==
// 			(atoi64(numer) / ((atoi64(denom) + 1))))
// 		nb = atoi64(numer) / atoi64(denom);
// 	else
// 		ft_divi4(s1, s2, tmp, &nb);
// 	result[MAX_DBL_STR_LEN - 1] = nb + 48;
// }

// void	ft_division(char *s1, char *s2)
// {
// 	t_nbr	num;
// 	char	result[MAX_DBL_STR_LEN + 1];

// 	intialize_string(result);
// 	if (ft_strncmp(result, s2, MAX_DBL_STR_LEN + 1) == 0)
// 		return ;
// 	ft_divi2(s1, s2, result, &num);
// 	cpy_str(s1, result);
// }

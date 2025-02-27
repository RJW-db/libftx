/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   convert_to_str.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/12 17:26:37 by jmetzger      #+#    #+#                 */
/*   Updated: 2025/02/27 14:26:14 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_dbltoa.h"

/*
 * Converts a fraction (numerator/denominator) into a string representation of a floating-point number.
 * Handles cases such as numbers less than 1, decimal placement, and precision.
 */
static int		convert_first_digit(char *resultStr, char *num, char *deno)
{
	int		len;
	char	tmp[BIG_INT + 1];
	char	dix[BIG_INT + 1];

	len = 1;
	init_bigChar(tmp);
	init_bigChar(dix);
	dix[BIG_INT - 2] = '1';
	
	ft_strlcpy(tmp, num, BIG_INT + 1);
	ft_divi(tmp, deno);
	
	resultStr[len] = tmp[BIG_INT - 1];
	while (tmp[BIG_INT - 1]-- != '0')
		ft_subs(num, deno);
	
	ft_multi(num, dix);
	return (3);
}

/*
 * Ensures that the decimal point is placed correctly in the string representation.
 */
static void	place_decimal_point(char *resultStr, char *num, int *len, int *digitexp)
{
	char	zero[BIG_INT + 1];
	int		i;

	i = 0;
	init_bigChar(zero);
	if (*len - 1 > *digitexp && *digitexp)
	{
		resultStr[(*len)++] = '.';
		*digitexp = 0;
	}
	if (!compare_str(num, zero))
	{
		while (resultStr[i] && resultStr[i] != '.')
			i++;
		if (!resultStr[i])
			resultStr[*digitexp + 2] = '.';
	}
}

/*
 * Initializes memory for the result string, places the decimal point, 
 * and adds leading zeros for numbers < 1.
 */
static char	*initialize_result_string(char *digit, char *zero, int *digitexp, int *len)
{
	char *result;

	result = malloc(sizeof(*result) * (MAX_DIGIT + 1));
	if (result == NULL)
		return (NULL);
	result[MAX_DIGIT] = '\0';
	
	ft_memset(result, 48, MAX_DIGIT);
	if (*digitexp < 0)
	{
		result[++(*len)] = '.';
		while (*len - 2 < -(*digitexp))
			(*len)++;
	}
	else if (!(*digitexp))
		result[++(*len)] = '.';
		
	init_bigChar(digit);
	digit[BIG_INT - 2] = '1';
	init_bigChar(zero);
	return (result);
}

/*
 * function that converts a fraction (numerator/denominator) into a floating-point number string.
 * Handles edge cases like numbers < 1, proper placement of decimal point, and precision.
 */
char	*convert_to_str(char *dbl, char *num, char *deno, int digitexp)
{
	int		len;
	char	tmp[BIG_INT + 1];
	char	dix[BIG_INT + 1];
	char	zero[BIG_INT + 1];

	len = 1;
	if (!(dbl = initialize_result_string(dix, zero, &digitexp, &len)))
		return (NULL);
	if (!digitexp)
		len = convert_first_digit(dbl, num, deno);
	else if (digitexp < 0)
		digitexp = 0;
	while (compare_str(num, zero) != 0 && len < MAX_DIGIT)
	{
		init_bigChar(tmp);
		ft_strlcpy(tmp, num, BIG_INT + 1);
		if (!ft_divi(tmp, deno))
			return (NULL);
		dbl[len++] = tmp[BIG_INT - 1];
		while (tmp[BIG_INT - 1]-- != '0')
			ft_subs(num, deno);
		ft_multi(num, dix);
		place_decimal_point(dbl, num, &len, &digitexp);
	}
	return (dbl);
}

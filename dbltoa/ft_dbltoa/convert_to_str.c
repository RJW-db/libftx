/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   convert_to_str.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/12 17:26:37 by jmetzger      #+#    #+#                 */
/*   Updated: 2025/03/06 21:24:40 by rjw           ########   odam.nl         */
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
static void	place_decimal_point(char *resultStr, char *num, int *len, int16_t *digitexp)
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
static char	*initialize_result_string(char *digit, char *zero, int16_t *digitexp, int *len)
{
	char *result;

	result = malloc(sizeof(char) * (MAX_DIGIT + 1));
	if (result == NULL)
		return (NULL);
	result[MAX_DIGIT] = '\0';
	ft_memset(result, '0', MAX_DIGIT);
	if (*digitexp < 0)
	{
		result[++(*len)] = '.';
		while (*len - 2 < -(*digitexp))
			++(*len);
	}
	else if (*digitexp == 0)
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
// char	*convert_to_str(char *str, char *num, char *deno, int16_t digitexp)
char	*convert_to_str(t_dbl *s, int16_t digitexp)
{
	int		len;
	char	tmp[BIG_INT + 1];
	char	dix[BIG_INT + 1];
	char	zero[BIG_INT + 1];

	len = 1;
	s->result = initialize_result_string(dix, zero, &digitexp, &len);
	if (s->result == NULL)
		return (NULL);
	if (digitexp == 0)
		len = convert_first_digit(s->result, s->s1, s->s2);
	else if (digitexp < 0)
		digitexp = 0;
	while (compare_str(s->s1, zero) != 0 && len < MAX_DIGIT)
	{
		init_bigChar(tmp);
		ft_strlcpy(tmp, s->s1, BIG_INT + 1);
		if (!ft_divi(tmp, s->s2))
			return (NULL);
		s->result[len++] = tmp[BIG_INT - 1];
		while (tmp[BIG_INT - 1]-- != '0')
			ft_subs(s->s1, s->s2);
		ft_multi(s->s1, dix);
		place_decimal_point(s->result, s->s1, &len, &digitexp);
	}
	return (s->result);
}

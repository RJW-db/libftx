/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   convert_to_str.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/12 17:26:37 by jmetzger      #+#    #+#                 */
/*   Updated: 2025/03/07 17:37:27 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_dbltoa.h"

/*
 * Converts a fraction (numerator/denominator) into a string representation of a floating-point number.
 * Handles cases such as numbers less than 1, decimal placement, and precision.
 * 
 * --tmp[BIG_INT - 1];
 * if tmp[] = '5' it would become tmp[] = '4'
 */
static uint16_t		convert_first_digit(char *result, char *num, char *deno)
{
	char	tmp[BIG_INT + 1];
	char	digit[BIG_INT + 1];

	init_bigChar(tmp);
	init_bigChar(digit);
	digit[BIG_INT - 2] = '1';
	
	cpy_str(tmp, num);
	ft_division(tmp, deno);			// TODO might change functions
	
	result[1] = tmp[BIG_INT - 1];
	while (tmp[BIG_INT - 1] != '0')  
	{  
		ft_subtraction(num, deno);		// TODO might change functions
		--tmp[BIG_INT - 1];
	}
	ft_multiply(num, digit);
	return (3);
}

/*
 * Ensures that the decimal point is placed correctly in the string representation.
 */
static void	place_decimal_point(char *resultStr, char *num, uint16_t *len, int16_t *digitexp)
{
	char	zero[BIG_INT + 1];
	uint16_t	i;

	i = 0;
	init_bigChar(zero);
	if (*len - 1 > *digitexp && *digitexp != 0)
	{
		resultStr[(*len)++] = '.';
		*digitexp = 0;
	}
	if (ft_strncmp(num, zero, ft_strlen(num) + 1) == 0)
	{
		while (resultStr[i] && resultStr[i] != '.')
			++i;
		if (resultStr[i] == '\0')
			resultStr[*digitexp + 2] = '.';
	}
}

uint16_t	init_result_str(char *result, int16_t digitexp)
{
	uint16_t	len;
	int16_t	pos_exp;

	result[MAX_DIGIT] = '\0';
	ft_memset(result, '0', MAX_DIGIT);
	if (digitexp > 0)
		return (1);
	len = 2;
	result[len] = '.';
	if (digitexp < 0)
	{
		pos_exp = -digitexp;
		while (len - 2 < pos_exp)
			++len;
	}
	return (len);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n--)
	{
		if (*s1 != *s2) {
			return (*(unsigned char *)s1 - *(unsigned char *)s2);
		}
		if (*s1 == '\0') {
			return (0);
		}
		++s1;
		++s2;
	}
	return (0);
}

/*
 * function that converts a fraction (numerator/denominator) into a floating-point number string.
 * Handles edge cases like numbers < 1, proper placement of decimal point, and precision.
 */
// char	*convert_to_str(char *str, char *num, char *deno, int16_t digitexp)
char	*convert_to_str(t_dbl *s, int16_t digitexp)
{
	char	tmp[BIG_INT + 1];
	char	digit[BIG_INT + 1];
	char	zero[BIG_INT + 1];
	uint16_t	len;
	size_t	zero_len_plus_term;
	len = init_result_str(s->result, digitexp);
	init_bigChar(digit);
	digit[BIG_INT - 2] = '1';
	init_bigChar(zero);
	if (digitexp == 0)
		len = convert_first_digit(s->result, s->s1, s->s2);
	else if (digitexp < 0)
		digitexp = 0;
	zero_len_plus_term = ft_strlen(zero) + 1;
	while (ft_strncmp(s->s1, zero, zero_len_plus_term) != 0 && len < MAX_DIGIT)
	{
		init_bigChar(tmp);
		cpy_str(tmp, s->s1);
		ft_division(tmp, s->s2);
		s->result[len++] = tmp[BIG_INT - 1];
		while (tmp[BIG_INT - 1]-- != '0')
			ft_subtraction(s->s1, s->s2);
		ft_multiply(s->s1, digit);
		place_decimal_point(s->result, s->s1, &len, &digitexp);
	}
	return (s->result);
}

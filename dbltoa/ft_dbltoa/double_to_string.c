/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   double_to_string.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/12 17:26:37 by jmetzger      #+#    #+#                 */
/*   Updated: 2025/03/09 04:00:17 by rjw           ########   odam.nl         */
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
static void		process_first_digit(char *result, char *num, char *deno)
{
	char	tmp[BIG_INT + 1];
	char	digit[BIG_INT + 1];

	intialize_string(tmp);
	intialize_string(digit);
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
}

/*
 * Ensures that the decimal point is placed correctly in the string representation.
 */
static void	insert_dec_point(char *res, char *num, uint16_t *len, int16_t *exp)
{
	char		zero[BIG_INT + 1];
	uint16_t	i;

	i = 0;
	intialize_string(zero);
	if (*len - 1 > *exp && *exp != 0)
	{
		res[(*len)++] = '.';
		*exp = 0;
	}
	if (ft_strncmp(num, zero, BIG_INT + 1) == 0)
	{
		while (res[i] != '\0' && res[i] != '.')
			++i;
		if (res[i] == '\0')
			res[*exp + 2] = '.';
	}
}

uint16_t	initialize_strings(t_dbl *s, int16_t *digitexp)
{
	int16_t		pos_exp;
	uint16_t	len;

	s->result[MAX_DIGIT] = '\0';
	ft_memset(s->result, '0', MAX_DIGIT);
	if (*digitexp > 0)
		return (1);
	s->result[2] = '.';
	if (*digitexp < 0)
	{
		len = 0;
		pos_exp = -(*digitexp);
		while (len < pos_exp)
			++len;
		len += 2;
		*digitexp = 0;
		return (len);
	}
	process_first_digit(s->result, s->s1, s->s2);
	return (3);
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
void	double_to_string(t_dbl *s, int16_t digit_exponent)
{
	char		tmp[BIG_INT + 1];
	char		digit[BIG_INT + 1];
	char		zero[BIG_INT + 1];
	uint16_t	len;

	len = initialize_strings(s, &digit_exponent);
	intialize_string(digit);
	digit[BIG_INT - 2] = '1';
	intialize_string(zero);
	while (ft_strncmp(s->s1, zero, BIG_INT) != 0 && len < MAX_DIGIT)
	{
		cpy_str(tmp, s->s1);
		ft_division(tmp, s->s2);
		s->result[len++] = tmp[BIG_INT - 1];
		while (tmp[BIG_INT - 1]-- != '0')
			ft_subtraction(s->s1, s->s2);
		ft_multiply(s->s1, digit);
		insert_dec_point(s->result, s->s1, &len, &digit_exponent);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_dbltoa.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/12 01:27:15 by rjw           #+#    #+#                 */
/*   Updated: 2025/03/12 01:27:17 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_dbltoa.h"

//	Static functions
static int16_t	dbltoa_convert(double value, t_dbl *strings);

char	*dbltoa(double value)
{
	char	result[MAX_DBL_STR_LEN + 1];
	t_dbl	strings;

	strings.result = result;
	strings.prec = UINT16_MAX;
	dbltoa_convert(value, &strings);
	return (ft_strdup(result));
}

char	*dbltoa_precision(double value, uint16_t prec)
{
	char	result[MAX_DBL_STR_LEN + 1];
	t_dbl	strings;

	strings.result = result;
	strings.prec = prec;
	dbltoa_convert(value, &strings);
	return (ft_strdup(result));
}

uint16_t	dbltoa_buff(double value, char *buff, uint16_t b_size)
{
	char		result[MAX_DBL_STR_LEN + 1];
	t_dbl		strings;
	uint16_t	result_len;

	if (b_size == 1)
		buff[0] = '\0';
	if (b_size <= 1)
		return (b_size);
	strings.result = result;
	strings.prec = UINT16_MAX;
	result_len = dbltoa_convert(value, &strings);
	// printf(">%s\n", strings.result);
	if (b_size <= result_len)
	{
		ft_strlcpy(buff, result, b_size);
		--b_size;
		if (buff[b_size - 1] == '.')
		{
			buff[b_size - 1] = '\0';
			--b_size;
		}
		return (b_size);
	}
	ft_strlcpy(buff, result, result_len + 1);
	return (result_len);
}

static int16_t	dbltoa_convert(double value, t_dbl *strings)
{
	int16_t		digitexpo;			// stores the exponent
	char		numerator[MAX_DBL_STR_LEN + 1]; 	// storing the numerator
	char		denominator[MAX_DBL_STR_LEN + 1]; 	// storing the denominator
	bool 		is_neg;
	uint16_t	result_len;

	is_neg = true;
	intialize_string(numerator);
	intialize_string(denominator);
	strings->s1 = numerator;
	strings->s2 = denominator;
	if (fraction_conversion(value, strings, &is_neg) == false)
		return (ft_strlen(strings->result));
	scientific_notation(numerator, denominator, &digitexpo, value);
	double_to_string(strings, digitexpo);
	result_len = process_number_string(strings->result, is_neg);
	if (strings->prec == UINT16_MAX)
		return (result_len);
	return (process_precision(strings->result, strings->prec));
}
